/* 
Date:2024.7.15
Title:线程退出
Author:
Content:
pthread_exit
创建线程可以return退出，不会对进程有影响
也可以pthread_exit退出

main线程使用return退出，会造成进程退出，导致所有的线程退出
main线程使用pthread_exit退出，其他线程仍会继续执行，当所有线程推出后，进程也会终止(也会默认调用exit)
 */

#include <my_header.h>
// pthread_create | pthread_self
#include <pthread.h>
// getpid
#include <unistd.h>
// error
#include <error.h>
// on_exit()
#include <stdlib.h>

void print_ids(const char* arg) {
    printf("%s：pid = %d, tid = %#lx\n", arg, getpid(), pthread_self());
   // pthread_exit(NULL);
}

// 新线程函数
void* start_routine(void* arg){
    // sleep(3);
    printf("new thread is running...\n");
    print_ids("new thread");
    printf("new thread is ending..\n");

    exit(1);
    // return (void*)1;
    // pthread_exit(NULL);
}

//exit() 退出处理函数
void onexitFunc(int status, void* arg){
    printf("exit()：statud is %d, arg is %ld \n", status, (long)arg);
}

int main(int argc, char* argv[]) {
    // test
    // printf("sizeof(int) = %zuB, sizeof(void*) = %zuB, sizeof(long) = %zuB\n", sizeof(int), sizeof(void*), sizeof(long));
    
    // 注册退出处理函数
    on_exit(onexitFunc, (void*)100);

    // 记录返回错误，和线程id
    int err;
    pthread_t tid;
    
    // 创建新线程
    err = pthread_create(&tid, NULL, start_routine, NULL);
    if (err) { error(1, err, "pthread_t"); }
    
    // 新线程id和main信息
    printf("main: new thread is %#lx\n", tid);
    sleep(1); // 等待新线程
    print_ids("main");

    // 线程退出
    pthread_exit(NULL); // main线程结束子线程仍可继续执行

    // 进程的退出
    // return 0;
}

