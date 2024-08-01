/*************************************************************************
    > File Name: transfer.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 17时34分23秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 网络间传输文件
    > Content:

 ************************************************************************/

#include "Thread_Pool.h"

/* 通过网络套接字, 与其传输文件 */
int transferFile(const int netfd) {
    /* 读取服务端文件 */
    int fd = open(FILENAME, O_RDONLY);
    if ( fd == -1 ) {
        perror("transfer  transferFile");
        return -1;
    }

    /* 传输文件长度和名字 */
    int len_filename = strlen(FILENAME);
    int ret = send(netfd, &len_filename, sizeof(len_filename), 0);
    if ( ret == -1 ) {
        perror("transfer transferFile send len_filename");
        return -1;
    }

    // 传输名字
    char buff_name[1024] = { 0 };
    strcpy(buff_name, FILENAME);
    ret = send(netfd, buff_name, len_filename, 0);
    if ( ret == -1 ) {
        perror("transfer transferFile send filename");
        return -1;
    }

    /* 传输内容长度 和 内容 */
    int len_filecontent = 0;
    struct stat st_file;
    memset(&st_file, 0, sizeof(st_file));
    ret = fstat(fd, &st_file);
    if ( ret == -1 ) {
        perror("transfer transferFile fstat");
        return -1;
    }
    len_filecontent = st_file.st_size;
    ret = send(netfd, &len_filecontent, sizeof(len_filecontent), 0);
    if ( ret == -1 ) {
        perror("transfer transferFile send len_filecontent");
        return -1;
    }

    // 传输内容, 使用splice
    int fds[2];
    pipe(fds);
    int sendSize = 0;
    while( sendSize < len_filecontent ) {
        ret = splice(fd, NULL, fds[1], NULL, 4096, SPLICE_F_MORE);
        ret = splice(fds[0], NULL, netfd, NULL, ret, SPLICE_F_MORE);
        sendSize += ret;
    }
    printf("splice ret: %d\n", sendSize);
    close(fds[0]);
    close(fds[1]);
    return 0;
}

