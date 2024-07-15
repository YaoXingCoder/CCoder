/* 
Date:
Title:
Author:
Content:
 */

#include <my_header.h>
// pthread_self()
#include <pthread.h>


int main(int argc, char* argv[]) {
    printf("pthread_self = %lu \n", pthread_self());
    printf("pthread_self = %#lx \n", pthread_self());
    return 0;
}

