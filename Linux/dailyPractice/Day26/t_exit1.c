/* 
Date:
Title:
Author:
Content:
 */

#include <my_header.h>
// atexit()
#include <stdlib.h>
// error
#include <error.h>
#include <errno.h>

void exitFunc1(void) {
    printf("I'm going to die1\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void exitFunc2(void) {
    printf("I'm going to die2\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void exitFunc3(void) {
    printf("I'm going to die3\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}

int main(int argc, char* argv[]) {
    if(atexit(exitFunc1) != 0) error(1, errno, "atexit exitFunc1");
    if(atexit(exitFunc2) != 0) error(1, errno, "atexit exitFunc2");
    if(atexit(exitFunc3) != 0) error(1, errno, "atexit exitFunc3");

    printf("BEGIN...\n");

    printf("END...\n");
    exit(0);
    return 0;
}

