/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 20时09分19秒
    > Mail: JiaZiChunQiu@163.com
    > Title: client
    > Content:
 ************************************************************************/

#include "../Thread_Pool.h"

int main (int argc, char* argv[]) {
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "clientfd");

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129");
    printf("serverAddr'ip is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    int ret = connect(clientfd, &serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("client connected server \n");

    /* 文件接收 */
    /* 文件名字长度 和 文件名 */
    int len_filename = 0;
    ret = recv(clientfd, &len_filename, sizeof(len_filename), 0);
    ERROR_CHECK(ret, -1, "recv len_filename");
    char buff_name[1024] = { 0 };
    ret = recv(clientfd, buff_name, len_filename, 0);
    ERROR_CHECK(ret, -1, "recv filename");
    printf("the filename and len_filename is %s, %d", buff_name, len_filename);

    int fd = open(buff_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ERROR_CHECK(fd, -1, "open");

    /* 文件内容长度 和 文件内容 */
    int len_filecontent = 0;
    ret = recv(clientfd, &len_filecontent, sizeof(len_filecontent), 0);
    ERROR_CHECK(ret, -1, "recv len_filecontent");

    int fds[2];
    pipe(fds);
    int recvSize = 0;
    while(recvSize < len_filecontent) {
        ret = splice(clientfd, NULL, fds[1], NULL, 4096, SPLICE_F_MORE);
        ret = splice(fds[0], NULL, fd, NULL, ret, SPLICE_F_MORE);
        recvSize += ret;
    }

    printf("recvFile complete\n");
    close(fds[0]);
    close(fds[1]);
    close(clientfd);

    return 0;
}
