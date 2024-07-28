/* 
Date:2024.7.15
Title:线程创建
Author:
Content:
 */

#include <my_header.h>
// pthread_create | pthread_self
#include <pthread.h>
// getpid
#include <unistd.h>
// error
#include <error.h>

void print_ids(const char* arg) {
    printf("%s：pid = %d, tid = %#lx\n", arg, getpid(), pthread_self());
}

void* start_routine(void* arg){
    printf("new thread is running...\n");
    print_ids("new thread");
    printf("new thread is ending..\n");
    return NULL;
}

int main(int argc, char* argv[]) {
    // 记录返回错误，和线程id
    int err;
    pthread_t tid;
    
    // 创建新线程
    err = pthread_create(&tid, NULL, start_routine, NULL);
    if (err) { error(1, err, "pthread_t"); }
    
    printf("main: new thread is %#lx\n", tid);
    print_ids("main");

    sleep(1);
    return 0;
}

