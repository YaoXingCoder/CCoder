/*************************************************************************
    > File Name: client_recvFile.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月31日 星期三 19时20分42秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 接收文件传输
    > Content:
 ************************************************************************/

#include "../process_pool.h"
#include <sys/mman.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
    
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "clientfd");

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129");
    
    int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("connected server successfully\n");

    /* 1.接收文件名相关 */
    // 1.1.文件名长度
    size_t len_filename = 0;
    ret = recv(clientfd, &len_filename, sizeof(len_filename),0);
    ERROR_CHECK(ret, -1, "recv len_filename");

    // 1.2.文件名数据
    char buff_filename[FILE_NAME_SIZE] = { 0 };
    ret = recv(clientfd, buff_filename, len_filename, 0);
    ERROR_CHECK(ret, -1, "recv buff_filename");

    // 创建文件
    int fd = open(buff_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    ERROR_CHECK(fd, -1, "open");

    /* 2.接收内容相关 */
    // 2.1.内容大小
    off_t len_filecontent = 0;
    ret = recv(clientfd, &len_filecontent, sizeof(len_filecontent), 0);
    ERROR_CHECK(ret, -1, "recv len_filecontent");

    // 接收内容数据
    // int recvSize = 0;
    // int time = 0;
    // char buff_filecontent[FILE_CONTENT_SIZE] = { 0 };
    // while (recvSize < len_filecontent){
    //     ret = recv(clientfd, buff_filecontent, FILE_CONTENT_SIZE, 0);
    //     ERROR_CHECK(ret, -1, "recv buff_filecontent");
    //     ret = write(fd, buff_filecontent, ret);
    //     ERROR_CHECK(ret, -1, "write");
    //     printf("%d times recv %d bytes\n", ++time, ret);
    //     recvSize += ret;
    //     memset(buff_filecontent, 0, FILE_CONTENT_SIZE);
    // }
        
    // 因为从管道直接映射到文件中, 所以需要将文件扩容到需要接受的数据大小
    ret = ftruncate(fd, len_filecontent);
    ERROR_CHECK(ret, -1, "ftruncate");

    // 2.1 mmap映射传输
    char* pMmap = mmap(NULL, len_filecontent, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    ret = recv(clientfd, pMmap, len_filename, 0);
    ERROR_CHECK(ret, -1, "recv");


    printf("File transfer complete\n");

    munmap(pMmap, len_filecontent);
    close(fd);
    close(clientfd);
    return 0;
}
