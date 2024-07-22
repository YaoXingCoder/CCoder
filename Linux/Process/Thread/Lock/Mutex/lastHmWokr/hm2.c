/* 
Date:2024.7.15
Title:双线程求和
Author:JiaZiChunQiu
Content:
创建两个线程
第一个线程对区间[1, n/2]累加
第二个线程对区间(n/2, n]累加

mian线程接收，并相加输出
*/

#include <my_header.h>
// error
#include <error.h>
// pthread
#include <pthread.h>
// sleep
#include <unistd.h>

// 入口函数
void* start_routine1(void* arg){
    long long* tmp = (long long*)arg;
    for(int i = 1; i <= 100; i++) { (*tmp)++;}
    printf("tid = %lu, value = %lld\n", pthread_self(), *tmp); // 查看新线程输出
    return NULL;
}

int main(int argc, char* argv[]) {
    long long* value = (long long*) calloc(1, sizeof(long long));
    // 接收状态码和新线程x2
    int err;
    pthread_t tid1;
    pthread_t tid2;

    // 创建新线程
    err = pthread_create(&tid1, NULL, start_routine1, (void*)value);
    if (err) { error(1, err, "pthread_create, tid1"); }
    err = pthread_create(&tid2, NULL, start_routine1, (void*)value);
    if (err) { error(1, err, "pthread_create, tid2"); }

    // join接收线程返回值
    err = pthread_join(tid1, NULL);
    if (err) { error(1, err, "phtread_join tid1"); }
    err = pthread_join(tid2, NULL);
    if (err) { error(1, err, "phtread_join tid2"); }

    printf("*value = %lld \n", *value);

    return 0;
}

