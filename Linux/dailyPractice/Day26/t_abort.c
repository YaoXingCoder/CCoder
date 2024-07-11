/* 
Date:2024.7.11
Title:abort异常终止
Author:JiaZiChunQiu
Content:
异常终止，abort不会刷新缓冲区，不会执行退出处理函数
 */

#include <my_header.h>
// atexit()
#include <stdlib.h>
// error
#include <error.h>
#include <errno.h>
// sleep
#include <unistd.h>

void exitFunc1(void) {
    printf("I'm going to die1\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void exitFunc2(void) {
    printf("I'm going to die2\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void exitFunc3(void) {
    printf("I'm going to die3\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void onexitFunc1(int exitStatus, void* arg) {
    printf("on_eixt_function called: status = %d, arg = %ld\n", exitStatus,(long)arg);
}
void onexitFunc2(int exitStatus, void* arg) {
    printf("on_eixt_function called: status = %d, arg = %ld\n", exitStatus, (long)arg);
}

int main(int argc, char* argv[]) {
    if(on_exit(onexitFunc1,(void*) 10) != 0) error(1, errno, "on_exit onexitFunc1");
    if(atexit(exitFunc1) != 0) error(1, errno, "atexit exitFunc1");
    if(atexit(exitFunc2) != 0) error(1, errno, "atexit exitFunc2");
    if(atexit(exitFunc3) != 0) error(1, errno, "atexit exitFunc3");
    if(on_exit(onexitFunc2,(void*) 20) != 0) error(1, errno, "on_exit onexitFunc1");

    printf("Pragramming running...");
    sleep(3);


    // printf("BEGIN...\n");
    // exit(3);
    // printf("END...\n");
    // exit(0);
    // return 0;
    abort();
}

