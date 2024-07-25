/*************************************************************************
  > File Name: tcp_server.c
  > Author: JiaZiChunQiu
  > Created Time: 2024年07月19日 星期五 21时25分52秒
  > Mail: JiaZiChunQiu@163.com
  > Title: 创建服务器端, 开启Listen监听
  > Content:
  >   1.sokcet 获取套接字
  >   2.创建struct sockaddr_in, 确定服务器的地址和端口
  >   3.bind 绑定 ip+port 与 套接字
  >   4.listen 将套接字变为监听模式
  >   5.创建 struct sockaddr_in, 用于确定客户端的地址
  >   6.accept, 从listen中的全连接队列取TCP连接
  >   7.send, 在连接成功, 获取到客户端连接后, 给客户端发送消息
 ************************************************************************/

#include <my_header.h>
// socket, accept
#include <sys/socket.h>
#include <sys/types.h>
// struct sockaddr_in
#include <arpa/inet.h>
// inet_aton
#include <netinet/in.h>
// close
#include <unistd.h>
// signal
#include <signal.h>

#define MAX_LINE 1024

int main (int argc, char* argv[]) {
    signal(SIGINT, SIG_IGN); // 忽略终止程序

    // 创建套接字, 关联socket设备
    int socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    if ( socketfd < 0) { error(1, errno, "socket"); }
    printf("socketfd is %d\n", socketfd); // 套接字值

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

    // 先创建地址结构体接收客户端的地址, 取完成的TCP连接
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t clientAddr_len = sizeof(clientAddr);

    while(1) {
        int acceptfd = accept(socketfd, (struct sockaddr*)&clientAddr, &clientAddr_len); // 从全连接队列获取TCP连接, 阻塞函数
        ERROR_CHECK(acceptfd, -1, "accept");
        printf("acceptfd id is %d\n", acceptfd); // 打印新的套接字值
        printf("clientAddr is %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port)); // 打印获取的IP

        // 给客户端发送数据, 连接成功发送
        char sendLine[MAX_LINE] = { 0 };
        char receLine[MAX_LINE] = { 0 };
        while(1) {
            char* charRet = fgets(sendLine, MAX_LINE, stdin); // fgets阻塞函数
            if (charRet == NULL) break; // 发送NULL, 即关闭发送端
            ret = send(acceptfd, sendLine, strlen(sendLine) + 1, 0); // send不会阻塞
            if (ret == 0) break;
            ERROR_CHECK(ret, -1, "send");

            // 接收客户端数据
            ret = recv(acceptfd, receLine, sizeof(receLine), 0); // 接收数据, 会阻塞
            if ( ret == 0) break;
            else if (ret == -1) { error(1, errno, "recv"); }
            printf("client said %s\n", receLine); // 打印接收的数据
        }

        close(acceptfd); // 关闭accept的套接字
    }

    // sleep(3);
    close(socketfd); // 关闭套接字

    return 0;
}
