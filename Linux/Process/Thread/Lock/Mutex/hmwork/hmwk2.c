/* 
Date:2024.7.16
Title:自定义互斥锁, 实现用户间转账 
Author:JiaZiChunQiu
Content:
typedef struct {
    int id;
    int money;
    pthread_mutex_t mutex;
} Account;

Account acct1 = {1, 100, PTHREAD_MUTEX_INITIALIZER};
Account acct2 = {2, 900, PTHREAD_MUTEX_INITIALIZER};

int main(void) {
    // 创建两个线程：
    // 其中一个线程：从acct1转账100给acct2
    // 同时另一个线程：从acct2转账900给acct1
    // 要求：任何情况下，都避免死锁现象！

    // 主线程等待各个子线程结束。
}
 */

#include <my_header.h>
// pthread
#include <pthread.h>
// sleep
#include <unistd.h>

// 带锁结构体
typedef struct {
    long id;
    long money;
    pthread_mutex_t mutex;
}Account;

Account acct1 = {1, 200, PTHREAD_MUTEX_INITIALIZER}; // tid1 = acct1
Account acct2 = {2, 1000, PTHREAD_MUTEX_INITIALIZER}; // tid2 = acct2

// 清理函数, 函数执行结束总是释放锁
void cleanup(void* arg) {

}

// transfer: A 转账给 B
long transfer(Account* acctA, Account* acctB, long money) {
    // 需要同是对两个用户操作，且锁在用户本身空间内，所以对两个用户中的锁进行上锁，
    // 其他用户想要进入函数操作用户，应持先上锁才能进入，若锁已被使用则被阻塞在上锁
    if(acctA->id < acctB->id ) {
        pthread_mutex_lock(&acctA->mutex);
        pthread_mutex_lock(&acctB->mutex);
    } else{
        pthread_mutex_lock(&acctB->mutex);
        pthread_mutex_lock(&acctA->mutex);   
    }

    // 清理函数
    pthread_cleanup_push(cleanup, (void*)acctA);
    pthread_cleanup_push(cleanup, (void*)acctB);

    // 余额不足
    if (acctA->money < money){
        pthread_mutex_unlock(&acctA->mutex);
        pthread_mutex_unlock(&acctB->mutex);
        return 0;
    }
    
    acctA->money -= money;
    acctB->money += money;

    pthread_mutex_unlock(&acctA->mutex);
    pthread_mutex_unlock(&acctB->mutex);

    return money;

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}

// 口函数1
void* start_routine1(void* arg) {
    long money = (long) arg;
    printf("acct1 balance is %ld\n", acct1.money);
    sleep(2); // 先查看余额
              //
    long transfer_money = transfer(&acct1, &acct2, money);
    printf("acct1 -> acct2 money is %ld\n", transfer_money);

    sleep(2);
    printf("acct1 balance is %ld\n", acct1.money);
    return NULL;
}

// 入口函数2
void* start_routine2(void* arg) {
    long money = (long) arg;
    printf("acct2 balance is %ld\n", acct2.money);
    sleep(2); // 查看余额
              //
    long transfer_money = transfer(&acct2, &acct1, money);
    printf("acct2 -> acct1 money is %ld\n", transfer_money);

    sleep(2);
    printf("acct2 balance is %ld\n", acct2.money);
    return NULL;
}

// 主函数
int main(int argc, char* argv[]) {
    // double thread
    int err;
    pthread_t tid1, tid2;

    // create thread
    err = pthread_create(&tid1, NULL, start_routine1, (void*)100); // 转账100->acct2
    if(err) {error(1, err, "create tid1"); }
    err = pthread_create(&tid2, NULL, start_routine2, (void*)900); // 转账900->acct1
    if(err) {error(1, err, "create tid2"); }

    // join wait 
    err = pthread_join(tid1, NULL);
    if(err) {error(1, err, "join tid1");}
    err = pthread_join(tid2, NULL);
    if(err) {error(1, err, "join tid2");}

    return 0;
}

