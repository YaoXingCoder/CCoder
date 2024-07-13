/* 
Date:2024.7.12
Title:使用管道文件实现全双工通信
Author:JiaZiChunQiu
Content:
1.pipe
2.pipe
 */

#include <my_header.h>
// fork, read, write
#include <unistd.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// error
#include <error.h>
#include <errno.h>
// bzero
#include <strings.h>

#define MAXLINE 254

int main(int argc, char* argv[]) {
    int fdw = open("1.pipe", O_WRONLY);
    if (fdw == -1) error(1, errno, "open fdr 1.pipe");

    int fdr = open ("2.pipe", O_RDONLY);
    if (fdr == -1) error(1, errno, "open fdw 2.pipe");

    char reciveLine[MAXLINE];
    char sendLine[MAXLINE];

    while(fgets(sendLine, MAXLINE, stdin) != NULL) {
        write(fdw, sendLine, strlen(sendLine)); // 写入管道1
        read(fdr, reciveLine, MAXLINE); // 读取管道2信息
        printf("from p2 said: %s\n", reciveLine);
    }

    close(fdw);
    close(fdr);

    return 0;
}

