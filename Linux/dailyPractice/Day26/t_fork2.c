/* 
Date:2024.7.11
Title:创建子进程
Author:JiaZiChunQiu
Content:
 */

#include <my_header.h>
// fork
#include <sys/types.h>
#include <unistd.h>
// error
#include <error.h>
#include <errno.h>

int g_value = 10; // 数据段
int main(int argc, char* argv[]) {
    printf("BEGIN\n");

    int l_value = 20; // 栈
    int* d_value = (int*)malloc(sizeof(int)); // 堆
    *d_value = 30;

    // 创建进程
    pid_t pid = fork();

    switch(pid) {
    case -1:
        error(1, errno, "fork()");
    case 0: // 子线程
        // sleep(3);
        g_value += 100;
        l_value += 100;
        *d_value += 100;
        printf("child\n");
        printf("child: pid = %d, parentpid = %d\n", getpid(), getppid());
        printf("g_value = %d, l_value = %d, d_value = %d\n", g_value, l_value, *d_value);
        exit(0);
    default: // 父线程
        sleep(2);
        printf("parent\n");
        printf("parent: pid = %d, childpid = %d\n", getpid(), pid);
        printf("g_value = %d, l_value = %d, d_value = %d\n", g_value, l_value, *d_value);
        exit(0);
    }
    return 0;
}

