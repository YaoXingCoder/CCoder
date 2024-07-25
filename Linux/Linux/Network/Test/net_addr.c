/*************************************************************************
    > File Name: net_addr.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月19日 星期五 09时40分43秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 点分十进制(字符串)与网络字节序的相互转换
    > Content:
 ************************************************************************/

#include <my_header.h>
// inet_aton, inet_ntoa
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char* argv[]) {
    struct sockaddr_in addr;
    inet_aton(argv[1], &addr.sin_addr);
    printf("addr = %0x\n", addr.sin_addr.s_addr);
    printf("addr = %s\n", inet_ntoa(addr.sin_addr));
    return 0;
}
