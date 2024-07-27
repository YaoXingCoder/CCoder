/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月26日 星期五 19时56分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 客户端实现
    > Content:  接收服务端用户传输的文件
    >   1.并创建文件输出
 ************************************************************************/

#include "../process_pool.h"
#include <time.h>


int main (int argc, char* argv[]) {
    // 创建socket套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");

    // 地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129");
    printf("client request server's ip is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    // connect 连接服务器
    int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("client is connected server\n");


    // 先接受文件长度
    int len_filename = 0;
    ret = recv(clientfd, &len_filename, sizeof(len_filename), 0);
    printf("the size of filename is %d\n", len_filename);
    ERROR_CHECK(ret, -1, "recv len_filename");

    // 接收文件名字
    char filename[100] = {0};
    ret = recv(clientfd, filename, len_filename, 0);
    ERROR_CHECK(ret, -1, "recv filename");
    printf("filename is %s\n", filename);

    // 打开/创建文件
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ERROR_CHECK(fd, -1, "open");

    // 接收文件内容长度
    int len_filecontent = 0;
    ret = recv(clientfd, &len_filecontent, sizeof(len_filecontent), 0);
    ERROR_CHECK(ret, -1, "recv len_filecontent");
    printf("the size of file is %d\n", len_filecontent);

    // 接收文件内容
    char filecontent[FILE_SMALL] = { 0 };
    ret = recv(clientfd, filecontent, len_filecontent, 0);
    ERROR_CHECK(ret, -1, "recv filecontent");
    printf("file content is %s\n", filecontent);

    // 写入文件
    int writeNum = write(fd, filecontent, len_filecontent);
    ERROR_CHECK(writeNum, -1, "write");

    return 0;
}
