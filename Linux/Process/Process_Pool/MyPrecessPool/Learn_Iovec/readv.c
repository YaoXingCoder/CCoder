/*************************************************************************
    > File Name: readv.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月31日 星期三 10时09分33秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 分散读readv, iovs
    > Content:
 ************************************************************************/

#include <my_header.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
    int fd = open("file.txt", O_RDONLY);
    ERROR_CHECK(fd, -1, "open");

    char buff1[6] = { 0 };
    char buff2[6] = { 0 };

    struct iovec iovs[2];
    memset(iovs, 0, sizeof(iovs));
    iovs[0].iov_base = buff1;
    iovs[0].iov_len = sizeof(buff1);
    iovs[1].iov_base = buff2;
    iovs[1].iov_len = sizeof(buff2);

    /* 分散读, 将一条长的字符串内容分别放入到不同的缓冲区
     * 只有前面的iovec填满之后, 才会添下一个
     * */
    int ret = readv(fd, iovs, 2);
    ERROR_CHECK(ret, -1, "readv");

    printf("readv %d bytes\n", ret);
    printf("buff1 is %s\n", buff1);
    printf("buff2 is %s\n", buff2);

    close(fd);
    return 0;
}
