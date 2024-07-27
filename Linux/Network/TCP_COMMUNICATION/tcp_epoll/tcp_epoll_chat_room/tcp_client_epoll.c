/*************************************************************************
    > File Name: tcp_client_select.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月20日 星期六 21时23分24秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 使用 select 多路复用, 实现两端的自由通信
    > Content:
    >   1.创建套接字 -> 创建地址结构体(服务端IP) -> connect 连接服务端 -> send/recv 收发消息 -> close 关闭套接字
    >   2.创建用户缓冲, 分别接收发送数据
    >   3.创建 select 监听集合, 循环重置监听集合
    >   4.循环获取返回的读就绪集合, 并做相应的操作
 ************************************************************************/

#include <my_header.h>
// socket
#include <sys/socket.h>
// struct sockaddr_in
#include <arpa/inet.h>
#include <netinet/in.h>
// selcet 
#include <sys/select.h>
// close
#include <unistd.h>

#define MAX_LINE 1024

int main (int argc, char* argv[]) {
    // 创建套接字
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socketfd, -1, "socket");

    // 创建ip结构体
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(8080);
    clientAddr.sin_addr.s_addr = INADDR_ANY;
    
    // 使用 connect 连接服务端
    int ret = connect(socketfd, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("link successfully~~~\n");

    // 创建用户缓冲
    char recvLine[MAX_LINE] = {0};
    char sendLine[MAX_LINE] = {0};

    // 创建读就绪监听集合
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(STDIN_FILENO, &readSet);
    FD_SET(socketfd, &readSet);
    int maxfd = socketfd > STDIN_FILENO ? socketfd : STDIN_FILENO;

    // while循环读写
    while(1) {
        fd_set backSet = readSet;

        ret = select(maxfd + 1, &backSet, NULL, NULL, NULL);
        if ( ret == 0) { printf("overrunning time~~~\n"); }
        ERROR_CHECK(ret, -1, "select");

        // 标准读就绪
        if (FD_ISSET(STDIN_FILENO, &backSet)){
            memset(sendLine, 0, MAX_LINE);
            int readNum = read(STDIN_FILENO, sendLine, MAX_LINE);
            if ( readNum == 0 ) { break; }
            ERROR_CHECK(readNum, -1, "read");
            int sendNum = send(socketfd, sendLine, readNum, 0);
            ERROR_CHECK(sendNum, -1, "send");
        }

        // recv套接字读就绪
        if (FD_ISSET(socketfd, &backSet)) {
            memset(recvLine, 0, MAX_LINE);
            int recvNum = recv(socketfd, recvLine, MAX_LINE, 0);
            if (recvNum == 0) { break; }
            ERROR_CHECK(recvNum, -1, "recv");
            printf("server said is %s\n", recvLine);
        }

    }   
    
    // 关闭流
    close(socketfd);

    return 0;
}
