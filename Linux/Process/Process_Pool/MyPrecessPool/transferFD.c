/*************************************************************************
    > File Name: transferFD.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月28日 星期日 21时31分55秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 父子进程间传递信息和文件描述符
    > Content:
    >   1.sendFD发送信息和套接字
    >   2.recvFD接收信息和套接字
 ************************************************************************/

#include "process_pool.h"
#include <stdint.h>

int sendFD(const int skpfd, char exitFlag ,const int netfd) {
    //第二簇结构体初始化, 用于父子进程间通信
    // char buff[10] = { 0 };
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = &exitFlag;
    iov.iov_len = sizeof(exitFlag);

    // 第三簇结构体初始化, 附属消息, 这里传输套接字
    size_t len_pcmsg = CMSG_LEN(sizeof(netfd));
    struct cmsghdr* pcmsg = (struct cmsghdr*)calloc(1, len_pcmsg);
    pcmsg->cmsg_len = len_pcmsg;
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    int* pcmsg_data = (int*)CMSG_DATA(pcmsg);
    *pcmsg_data = netfd;

    // 完成msghdr结构体的初始化, sendmsg发送需要的结构体
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg;
    msg.msg_controllen = len_pcmsg;

    // 给进程发送消息
    int ret = sendmsg(skpfd, &msg, 0);
    if ( ret == -1 ) {
        perror("transferFD sendfD sendmsg");
        return -1;
    }
    printf("sendmsg send %d fd\n", ret);
    free(pcmsg);
    return 0;
}

/* netfd为传出参数, 需要调用函数方传入地址, 便于在函数内更改后传出  */
int recvFD(const int skpfd, char* pexitFlag, int* netfd) {
    //第二簇结构体初始化, 用于父子进程间通信
    // char buff[10] = { 0 };
    char exitFlag = 0;
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = &exitFlag;
    iov.iov_len = sizeof(exitFlag);

    // 第三簇结构体初始化, 附属消息, 这里传输套接字
    size_t len_pcmsg = CMSG_LEN(sizeof(netfd));
    struct cmsghdr* pcmsg = (struct cmsghdr*)calloc(1, len_pcmsg);
    pcmsg->cmsg_len = len_pcmsg;
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    // 完成msghdr结构体的初始化, sendmsg发送需要的结构体
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg;
    msg.msg_controllen = len_pcmsg;

    // 给进程发送消息
    int ret = recvmsg(skpfd, &msg, 0);
    if ( ret == -1 ) {
        perror("transferFD recvfD recvmsg");
        return -1;
    }
    *netfd = *(int*)CMSG_DATA(pcmsg);
    *pexitFlag = exitFlag;
    printf("recvmsg receive %d bytes data\n", ret);
    free(pcmsg);
    return 0;
}
