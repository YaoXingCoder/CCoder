/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月05日 星期一 10时38分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 用户端函数实现
    > Content:
    >   1.初始化客户端
    >   2.用户名和密码发送验证
    >   3.命令解析
    >   4.文件传输
 ************************************************************************/

#include "client.h"
#include "str_util.h"

int tcpConnect(const char * ip, unsigned short port) {
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( clientfd < 0 ) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if ( ret < 0 ) {
        perror("connect");
        close(clientfd);
        return -1;
    }
    return clientfd;
}

int recvn(int sockfd, void * buff, int len){
    int left = len;
    char* pbuff = (char*)buff;
    int ret = 0;
    while( left > 0 ) {
        ret = recv(sockfd, pbuff, left, 0);
        if ( ret == 0 ) { break; }
        else if ( recv < 0 ) {
            perror("recv");
            return -1;
        }
        left -= ret;
        pbuff += ret;
    }
    return len - left;
}

int sendn(int sockfd, const void * buff, int len) {
    int left = len;
    char* pbuff = (char*)buff;
    int ret = 0;
    while( left > 0 ) {
        ret = send(sockfd, pbuff, left, 0);
        if ( ret < 0 ) { 
            perror("send\n");
            return -1;
        }
        left -= ret;
        pbuff += ret;
    }
    return len - left;
}

static int userLogin1(int sockfd, train_t* t);
static int userLogin2(int sockfd, train_t* t);

/* 第一次与服务端交换username */
static int userLogin1(int sockfd, train_t* pt) {
    train_t t;
    memset(&t, 0, sizeof(t));
    while(1) {
        printf(USER_NAME);
        fflush(stdout);
        char user[20] = { 0 };
        int ret = read(STDIN_FILENO, user, sizeof(user));
        user[ret - 1] = '\0';

        /* 初始化消息头, 第一次发送给服务器 */
        t.len = strlen(user);
        t.type = TASK_LOGIN_SECTION1;
        strncpy(t.buff, user, t.len);
        ret = sendn(sockfd, &t, 8 + t.len);

        /* 接收客户端回应 */
        memset(&t, 0, sizeof(t));
        ret = recvn(sockfd, &t.len, sizeof(t.len));
        ret = recvn(sockfd, &t.type, sizeof(CmdType));
        
        if (t.type == TASK_LOGIN_SECTION1_RESP_ERROR) {
            printf("\nuser name not exist.\n");
            continue;
        }

        /* 接收salt */
        ret = recvn(sockfd, t.buff, t.len);
        break;
    }

    memcpy(pt, &t, sizeof(t));
    return 0;
}

static int userLogin2(int sockfd, train_t* pt) {
    int ret;
    train_t t;
    memset(&t, 0, sizeof(t));

    while(1) {
        char* passwd = getpass(PASSWORD);
        char* encrytped = crypt(passwd, pt->buff);
        /* printf("crypt ——》 satl + passwd is %s, len is %ld\n", encrytped, strlen(encrytped)); */
        
        /* 发送加密后密文给客户端 */
        t.len = strlen(encrytped);
        t.type = TASK_LOGIN_SECTION2;
        strncpy(t.buff, encrytped, t.len);
        ret = sendn(sockfd, &t, 8 + t.len);

        /* 等待客户端响应 */
        memset(&t, 0, sizeof(t));
        ret = recvn(sockfd, &t.len, sizeof(t.len));
        ret = recvn(sockfd, &t.type, sizeof(CmdType));
        if ( t.type == TASK_LOGIN_SECTION2_RESP_ERROR ) {
            printf("\nsorry, password is not correct.\n");
            continue;
        }else {
            ret = recvn(sockfd, t.buff, t.len);
            printf("\nLogin Success.\n");
            fprintf(stderr, "%s", t.buff); // 打印出当前目录
            break;
        }
    }
    return 0;
}

int userLogin(int sockfd) {
    /* int ret; */
    train_t t;
    memset(&t, 0, sizeof(t));
    userLogin1(sockfd, &t);
    userLogin2(sockfd, &t);
    return 0;
}

/* 解析命令
 * 参数：
 * input 用户输入的字符串
 * len 字符串的长度
 * pt 指向train_t的结构体, 用于传输消息
 * */
