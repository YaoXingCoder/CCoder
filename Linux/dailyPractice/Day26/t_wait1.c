/* 
Date:2024.7.11
Title:wait()等待子进程终止
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
// wait
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    switch(fork()) {
    case -1:
        error(1, errno, "fork");
    case 0: // 子进程
        for(;;);
        exit(2);
    default:
        pid_t pid = wait(NULL);
        if (pid == -1) error(1, errno, "wait");

        printf("child %d terminated\n", pid);
    }     
    return 0;
}

