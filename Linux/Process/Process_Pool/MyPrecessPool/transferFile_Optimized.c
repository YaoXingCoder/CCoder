/*************************************************************************
    > File Name: transferFile.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月31日 星期三 17时24分46秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 服务端的文件传输, 子进程调用
    > Content:
    >   1.创建文件描述符
    >   因为存在粘包关系, TCP为无边界的协议
    >   2.先传输文件名字相关
    >       2.1.传输文件名字长度
    >       2.2.传输文件名字数据
    >   3.再传输文件内容相关
    >       3.1.传输文件内容大小
    >       3.2.传输文件内容数据
 ************************************************************************/

#include "process_pool.h"

#define FILE_NAME "1.ev4"

int transferFile(const int netfd) {
    int fd = open(FILE_NAME, O_RDONLY);
    if ( fd == -1 ) {
        perror("transferFile open file");
        // return -1;
    }

    /* 1文件名相关 */
    // 1.1文件名长度
    size_t len_filename = strlen(FILE_NAME);
    int ret = send(netfd, &len_filename, sizeof(len_filename), 0);
    if ( ret == -1 ) {
        perror("transferFile send len_filename");
        // return -1;
    }

    // 1.2文件名数据
    char filename[FILE_NAME_SIZE] = { 0 };
    strcpy(filename, FILE_NAME);
    ret = send(netfd, filename, len_filename, 0);
    if ( ret == -1 ) {
        perror("transferFile send filename");
        // return -1;
    }

    /* 2.文件内容相关 */
    // 2.1.文件内容大小获取
    off_t len_filecontent = 0;
    struct stat st_file;
    memset(&st_file, 0, sizeof(st_file));
    ret = fstat(fd, &st_file); // 获取文件相关内容
    len_filecontent = st_file.st_size;

    // 2.2.发送文件内容大小
    ret = send(netfd, &len_filecontent, sizeof(len_filename), 0);
    if ( ret == -1 ) {
        perror("transferFile send len_filecontent");
        // return -1;
    }

    // 2.3.发送文件数据, 正常的循环send发送文件, 但会经过用户态文件的buff_filecontent缓冲
    // int sendSize = 0; // 已经发送的数据大小
    // char buff_filecontent[FILE_CONTENT_SIZE] = { 0 };
    // while (sendSize < len_filecontent) {
    //     ret = read(fd, buff_filecontent, FILE_CONTENT_SIZE);
    //     // ERROR_CHECK(ret, -1, "read");
    //     ret = send(netfd, buff_filecontent, ret, 0);
    //     if ( ret  == -1 ) {
    //         perror("transferFile send buff_filecontent");
    //         // return -1;
    //         break;
    //     }
    //     printf("has sent %d bytes\n", ret);
    //     sendSize += ret;
    //     memset(buff_filecontent, 0, FILE_CONTENT_SIZE);
    // }
    
    // 2.3.1 服务器端传输优化, 内存映射, 不再经过用户态的缓冲
    // char* pMmap = mmap(NULL, len_filecontent, PROT_READ, MAP_PRIVATE, fd, 0);
    // ret = send(netfd, pMmap, len_filecontent, 0);


    // 2.3.2 服务端传输优化, sendfile
    // ret = sendfile(fd, netfd, NULL, len_filename);

    // 2.3.3 splic
    // 创建管道用于splice
    int fds[2];
    pipe(fds);
    
    int sendSize = 0;
    while(sendSize < len_filecontent){
        ret = splice(fd, NULL, fds[1], NULL, 4096, SPLICE_F_MORE);
        ret = splice(fds[0], NULL, netfd, NULL, ret, 0);
        sendSize += ret;
    }

    printf("File transfer complete\n");
    

    // munmap(pMmap, len_filecontent);
    close(fds[0]);
    close(fds[1]);
    close(fd);
    return 0;
}
