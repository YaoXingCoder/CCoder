/* 
Date:
Title:
Author:
Content:
 */

#include <my_header.h>
// fork open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
// error
#include <errno.h>
#include <error.h>

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666);
    if(fd == -1) error(1, errno, "open fd %s", argv[1]);
    
    printf("pos: %ld\n", lseek(fd, 0, SEEK_CUR)); // pos = 0;

    pid_t pid = fork();
    int newfd;

    switch(pid) {
    case -1:
        error(1, errno, "fork()");
    case 0:
        write(fd, "hello world", 11); // 写入数据

        close(STDERR_FILENO); // 关闭表述错误流
        newfd = dup(fd); // 使标准错误流指向文件流, newfd = 2;
        printf("newfd = %d\n", newfd); // 输出newfd的文件描述符
        exit(0);
    default:
        sleep(2);
        printf("pos: %ld\n", lseek(fd, 0, SEEK_CUR)); // pos = 11; 指向同一个文件描述符，共享其中的文件指针

        newfd = dup(fd); // newfd = 4;
        printf("newfd = %d\n", newfd);
        exit(0);
    }
    return 0;
}