int parseCommand(const char * input, int len_input, train_t * pt){
    // printf("input is %s\n", input);
    char* pstrs[10] = { 0 }; // 最多10组数据
    int cnt = 0;
    splitString(input, " ", pstrs, 10, &cnt);
    // printf("pstrs[0] is %s, pstrs[1] is %s\n", pstrs[0], pstrs[1]);
    pt -> type = getCommandType(pstrs[0]); // 根据字符串获取相应的type
    printf("pt->type is %d\n", pt->type);

    /* 命令格式 暂时只有 1.cmd  2.cmd content */
    if ( cnt == 2 ) {
        pt->len = strlen(pstrs[1]);
        strncpy(pt->buff, pstrs[1], pt->len);
    }

    if ( cnt == 3 ) {
        int len_pstrs1 = strlen(pstrs[1]);
        strncpy(pt->buff, pstrs[1], len_pstrs1); // 指令的参数传入t.buff
        // printf("pstrs[1] is :%s, %d\n", pstrs[1], len_pstrs1);

        // 传入第二个数据
        int len_pstrs2 = strlen(pstrs[2]);
        strcat(pt->buff, " ");
        strcat(pt->buff, pstrs[2]);
        // printf("pstrs[2] is :%s, %d\n", pstrs[2], len_pstrs2); 

        pt->len = strlen(pt->buff);
    }
    printf("pt->buff is :%s, %d\n", pt->buff, pt->len);

    freeStrs(pstrs, cnt);
    return 0;
}

/* 获取字符串对应命令的枚举类
 * 
 * */
int getCommandType(const char * str){
    if (!strcmp(str, "pwd"))        return CMD_TYPE_PWD;
    else if (!strcmp(str, "ls"))    return CMD_TYPE_LS;
    else if (!strcmp(str, "cd"))    return CMD_TYPE_CD;
    else if (!strcmp(str, "mkdir")) return CMD_TYPE_MKDIR;
    else if (!strcmp(str, "rmdir")) return CMD_TYPE_RMDIR;
    else if (!strcmp(str, "puts"))  return CMD_TYPE_PUTS;
    else if (!strcmp(str, "gets"))  return CMD_TYPE_GETS;
    else if (!strcmp(str, "tree"))  return CMD_TYPE_TREE;
    else return CMD_TYPE_NOTCMD;
}

 /* 执行上传文件操作 */
void putsCommand(const int sockfd, const train_t* pt){
    // printf("\n\n===============putsCommand=================\n");

    /* 打开文件 */
    int fd = open(pt->buff, O_RDONLY);
    if ( fd < 0 ) { perror("open"); return; }

    /* 获取文件大小 */
    struct stat st_file;
    memset(&st_file, 0, sizeof(st_file));
    int ret = fstat(fd, &st_file);
    if ( ret < 0 ) { perror("fstat"); close(fd);  return; }
    ret = sendn(sockfd, &st_file.st_size, sizeof(st_file.st_size));
    if ( ret < 0 ) { perror("sendn"); close(fd);  return; }

    /* 文件传输优化 */
    int fds[2];
    ret = pipe(fds);
    if ( ret < 0 ) { perror("pipe"); close(fd);  return; }
    long sendSize = 0;
    while(sendSize < st_file.st_size) {
        ;ret = splice(fd, NULL, fds[1], NULL, TRANS_FILE_SIZE, SPLICE_F_MORE);
        ret = splice(fds[0], NULL, sockfd, NULL, ret, SPLICE_F_MORE);
        sendSize += ret;
    }

    /* 关闭资源 */
    sleep(1); /* 等待服务器读取 */
    printf("file send over.\n");
    close(fds[0]);
    close(fds[1]);
    close(fd);
    return;
}

/* 接收服务器传输的文件 
 * 
 * */
void getsCommand(const int sockfd, const train_t* pt){

    /* 处理pt->中buff的信息*/
    char* pstrs[3] = { 0 };
    int cnt = 0;
    splitString(pt->buff, " ", pstrs, 3, &cnt);
    off_t curr_size = 0;
    /* 存在该文件, 将该文件的大小转换为整型 */
    if ( cnt == 2 ) {
        curr_size = atoi(pstrs[1]);
        printf("pstrs[0] is %s, pstrs[1] is %s, cnt is %d, client_size is %ld\n", pstrs[0], pstrs[1], cnt, curr_size);
    }

    /* 打开文件 不存在则创建 */
    int fd = open(pstrs[0], O_WRONLY | O_CREAT, 0664);
    if ( fd < 0 ) { perror("open"); return; }

    /* 1.先接收文件大小 */
    __off_t filecontent = 0;
    int ret = recvn(sockfd, &filecontent, sizeof(filecontent));
    printf("filecontent is %ld\n", filecontent);
    if ( ret < 0 ) { perror("sendn"); close(fd);  return; }

    /* 如果文件存在, 则对文件进行重定位*/
    if ( cnt == 2 ) { lseek(fd, curr_size, SEEK_SET); }

    /* 文件传输优化 */
    int fds[2];
    ret = pipe(fds);
    if ( ret < 0 ) { perror("pipe"); close(fd);  return; }
    long recvSize = 0;
    while(recvSize < filecontent) {
        ret = splice(sockfd, NULL, fds[1], NULL, TRANS_FILE_SIZE, SPLICE_F_MORE);
        ret = splice(fds[0], NULL, fd, NULL, ret, SPLICE_F_MORE);
        if ( ret < 0 ) { perror("splice"); goto end; }
        recvSize += ret;
    }

end:
    /* 释放资源 */
    /* printf("file recv over.\n"); */
    close(fds[0]);
    close(fds[1]);
    close(fd);
    freeStrs(pstrs, cnt);
    return;
}


