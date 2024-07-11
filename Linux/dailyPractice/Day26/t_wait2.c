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

// 解析进程的终止状态
void print_wastatus(int status) {
    // 正常终止
    if(WIFEXITED(status)) {
        printf("Exit code: %d\n", WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)) { // 异常终止
        printf("Terminational Signal: %d\n", WTERMSIG(status));
#ifdef WCOREDUMP
        if (WCOREDUMP(status)) {
            printf("core dump\n");
        }
#endif
    }
}

int main(int argc, char* argv[]) {
    switch(fork()) {
    case -1:
        error(1, errno, "fork");
    case 0: // 子进程
        printf("Child: childpid = %d, parentpid = %d\n", getpid(), getppid());
        for(;;);
        // exit(108);
        _exit(10);
    default:
        int status;
        pid_t pid = wait(&status); // NULL 不接受进程的终止状态信息
        
        if (pid == -1) error(1, errno, "wait");

        printf("Parent: child %d terminated\n", pid);
        print_wastatus(status);
    }     
    return 0;
}

