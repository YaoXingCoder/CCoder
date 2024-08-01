/* 
Date:2024.7.15
Title:连接终止线程
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
    printf("new thread is running...\n");
    // print_ids("new thread");
    printf("new thread is ending..\n");

    // 测试join阻塞
    sleep(2);

    // 结构体信息
    Student* s = (Student*)malloc(sizeof(Student));
    s->id = 1;
    strcpy(s->name, "123");
    s->gender = 'm';
    s->chinese = 100;
    s->math = 100;
    s->english = 100;

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
    // printf("main: new thread is %#lx\n", tid);
    // sleep(1); // 等待新线程
    // print_ids("main");

    // join获取新线程信息，join会阻塞等待新线程
    void* ret;
    err = pthread_join(tid, &ret);
    // Student* s = NULL;
    // err = pthread_join(tid, (void**)&s);
    if (err) { error(1, err, "pthread_join"); } // 错误处理

    // 打印接收值
    long i = (long)ret;
    printf("ret is %lu \n", i);
    // print_stu_info(s);

    // free(s);

    // 退出
    return 0;
}

