/* 
Date:2024.7.11
Title:execve()执行程序
Author:JiaZiChunQiu
Content:

 */

#include <my_header.h> 
#include <unistd.h>


int main(int argc, char* argv[]) {
    // 打印进程pid
    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    // 打印命令行参数
    printf("Arguments:\n");
    for(int i = 0; i < argc; i++) {
        printf("    %s\n", argv[i]);
    }

    // 打印环境变量
    printf("Enviroments:\n");
    extern char** environ; // 外部变量
    char** p = environ;
    while(*p != NULL) {
        printf("    %s\n", *p);
        p++;
    }
    return 0;
}

