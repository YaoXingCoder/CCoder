/* 
Date:2024.7.11
Title:获取进程id/ppid
Author:JiaZiChunQiu
Content:
 */

#include <my_header.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("getpid = %d\n", getpid());
    printf("getppid = %d\n", getppid());

    printf("Pragramming running...");
    sleep(3);
    
    _exit(2);
}

