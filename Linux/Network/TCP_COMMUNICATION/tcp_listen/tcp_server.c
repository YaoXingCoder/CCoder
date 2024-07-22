/*************************************************************************
    > File Name: tcp_server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月19日 星期五 21时25分52秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 创建服务器端, 开启Listen监听
    > Content:
    >   1.sokcet 获取套接字
    >   2.bind 绑定 ip+port 与 套接字
    >   3.listen 将套接字变为监听模式
 ************************************************************************/

#include <my_header.h>
// socket
#include <sys/socket.h>
// struct sockaddr_in
#include <arpa/inet.h>
// inet_aton
#include <netinet/in.h>

int main (int argc, char* argv[]) {
    // 创建套接字, 关联socket设备
    int socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    if ( socketfd < 0) { error(1, errno, "socket"); }

    // 创建sockaddr, 指定类型, 端口, IP
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_port = htons(8080); // 端口
    serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129"); // ip

    printf("serverAddr is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    // 通过bine, 绑定socketfd 与 ip+port 便于开启监听
    int ret = bind(socketfd, (const struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");

    // 打开监听
    ret = listen(socketfd, 2);
    ERROR_CHECK(ret, -1, "listen");

    while(1);

    return 0;
}
