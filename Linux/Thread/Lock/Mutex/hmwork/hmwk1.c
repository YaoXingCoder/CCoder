/* 
Date:2024.7.16
Title:互斥锁
Author:JiaZiChunQiu
Content:
typedef struct {
    int id;
    int money;
} Account;

Account acct1 = {1, 100};

int main(void) {
    // 创建10个线程，同时去acct账号上取100。
    // 要求：任何情况下，都只能有一个线程能取成功。

    // 主线程等待各个子线程结束。
}
 */

#include <my_header.h>
// pthread, pthread_mutex_t
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 锁定义和初始化

#define THREAD_NUMS 10

// 账户结构体
typedef struct {
    long id;
    long money;
}Account;

Account acct1 = {1, 100}; // 初始化

// 清理函数，当线程结束后，总是释放锁
void cleanup(void* arg) { 
    pthread_mutex_unlock(&mutex);
}

// withdraw, 判断余额，互斥进行操作, 返回所取金额
long withdraw(Account* acct, const long money){
    pthread_mutex_lock(&mutex); // 上锁

    pthread_cleanup_push(cleanup, NULL);

    // 余额不足, 不做操作, 解锁
    if (acct->money < money) {
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    // 余额充足
    acct->money -= money;
    pthread_mutex_unlock(&mutex);
    return money;

    pthread_cleanup_pop(1);
}

// 入口函数, 执行withdraw函数
void* start_routine(void* arg){
    long money = (long)arg;
    long tmp = withdraw(&acct1, money);
    printf("thread id = %#lx, money is %ld \n", pthread_self(), tmp);
    return NULL;
}

int main(int argc, char* argv[]) {
    
    // 创建10个进程
    pthread_t threads[10];
    int err;
    for(int i = 0; i < THREAD_NUMS; i++) {
        err = pthread_create(threads + i, NULL, start_routine, (void*)100);
        if (err) { error(1, err, "pthread_create"); }
    }

    // 顺序的join，等待所有的进程执行完毕
    for( int i = 0; i < THREAD_NUMS; i++) { 
        err = pthread_join(threads[i], NULL);  
        if (err) { error(1, err, "phtread_join");  }
    }

    return 0;
}

