/*************************************************************************
  > File Name: tcp_server.c
  > Author: JiaZiChunQiu
  > Created Time: 2024年07月19日 星期五 21时25分52秒
  > Mail: JiaZiChunQiu@163.com
  > Title: 创建服务器端, 开启Listen监听
  > Content:
  >   1.sokcet 获取套接字
  >   2.创建strucet sockaddr_in, 填写需要连接的服务器ip:port
  >   3.connect连接服务器, 服务器需要开启listen
  >   4.使用recv获取服务器发送的数据, 并输出到屏幕
 ************************************************************************/

#include <my_header.h>
// socket
#include <sys/socket.h>
// struct sockaddr_in
#include <arpa/inet.h>
// inet_aton
#include <netinet/in.h>
// close
#include <unistd.h>

#define MAX_LINE 1024

int main (int argc, char* argv[]) {
    // 创建套接字, 关联socket设备
    int socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    if ( socketfd < 0) { error(1, errno, "socket"); }
    printf("socketfd is %d\n", socketfd); // 套接字值

    // 创建sockaddr, 指定类型, 端口, IP
    struct sockaddr_in clientAddr ={ 0 };
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(8080); // 端口
    clientAddr.sin_addr.s_addr = inet_addr("192.168.225.129"); // ip

    printf("serverAddr is %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port)); // 请求的服务器地址

    // connect 连接服务器
    int ret = connect(socketfd, (const struct sockaddr*)&clientAddr, sizeof(clientAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("connect success~~~\n"); // 连接成功

    // 接收缓冲
    char receLine[MAX_LINE] = { 0 };
    char sendLine[MAX_LINE] = { 0 };

    while(1) {
        // 接收数据
        ret = recv(socketfd, receLine, sizeof(receLine), 0);
        if (ret == 0) break; // 服务器端退出
        else if (ret == -1) { error(1, errno, "recv"); }
        printf("recv is %s\n", receLine); // 输出接收到的数据
        
        // 发送数据
        char* charRet = fgets(sendLine, MAX_LINE, stdin);
        if (charRet == NULL) break;
        ret = send(socketfd, sendLine, strlen(sendLine) + 1, 0);
        if( ret == 0 ) break; // 服务器端断开连接
        else if( ret == -1) { error(1, errno, "send"); }
    }

    close(socketfd); // 关闭套接字

    return 0;
}
