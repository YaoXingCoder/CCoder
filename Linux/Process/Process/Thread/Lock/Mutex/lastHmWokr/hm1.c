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

typedef struct{ 
    long long left;
    long long right;
}Section;

// 入口函数
void* start_routine1(void* arg){
    Section* sec = (Section*)arg;
    long long sum = 0;
    for(long long i = sec->left; i <= sec->right; i++) {
        sum += i;
    }
    return (void*)sum;
}

// void* start_routine2(void* arg){
//     long long tmp = (long long)arg;
//     long long sum = 0;
//     for(int i = tmp/2 + 1; i <= tmp; i++) {
//         sum += i;
//     }
//     return (void*)sum;
// }


int main(int argc, char* argv[]) {
    long long n;
    printf("Please input a long long int:");
    scanf("%lld", &n);

    // 接收状态码和新线程x2
    int err;
    pthread_t tid1, tid2;

    // 使用结构体传入区间
    Section sec1 = {1, n/2};
    Section sec2 = {n/2 + 1, n};

    // 创建新线程
    err = pthread_create(&tid1, NULL, start_routine1, (void*)&sec1);
    if (err) { error(1, err, "pthread_create, tid1"); }
    // err = pthread_create(&tid2, NULL, start_routine2, (void*)n);
    err = pthread_create(&tid2, NULL, start_routine1, (void*)&sec2);
    if (err) { error(1, err, "pthread_create, tid2"); }

    // join接收线程返回值
    long long sum1;
    err = pthread_join(tid1, (void**)&sum1);
    if (err) { error(1, err, "phtread_join tid1"); }
    long long sum2;
    err = pthread_join(tid2, (void**)&sum2);
    if (err) { error(1, err, "phtread_join tid2"); }

    // 睡眠等线程结束，并求和输出
    printf("tid1 + tid2 = %lld\n", sum1 + sum2);

    return 0;
}

