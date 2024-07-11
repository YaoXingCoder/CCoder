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

int main(int argc, char* argv[]) {
    printf("BEGIN   ");
    
    // 创建进程
    pid_t pid = fork();

    switch(pid) {
    case -1:
        error(1, errno, "fork()");
    case 0: // 子线程
        // sleep(3);
        printf("I am a baby.\n");
        exit(0);
    default: // 父线程
        sleep(2);
        printf("who's your daddy?\n");
        exit(0);
    }
    return 0;
}

