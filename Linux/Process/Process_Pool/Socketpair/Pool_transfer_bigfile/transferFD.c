/*************************************************************************
    > File Name: transferFD.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月25日 星期四 21时18分04秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 编写 rendFd 和 sendFd 方法, 传输文件描述符
    > Content:
    >   1.
 ************************************************************************/

#include "process_pool.h"
#define MAX_BUFF 1024

int sendFd(int skpfd, int fd) {
    // 完善第二簇信息, 用于skpfd之间的通信使用
    char buff[MAX_BUFF] = "hello"; // 暂时不传送数据
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buff;
    iov.iov_len = sizeof(buff);
    // printf("buff is %s\n", buff);
    
    // 完善第三簇信息, 附属数据缓冲区, 传递文件描述符
    size_t len_cmsg = CMSG_LEN(sizeof(fd)); // 加上要传输的数据后, 该结构体的大小
    // printf("len_cmsg is %ld \n", len_cmsg);
    struct cmsghdr* pcmsg = (struct cmsghdr*)calloc(1, len_cmsg);
    pcmsg->cmsg_len = len_cmsg;
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    int* pcmsg_data = (int*)CMSG_DATA(pcmsg);
    *pcmsg_data = fd;
    // printf("*pcmsg_data is %d\n", *pcmsg_data);

    // 构建msghdr
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg; // 传递文件描述符
    msg.msg_controllen = len_cmsg;

    // 传输msghdr
    ssize_t ret = sendmsg(skpfd, &msg, 0);
    ERROR_CHECK(ret, -1, "sendmsg");
    // printf("sendmsg send %s is %ld bytes.\n", buff, ret);
    free(pcmsg);
    return ret;
}

int recvFd(int skpfd, int* fd) {
    // 完善第二簇信息, 用于skpfd之间的通信使用
    char buff[MAX_BUFF] = { 0 }; // 暂时不传送数据
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buff;
    iov.iov_len = sizeof(buff);
    
    // 完善第三簇信息, 附属数据缓冲区, 接收文件描述符
    size_t len_cmsg = CMSG_LEN(sizeof(fd)); // 加上要传输的数据后, 该结构体的大小
    struct cmsghdr* pcmsg = (struct cmsghdr*)calloc(1, len_cmsg);
    pcmsg->cmsg_len = len_cmsg;
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    // 构建msghdr
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg; // 传递文件描述符
    msg.msg_controllen = len_cmsg;

    // 传输msghdr
    ssize_t ret = recvmsg(skpfd, &msg, 0);
    ERROR_CHECK(ret, -1, "recvmsg");
    // printf("recvmsg %s is %ld bytes.\n",buff, ret);
    int* pcmsg_data = (int*)CMSG_DATA(pcmsg);
    *fd = *pcmsg_data; 
    return ret;
}