/* 若存在则返回文件大小, 不存在返回-1 */
void file_is_exist(train_t* pt) { 
    /* 判断文件是否存在 */
    /* int fd = open(pt->buff, O_CREAT | O_EXCL, 0644); */
    if ( access(pt->buff, F_OK) != 0 ) { /* 返回值>0, 文件不存在 */ 
        printf("the file is not existed\n");
        return;
    }

    /* 获取文件大小 */
    int fd = open(pt->buff, O_WRONLY);
    struct stat st_file;
    memset(&st_file, 0, sizeof(st_file));
    fstat(fd, &st_file);

    /* 添加文件大小到消息头中 */
    sprintf(pt->buff + pt->len, " %ld", st_file.st_size);
    /* printf("pt->buff is %s\n", pt->buff); */
    pt->len = strlen(pt->buff); /* 添加后更新消息头的len长度 */

    /* 关闭资源 */
    close(fd);
    return;
}


 /* @zg 用户注册 */
static int userRegister1(int sockfd, train_t *pt);
static int userRegister2(int sockfd, train_t *pt);

int userRegister(int sockfd) {
    /* int ret; */
    train_t t;
    memset(&t, 0, sizeof(t));
    userRegister1(sockfd, &t);
    userRegister2(sockfd, &t);
    return 0;
}

/* 发送用户名给服务器
 * 成功后, 接收服务返回的 salt
 *
 * 返回值: 
 *      成功: 0
 *      失败: 死循环
 * sockfd   客户端网络套接字
 * pt       消息头
 */
static int userRegister1(int sockfd, train_t *pt) {
    printf("\nUSER_REGISTER_1\n");

    train_t t; /* 临时最后赋值给pt */
    memset(&t, 0, sizeof(t));

    while(1) {
        /* 输入信息, 并发送给服务器 */
        printf("please input a valid user name: ");
        fflush(stdout);
        char user[20]= {0};
        int ret = read(STDIN_FILENO, user, sizeof(user));
        user[ret - 1] = '\0'; /* 将输入的最后换行符 \n 变为 '\0' */

        /* 放入消息头中 */
        t.len = strlen(user);
        t.type = TASK_REGISTER_SECTION1;
        strncpy(t.buff, user, t.len);
        ret = sendn(sockfd, &t, 8 + t.len);

        /* 接收信息, 正确则返回需要加密的salt, 否则重新输入 */
        memset(&t, 0, sizeof(t));
        ret = recvn(sockfd, &t.len, sizeof(t.len));
        ret = recvn(sockfd, &t.type, sizeof(t.type));
        if(t.type == TASK_REGISTER_SECTION1_RESP_ERROR) { continue; }

        /* 用户名合法，接收盐值信息 */
        recvn(sockfd, t.buff, t.len);
        break;
    }
    
    /* 放入消息头, 用户用于与密码形成加密*/
    memcpy(pt, &t, sizeof(t));
    /* printf("salt is %s, and is %ld\n", t.buff, strlen(t.buff)); */
    return 0;
}

/* 接受用户输入密码, 将密码和盐值合成密文
 * 将密码的密文发送给服务器
 * 返回值:
 *      成功: 0
 *      失败: 重新输入, 死循环
 * sockfd   用户与服务器 网络套接字
 * pt       消息头
 * */
static int userRegister2(int sockfd, train_t *pt) {
    printf("USER_REGISTER_2.\n");

    int ret = 0;
    train_t t;
    memset(&t, 0, sizeof(t));

    while(1) {
        /* 接收键盘输入密码, 加密处理 */
        char * passwd = getpass(PASSWORD_R);
        char * encrytped = crypt(passwd, pt->buff);
        /* printf("encrytped: %s, len is :%ld\n", encrytped, strlen(encrytped)); */

        /* 写入到消息头, 并发送 */
        t.len = strlen(encrytped);
        t.type = TASK_REGISTER_SECTION2;
        strncpy(t.buff, encrytped, t.len);
        ret = sendn(sockfd, &t, 8 + t.len);

        /* 接收服务器插入成功后 返回的消息 */
        memset(&t, 0, sizeof(t));
        ret = recvn(sockfd, &t, 8 + t.len);
        if (t.type != TASK_REGISTER_SECTION2_RESP_OK) { continue; }  /* 消息头判断, 是否正确, 因为注册, 所以暂时不存在密码错误 TODO 二次验证 */

        printf("%s\n", t.buff);
        break;
    }

    return 0;
}

