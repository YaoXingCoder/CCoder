/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月26日 星期五 19时56分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 客户端实现
    > Content:  接收服务端用户传输的文件
    >   1.并创建文件输出
    >   2.先读取发送过来的文件名字和长度, 创建文件
    >   3.循环接受服务端数据, 文件并输入内容到创建的文件
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
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/* 接收指定长度的数据, 返回已经接受的字节数
 * socketfd, 需要读取的套接字描述符
 * buff, 接收数据的缓冲区
 * len, 需要接受的大小
 * */
int recvn(int socketfd, void* buff, int len) {
    int remainsLen = len; // 剩余需要接受字节数
    char* pbuff = (char*)buff;
    int hasRecv = -1;
    while (remainsLen > 0) {
        hasRecv = recv(socketfd, pbuff, remainsLen, 0);
        if ( hasRecv == 0) { break; }
        else if ( hasRecv < 0 ) {
            perror("recv recvn");
            return -1;
        }

        remainsLen -= hasRecv;
        pbuff += hasRecv;
    }
    return len - remainsLen;
}

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
    int fd = open(t_file.buff, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ERROR_CHECK(fd, -1, "open");

    // 接收文件内容
    // 接收内容长度
    int len_fileContent = 0;
    ret = recv(clientfd, &len_fileContent, sizeof(len_fileContent), 0);
    ERROR_CHECK(ret, -1, "recv");
    printf("the len_fileContent is %d\n", len_fileContent);

    // 循环接受内容
    int totalSize = 0;
    // int len_recvSize = 0;
    while(totalSize < len_fileContent ){
        // 将recv设置为等待读到指定大小数据才不阻塞 MSG_WAITALL
        // recv(clientfd, &len_recvSize, sizeof(len_recvSize), MSG_WAITALL); // 先接受需要接受的信息
        int recvNum = recvn(clientfd, &t_file.len, sizeof(t_file.len));
        memset(&t_file, 0, sizeof(t_file));

        /* 读取并不一定按照所定的那用, 可能会出现差错
         * 极大概率出现 recvNum <= len_recvSize
         * 此时所读取的内容就万全乱序, 不再是 长度+数据
         * */
        // recv无法保证每次读取都是len_recvSize的长度, 因此会导致出错
        // recvNum = recv(clientfd, t_file.buff, len_recvSize, MSG_WAITALL); // 在接收文件内容信息
        recvNum = recvn(clientfd, t_file.buff, FILE_SMALL);
        if ( recvNum < FILE_SMALL ) {
            printf("recvNum is %d\n", recvNum);
        }
        if ( recvNum > 0 ) {
            totalSize += recvNum;
            write(fd, t_file.buff, recvNum);
        }
    }

    return 0;
}
