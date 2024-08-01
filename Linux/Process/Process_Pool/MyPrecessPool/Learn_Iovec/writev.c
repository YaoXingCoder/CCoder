/*************************************************************************
    > File Name: writev.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月31日 星期三 09时16分29秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 聚合写, iovs
    > Content:
 ************************************************************************/

#include <my_header.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
    char buff1[] = "hello";
    char buff2[] = "world";

    struct iovec iovs[2];
    iovs[0].iov_base = buff1;
    iovs[0].iov_len = sizeof(buff1);
    iovs[1].iov_base = buff2;
    iovs[1].iov_len = sizeof(buff2);

    int fd = open("file.txt", O_WRONLY | O_TRUNC);
    ERROR_CHECK(fd, -1, "open");

    /* writev是一个系统调用, 可以提高程序的执行效率  
     * 若用write操作, 需要两次write才能将buff1, buff2
     * */
    int ret = writev(fd, iovs, 2);
    printf("write %d bytes.\n", ret);

    close(fd);
    return 0;
}
