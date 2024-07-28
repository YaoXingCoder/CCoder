/*************************************************************************
    > File Name: transferFile_small.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月26日 星期五 20时57分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 传输文件函数
    > Content:
    >   1.因为tcp通信时字节流的, 字节流无边界
    >   2.所以发送内容前, 应先发送文件的名字和长度, 此时读取长度类型为约定俗成的int
    >   3.再发送文件的内容

    >   4.mmap映射传输, 不再使用用户态的缓冲
 ************************************************************************/

#include "process_pool.h"

#define FILE_NAME "1.ev4"

int transferFile(int peerfd) {
    // 打开需要文件, 读
    int fd = open(FILE_NAME, O_RDONLY);
    ERROR_CHECK(fd, -1, "open");
    
    // 文件名
    // 文件长度 + 文件名
    int len_fileName = 0;
    len_fileName = strlen(FILE_NAME);
    train_t t_file; // 文件结构体
    memset(&t_file, 0, sizeof(t_file));
    t_file.len = len_fileName;
    strcpy(t_file.buff, FILE_NAME);
    int ret = send(peerfd, &t_file, 4 + t_file.len, 0); // 发送文件结构体: 文件长度 + 文件名
    ERROR_CHECK(ret, -1, "send len_fileName + fileName");

    // 获取文件内容大小
    struct stat st_file;
    memset(&st_file, 0, sizeof(st_file));
    ret = fstat(fd, &st_file);
    ERROR_CHECK(ret, -1, "fstat");
    int len_fileSize = st_file.st_size; // 获取内容大小

    // 文件内容
    // 先发送文件内容大小
    ret = send(peerfd, &len_fileSize, sizeof(len_fileSize), 0);
    ERROR_CHECK(ret, -1, "send len_fileSize");
    printf("the file is %s, and size is %d\n", t_file.buff, len_fileSize);
    
    // mmap映射文件并, 发送
    // char* pMap = mmap(NULL, len_fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    // int sendNum = send(peerfd, pMap, len_fileSize, 0);
    // printf("send filecontent size is %d\n", sendNum);

    // sendfile
    // ret = sendfile(peerfd, fd, NULL, len_fileSize);
    // printf("sendfile filecontent size is %d\n", ret);
    
    // splic
    int sendSize = 0;
    int fds[2];
    ret = pipe(fds);
    while( sendSize < len_fileSize ) {
        ret = splice(fd, NULL, fds[1], NULL, 4096 , SPLICE_F_MORE);
        ret = splice(fds[0], NULL, peerfd, NULL, ret, SPLICE_F_MORE);
        sendSize += ret;
    }
    // printf("sendfile filecontent size is %d\n", ret);

    return 0;
}
