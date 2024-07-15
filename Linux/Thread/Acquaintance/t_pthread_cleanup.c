/* 
Date:2024.7.15
Title:线程清理函数 pthread_cleanup_push() | pthread_cleanup_pop()
Author:JiaZiChunQiu
Content:
引起处理函数的情况
1.响应取消请求
2.调用pthread_exit()函数
3.调用pthread_cleanup_pop(), 传入参数不为0

处理函数: void routine(void* arg);
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

// 线程处理函数
void routine(void* arg){
    char* msg = (char*) arg;
    puts(msg);
}

// 新线程函数
void* start_routine(void* arg){

    // pthread_exit(NULL); // 不会执行后边线程处理函数

    // 添加线程清理函数
    pthread_cleanup_push(routine, (void*)"111");
    pthread_cleanup_push(routine, (void*)"222");


    // exit(1); // 退出,只执行一次
    // pthread_exit(NULL); // 执行结束

    printf("new thread Begin...\n");
    sleep(3);
    printf("new thread End...\n");

    return (void*)9425;

    // 清理函数出栈
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    // return (void*)9425; // 返回值
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
    // err = pthread_cancel(tid);
    // if (err) { error(1, err, "pthread_cancel"); }

    // join获取新线程信息，join会阻塞等待新线程
    void* ret;
    err = pthread_join(tid, &ret);
    if (err) { error(1, err, "pthread_join"); } // 错误处理

    // 打印接收值
    printf("ret is %lu \n", (long)ret);
    printf("ret is %p \n", ret);

    return 0; // 退出
}

