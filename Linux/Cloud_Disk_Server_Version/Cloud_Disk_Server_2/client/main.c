/*************************************************************************
    > File Name: main.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月05日 星期一 13时12分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 客户端函数进入
    > Content:
 ************************************************************************/

#include "client.h"

#define BUFF_SIZE 512

int main (int argc, char* argv[]) {
    int clientfd = tcpConnect("127.0.0.1", 8080);
    if ( clientfd < 0 ) { return -1; }
    
    /* 登录 /  注册 */
    char input = '0';
    printf("user register   ------ please input 1\n");
    printf("user login      ------ please input 2\n");
    while(1) {
        printf("please input '1' or '2': ");
        input = getchar(); /* getchar 发生输入操作 刷新标准输出流 */
        if(input == '1' || input == '2'){ break; }
    }

    /* 根据输入值判断 注册 or 登录 */
    switch (input) {
    case '1': userRegister(clientfd);
    case '2': userLogin(clientfd); break;
    /* default: break; */
    }
    /* userLogin(clientfd); // 用户登陆操作 */

    /* 用户接收缓冲 */
    char buf[BUFF_SIZE] = { 0 };

    /* 套接字监听, 以及消息头 */
    fd_set rdset;
    train_t t;
    while( 1 ) {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(clientfd, &rdset);

        int nready = select(clientfd + 1, &rdset, NULL, NULL, NULL);
        // printf("nready:%d\n", nready);
        if (FD_ISSET(STDIN_FILENO, &rdset)){
            memset(buf, 0, sizeof(buf));
            memset(&t, 0, sizeof(t));
            int ret = read(STDIN_FILENO, buf, sizeof(buf));
            if ( ret == 0 ) { printf("byebye.\n"); break; }
            if (strcmp(buf, "\n") == 0) { continue;  } /* 处理回车 */
            /* printf("\nstrlen buf is %ld\n", strlen(buf)); */

            /* 解释命令, 并存入消息头中*/
            buf[strlen(buf) -1] = '\0'; // 将换行符换为 空字符
            // printf("\nstrlen is %ld", strlen(buf));
            parseCommand(buf, strlen(buf), &t); 
            if ( t.type == CMD_TYPE_GETS ) { file_is_exist(&t); }

            /* 发送到客户端 */
            sendn(clientfd, &t, 4 + 4 + t.len); // t.len + t.type + t.buff
            if ( t.type == CMD_TYPE_PUTS ) { putsCommand(clientfd, &t); } /* 如果是文件传输, 则在对服务端进行传输 */
            else if ( t.type == CMD_TYPE_GETS ) { getsCommand(clientfd, &t); }  /* 接收文件 */

        } else if (FD_ISSET(clientfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            recv(clientfd, buf, sizeof(buf) ,0);
            printf("%s", buf);
            fflush(stdout);
        }
    }
    close(clientfd);
    return 0;
}
