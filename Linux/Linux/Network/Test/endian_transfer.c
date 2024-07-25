/*************************************************************************
    > File Name: endian_transfer.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月19日 星期五 09时21分46秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 大小端的转换演示
    > Content: 
 ************************************************************************/

#include <my_header.h>
// htonl
#include <arpa/inet.h>

int main (int argc, char* argv[]) {
    unsigned short us = 0x1234;
    printf("%x\n", us);
    unsigned short us1 = htons(us); // 小 -> 大
    printf("%x\n", us1);
    printf("%x\n", ntohs(us1)); // 大 -> 小
    return 0;
}
