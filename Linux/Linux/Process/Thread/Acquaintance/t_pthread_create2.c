/* 
Date:2024.7.15
Title:线程创建，传输结构体给新线程
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

typedef struct Student {
    char name[20];
    int age;
}Student;

void print_ids(const char* arg) {
    printf("%s：pid = %d, tid = %#lx\n", arg, getpid(), pthread_self());
}

void* start_routine(void* arg){
    printf("new thread is running...\n");
    print_ids("new thread");
    // 接收结构体并输出
    Student* s = (Student*)arg;
    printf("student s = {%s, %d}\n", s->name, s->age);
    printf("new thread is ending..\n");
    return NULL;
}

int main(int argc, char* argv[]) {
    // 记录返回错误，和线程id
    int err;
    pthread_t tid;

    // 传输结构体
    Student s = {"123", 123};
    
    // 创建新线程
    err = pthread_create(&tid, NULL, start_routine, &s);
    if (err) { error(1, err, "pthread_t"); }
    
    // 输出新线程id和主线程id
    printf("main: new thread is %#lx\n", tid);
    print_ids("main");

    sleep(1);
    return 0;
}

