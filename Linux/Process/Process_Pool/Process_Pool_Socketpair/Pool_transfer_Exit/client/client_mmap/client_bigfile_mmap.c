/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月27日 星期六 23时56分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 客户端实现
    > Content:  接收服务端用户传输的文件
    >   1.并创建文件输出
    >   2.先读取发送过来的文件名字和长度, 创建文件
    >   3.循环接受服务端数据, 文件并输入内容到创建的文件
    >
    >   4.进度条显示

    >   5.内存映射读写
 ************************************************************************/

#include "../../process_pool.h"
#include <bits/pthreadtypes.h>
#include <bits/types/stack_t.h>
#include <complex.h>
#include <dirent.h>
#include <endian.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>


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

    // 用户态数据缓冲
    train_t t_file;
    int len_fileName = 0;

    // 文件名字
    // 先接受文件名字长度
    ret = recv(clientfd, &len_fileName, sizeof(len_fileName), 0); // 接收文件名字长度
    ERROR_CHECK(ret, -1, "len_filename recv");
    printf("the size of fileName is %d\n", len_fileName);

    memset(&t_file, 0, sizeof(t_file));
    t_file.len = len_fileName;

    // 接受名字内容
    ret = recv(clientfd, t_file.buff, len_fileName, 0); // 接收文件名字
    ERROR_CHECK(ret, -1, "recv");
    printf("filename is %s\n", t_file.buff);

    // 创建对应的文件
    int fd = open(t_file.buff, O_RDWR | O_CREAT | O_TRUNC, 0644);
    ERROR_CHECK(fd, -1, "open");

    // 接收文件内容
    // 接收内容长度
    int len_fileContent = 0;
    ret = recv(clientfd, &len_fileContent, sizeof(len_fileContent), 0);
    ERROR_CHECK(ret, -1, "recv");
    printf("the len_fileContent is %d\n", len_fileContent);

    // 进度条
    int segment = len_fileContent / 100; // 先获取百分之长度
    int lastSize = 0;
    
    // 需要先将文件
    ret = ftruncate(fd, len_fileContent);
    ERROR_CHECK(ret, -1, "ftruncate");

    // 直接从管道中读取到文件的映射区, 不再经过用户态缓冲
    char* pMap = mmap(NULL, len_fileContent, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    int recvNum = recv(clientfd, pMap, len_fileContent, MSG_WAITALL); // 需要设置接收len_fileContent长度的数据
    ERROR_CHECK(recvNum, -1, "recv");
    printf("recv from mmap size is %d\n", recvNum);

    return 0;
}
