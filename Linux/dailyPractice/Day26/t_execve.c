/* 
Date:2024.7.11
Title:execve()执行程序
Author:JiaZiChunQiu
Content:

 */

#include <my_header.h>
#include <unistd.h>

char* arguments[] = {"echoall", "aaa", "bbb", "ccc", NULL};
char* enviroments[] = {"USER=coder", "a=A", "b=B", NULL};

int main(int argc, char* argv[]) {
    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    printf("executing execve()\n");

    execve("echoall", arguments, enviroments);
    printf("you can not see me\n");
    return 0;
}

