/* 
Date:2024.7.15
Title:分离线程，pthread_detach()
Author:JiaZiChunQiu
Content:

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

void print_ids(const char* prex) {
    printf("%s : pid = %d, tid = %ld \n", prex, getpid(), pthread_self());
}

// 新线程函数
void* start_routine(void* arg){
    printf("new thread is running...\n");
    print_ids("new thread");
    printf("new thread is ending..\n");

    // sleep(2); // 测试join阻塞

    // int err = pthread_detach(pthread_self()); // 设置为分离状态, main线程的join报错 Invalid argument
    // if(err) { error(1, err, "pthread_detach"); }

    // pthread_exit(s);
    return (void*) 9527;
    // return NULL;
}

// 主函数
int main(int argc, char* argv[]) {
    // 记录返回错误，和线程id
    int err;
    pthread_t tid;

    // 创建新线程
    err = pthread_create(&tid, NULL, start_routine, (void*)10);
    if (err) { error(1, err, "pthread_t"); }
    
    // 新线程id和main信息
    printf("main: new thread is %#lx\n", tid);
    // sleep(3); // 等待新线程
    print_ids("main");

    // main线程 分离 新线程
    err = pthread_detach(tid);
    if (err) { error(1, err, "pthread_detach"); }

    // join获取新线程信息，join会阻塞等待新线程
    void* ret;
    err = pthread_join(tid, &ret);
    if (err) { error(1, err, "pthread_join"); } // 错误处理

    // 打印接收值
    long i = (long)ret;
    printf("ret is %lu \n", i);

    return 0; // 退出
}

