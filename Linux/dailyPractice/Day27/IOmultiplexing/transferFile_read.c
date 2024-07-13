/* 
Date:2024.7.13
Title:传输文件
Author:JiaZiChunQiu
Content:
read用于接收文件
若文件未常见则创建该文件
 */

#include <my_header.h>
// error
#include <error.h>
#include <errno.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// select
#include <sys/select.h>
// read, write
#include <unistd.h>

#define MAXLINE 1024

typedef struct File{
    char name[64];
    long size;
    char content[1024];
}FNode;

int main(int argc, char* argv[]) {
    // 打开，写管道1，读管道2
    int fdr = open("1.pipe", O_RDONLY);
    if (fdr == -1) { error(1, errno, "open read 1.pipe"); }

    FNode fileRead;
    // 读取文件相关信息
    
    // 读取文件名
    int nameLen = 0;
    read(fdr, &nameLen, sizeof(int));
    read(fdr, fileRead.name, nameLen);

    // 读取文件大小
    read(fdr, &fileRead.size, sizeof(long));

    // 读取内容
    int conLen = 0;
    read(fdr, &conLen, sizeof(int));
    read(fdr, fileRead.content, conLen);

    // 创建文件描述符并写入
    int newfd = open(fileRead.name, O_WRONLY|O_CREAT|O_TRUNC, 0664);
    ftruncate(newfd, fileRead.size);
    write(newfd, fileRead.content, conLen);

    close(newfd);
    close(fdr);
    return 0;
}

