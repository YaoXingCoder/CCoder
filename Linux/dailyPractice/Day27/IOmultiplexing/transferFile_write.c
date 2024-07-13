/* 
Date:2024.7.13
Title:管道传输文件
Author:JiaZiChunQiu
Content:
管道：1.pipe
write用于发送文件

 */

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// error
#include <error.h>
#include <errno.h>
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
    // 打开，读管道1，写管道2
    int fdw = open("1.pipe", O_WRONLY);
    if (fdw == -1) { error(1, errno, "open write 1.pipe"); }

    FNode fileWrite = {"test1.txt", 123, "helloworld"};

    // 读取用户输入，并格式化
    // printf("Please enter the file about name, size(B) and content:>");
    // fscanf(stdin, "%s %ld %s", fileWrite.name, &fileWrite.size, fileWrite.content);

    // 获取到文件信息，并输出
    // 先传输名字长度
    int nameLen = strlen(fileWrite.name);
    write (fdw, &nameLen, sizeof(int));
    write(fdw, fileWrite.name, strlen(fileWrite.name)); // 文件名字

    // 传输文件大小
    write(fdw, &fileWrite.size, sizeof(long)); // 文件大小
    
    // 传输内容
    int conLen = strlen(fileWrite.content);
    write(fdw, &conLen, sizeof(int));
    write(fdw, fileWrite.content, conLen); // 文件内容

    close(fdw);
    return 0;
}

