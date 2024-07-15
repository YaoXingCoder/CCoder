/* 
Date:2024.7.15
Title:取消线程链接 pthread_cancel()
Author:JiaZiChunQiu
Content:
在入口函数中写无限循环
main线程对新线程调用取消线程请求

默认到下一个取消点，取消，没有则main线程的join永久性阻塞

线程取消分为
1.取消状态：setcancelstate(int state, int* oldstate);
    默认: PTHREAD_CANCEL_ENABLE, 线程可以取消
    另选: PTHREAD_CANCEL_DISABLE, 线程不可被取消，会忽略取消请求
2.取消类型: setcanceltype(int state, int* oldtype); 都建立在取消状态为可以取消的基础上
    默认: PTHREAD_CANCEL_DEFERRED, 延迟取消，到下一次取消点取消
    另选: PTHREAD_CANCEL_ASYNCHRONOUS, 异步响应，可以任意时间点取消，即使没有取消点

设置取消点: pthread_testcancel();
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

typedef struct Student{
    int id;
    char name[25];
    char gender;
    int chinese;
    int math;
    int english;
}Student;

void print_stu_info(Student* s) {
    printf("%d %s %c %d %d %d\n", s->id, s->name, s->gender, s->chinese, s->math, s->english);
}

void print_ids(const char* arg) {
    printf("%s：pid = %d, tid = %#lx\n", arg, getpid(), pthread_self());
}

// 新线程函数
void* start_routine(void* arg){
    // 设置取消状态 和 取消类型
    // int err; // 存储错误信息
    // int oldstate; // 存储旧的错误信息
    // int oldtype;
    // err = pthread_setcancelstate( PTHREAD_CANCEL_DISABLE, &oldstate ); // 默认为PTHREAD_CANCEL_ENABLE为默认, 可以取消；现设置为不可取消
    // if ( err ) { error(1, err, "pthread_setcancelstate"); }
    // err = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype); // 即使没有取消点也会响应取消
    // if ( err ) { error(1, err, "setcanceltype"); }

    // 打印旧的状态信息
    // printf("oldstate =  %d\n", oldstate);
    // printf("oldtype =  %d\n", oldtype);

    // 设置取消点
    // pthread_testcancel();

    int i = 0;
    // 循环
    for(;;) { 
        i++;
      //  printf("hello %d \n", i); // 取消点
      //  sleep(1); // 取消点
    }
    return (void*)9425; // 执行不到
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
    // printf("main: new thread is %#lx\n", tid);
    // sleep(1); // 等待新线程
    // print_ids("main");
    
    // 对新线程调用取消请求
    err = pthread_cancel(tid);
    if (err) { error(1, err, "pthread_cancel"); }

    // join获取新线程信息，join会阻塞等待新线程
    void* ret;
    err = pthread_join(tid, &ret);
    // Student* s = NULL;
    // err = pthread_join(tid, (void**)&s);
    if (err) { error(1, err, "pthread_join"); } // 错误处理

    // 打印接收值
    printf("ret is %lu \n", (long)ret);
    printf("ret is %p \n", ret);
    // print_stu_info(s);
    // free(s); // 释放资源

    return 0; // 退出
}

