/*************************************************************************
    > File Name: cmd.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月05日 星期一 20时23分40秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 命令函数
    > Content:
 ************************************************************************/
#include "str_util.h"
#include "thread_pool.h"
#include "user.h"
#include "linked_list.h"

extern ListNode* userList;

#define BUFFER_SIZE 512
#define TRANS_FILE_SIZE 4096
#define CUR_PATH_SIZE 256

/* 获取当前路径
 * 格式: ~(用户根目录)/path/path$ (此处有空格)
 * 参数:
 *      task: 任务节点
 *      path: 传出参数, 上述格式的路径
 * 返回值:
 *      成功: 0
 *      失败: -1
 */
static int getCurPath(task_t* task, char* cur_path) {
    /* 获取服务器当前绝对路径 */
    char pwd[CUR_PATH_SIZE] = { 0 };
    char* pgcwd = getcwd(pwd, sizeof(pwd));
    if ( pgcwd == NULL ) { perror("getcwd"); return -1; }

    /* 获取用户记录记录的绝对路径 */
    user_info_t* user = NULL;
    findByPeerfd(userList, task->peerfd, &user);
    if ( user == NULL ) { printf("user pwd is NULL\n"); return -1; }
    int len_user_path = strlen(user->pwd);
    strcat(cur_path, "\033[0m\033[1;32m~");
    strcat(cur_path, pwd + len_user_path);
    strcat(cur_path, "$ \033[0m");

    return 0;
}

/*
 * 用户的绝对路径, 不是服务器的绝对路径
 * 正常: 切换路径并返回当前的路径
 * 异常: 超出记录用户根路径, 报错
 */
void cdCommand(task_t * task){
    printf("execute cd command.\n");
    char cur_path[CUR_PATH_SIZE] = { 0 }; /* 返回给用户的路径 */

    /* 先保存该改变前路径 */
    char originPath[CUR_PATH_SIZE] = { 0 };
    getcwd(originPath, sizeof(originPath));
    // printf("originPath is %s\n", originPath);

    /* 获取到用户信息节点 */
    user_info_t* user = NULL;
    findByPeerfd(userList, task->peerfd, &user);

    /* 根据用户提供进行目录切换 */ 
    int ret = chdir(task->data); 
    if ( ret < 0 ) { 
        perror("chdir");
        strcat(cur_path, strerror(errno));
        strcat(cur_path, "\n");
        goto end; 
    }
    
    /* 获取当前的工作路径 */
    char pwd[CUR_PATH_SIZE] = { 0 };
    char* pgcwd = getcwd(pwd, sizeof(pwd));
    if ( pgcwd == NULL ) { perror("getcwd"); return; }

    /* 更改后路径超出用户的路径则不变更, 提示用户输入路径有误 */
    if ( strstr(pwd, user->pwd) == NULL ) {
        strcat(cur_path, "Invalid Path.");
        strcat(cur_path, "\n");
        if ( ret < 0 ) { perror("cd Command sendn"); }
        chdir(originPath);
        goto end;
    }

end:
    /* 获取相对于用户的工作路径 */
    getCurPath(task, cur_path);

    /* 发送当前路径给sockfd */
    ret = sendn(task->peerfd, cur_path, strlen(cur_path)); /* 将当前路径发送给用户 */
    if ( ret < 0 ) { perror("sendn"); return; }

    /* 服务器端输出绝对路径 */
    char* abs_pwd = getcwd(NULL, 0);
    printf("cur_path1 absolutely : %s\n", abs_pwd);
    free(abs_pwd);
    return;
}

/* 获取当前的路径
 * 依旧是用户的绝对路径
 */
void pwdCommand(task_t * task) {
    printf("execute pwd command.\n");

    char cur_path[CUR_PATH_SIZE] = { 0 };
    getCurPath(task, cur_path);
    int ret = sendn(task->peerfd, cur_path, strlen(cur_path));
    if ( ret < 0 ) { perror("pwdCommand"); return; }
    
    return; 
}

/* 使用目录流, 遍历当前目录下所有文件
 * 添加所有文件到一个buff中
 * 最后添加上路径发送给客户端
 */
void lsCommand(task_t * task) {
    printf("execute ls command.\n");
    
    /* 打开目录流 */
    DIR* dirp = opendir(".");
    if( dirp == NULL  ) { perror("opendir"); return; };
    
    /* 用户态缓冲 */
    char* dirBuff = calloc(BUFFER_SIZE, sizeof(char));
    if ( dirBuff == NULL ) { 
        perror("calloc");
        return; 
    }
    
    /* 存储文件名 */
    size_t offset = 0;
    struct dirent* pdirent;
    while( (pdirent = readdir(dirp)) != NULL ) {
        if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0) { continue; }
        // sprintf(dirBuff, "%s\t", pdirent->d_name); // 使用 sprintf 来写入 dirBuff，每次都会覆盖之前的内容，从而只保留最后一个文件名。
        
        /* 计算下一个名字能否存进缓冲区 */
        size_t len_name = strlen(pdirent->d_name);
        if ( offset + len_name + 1 >= BUFFER_SIZE ) {
             fprintf(stderr, "Buffer is too small to hold all filenames.\n");
             break;
        }
    
        /* 每次加入前都计算文件名长度, 并定位字符指针*/
        sprintf(dirBuff + offset, "%s\t", pdirent->d_name);
        offset += len_name + 1; /* +1 是因为添加了 \t */
    }

    /* 判断目录是否为空 */
    if (strlen(dirBuff) == 0) {
        strcpy(dirBuff, "Current directory is NULL");
    }

    /* 拼接当前路径后,  发送消息 */
    strcat(dirBuff, "\n");
    getCurPath(task, dirBuff);
    int ret = sendn(task->peerfd, dirBuff, strlen(dirBuff));
    if ( ret < 0 ) { perror("sendn"); } 
    /* printf("dirBuff is %ld：%s\n", strlen(dirBuff), dirBuff); */
    
    /* 关闭资源 */
    closedir(dirp);
    free(dirBuff);
    return;
}

/*
 * 从队列中取出, 其中的buff就是文件名
 * 直接创建文件, 先接受客户端的文件长度
 * 再接收文件
 */
void putsCommand(task_t * task) {
    printf("execute puts command.\n");

    /* 打开文件 */
    int fd = open(task->data, O_WRONLY | O_CREAT | O_TRUNC, 0644); /* 没有则创建文件 */
    if ( fd < 0 ) { perror("open"); return; }

    /* 接收客户端传送的  */
    __off_t len_filecontent = 0;
    int ret = recvn(task->peerfd, &len_filecontent, sizeof(len_filecontent));
    printf("len_filecontent is %ld\n", len_filecontent);

    /* 接收客户端文件 */
    int fds[2];
    ret = pipe(fds);
    if ( ret < 0 ) { perror("pipe"); goto end; }
    long recvedSize = 0; // 已接受大小
    while( recvedSize < len_filecontent ) {
        ret = splice(task->peerfd, NULL, fds[1], NULL, 4096, SPLICE_F_MORE);
        ret = splice(fds[0], NULL, fd, NULL, ret, SPLICE_F_MORE);
        recvedSize += ret;
    }
    printf("recieved completely.\n");

    /* 返回当前路径给客户端 */ 
    char cur_path[CUR_PATH_SIZE] = { 0 };
    getCurPath(task, cur_path);
    ret = sendn(task->peerfd, cur_path, strlen(cur_path));
    if ( ret < 0 ) { perror( "sendn" ); } 

end:
    /* 关闭资源 */
    close(fds[0]);
    close(fds[1]);
    close(fd);
    return;
}

/* 创建目录
 * 先解构获取到的task->buff的字符串
 * 格式为 mkdir name mode
 * */
void mkdirCommand(task_t * task) {
    printf("execute mkdir command.\n");
    char cur_path[CUR_PATH_SIZE] = { 0 };

    /* 获取参数 */
    char* pstrs[3] = { 0 };
    int cnt = 0;
    printf("task->buff is: %s\n", task->data);
    splitString(task->data, " ", pstrs, 3, &cnt);
    // printf("pstrs[0] is %s, pstrs[1] is %s\n", pstrs[0], pstrs[1]);

    /* 将参数转化为所需要的类型 */
    mode_t mode = 0775; // 目录默认 0775
    if ( cnt == 2 ) { sscanf(pstrs[1], "%o", &mode); }

    /* 创建文件, 出错通知客户端 */
    int ret = mkdir(pstrs[0], mode);
    if ( ret < 0 ) {
        perror("mkdir");
        strcat(cur_path, strerror(errno));
        goto end;    
    }

    /* 释放资源, 通知客户端创建成功 */
    freeStrs(pstrs, cnt);
    strcat(cur_path, "mkdir successfully.");

end:
    /* 拼接当前路径返回 */
    strcat(cur_path, "\n");
    getCurPath(task, cur_path);
    ret = sendn(task->peerfd, cur_path, strlen(cur_path));
    if ( ret < 0 ) { perror("mkdir sendn"); }
    
    return;
}

/* 删除目录
 * 并返回当前路径
 * */
void rmdirCommand(task_t * task) {
    printf("execute rmdir command.\n");
    char cur_path[CUR_PATH_SIZE] = { 0 };

    /* 删除 */
    int ret = rmdir(task->data);
    if ( ret < 0 ) {
        perror("rmdir");
        strcat(cur_path, strerror(errno));
        goto end; /* 失败跳转至end, 并拼接当前路径 */ 
    }

    /* 成功 */
    strcat(cur_path, "rmdir successfully.");

end:    
    strcat(cur_path, "\n");
    getCurPath(task, cur_path);
    ret = sendn(task->peerfd, cur_path, strlen(cur_path));
    if ( ret < 0 ) { perror( "sendn" ); }
    return;
}

/* 不是命令处理 */
void notCommand(task_t * task) {
    printf("execute not command.\n");

    /* 不是命令提醒用户 */
    char not_buff[CUR_PATH_SIZE] = { 0 };
    strcat(not_buff, task->data);
    strcat(not_buff, "not find command");

    /* 拼接当前路径 */
    strcat(not_buff, "\n");
    getCurPath(task, not_buff);
    int ret = sendn(task->peerfd, not_buff, strlen(not_buff));
    if ( ret < 0 ) { perror("sendn"); }
}

/* 向客户端发送文件 
 * 并返回当前工作路径
 * 如果是目录则直接提醒客户, 停住传送
 * */
void getsCommand(task_t * task) {
    printf("execute gets command.\n");
    char cur_path[CUR_PATH_SIZE] = { 0 };

    /* 处理task中buff的数据 */
    char* pstrs[3] = { 0 };
    int cnt = 0;
    splitString(task->data, " ", pstrs, 3, &cnt);
    off_t client_size = 0;
    if ( cnt == 2 ) {
        client_size = atoi(pstrs[1]);
        printf("pstrs[0] is %s, pstrs[1] is %s, cnt is %d, client_size is %ld\n", pstrs[0], pstrs[1], cnt, client_size);
    }

    /* 打开文件 */
    int fd = open(pstrs[0], O_RDONLY);
    if ( fd < 0 ) {
        perror("open");
        goto end;
    }

    /* 获取该文件信息中的大小 */
    struct stat st_file;
    memset(&st_file, 0, sizeof(st_file));
    int ret = fstat(fd, &st_file);
    if ( ret < 0 ) { 
        perror("fstat"); 
        goto end;
    }
    /* TODO 文件类型判断不应该在接收文件中, 应在接收文件前判断并确定是否传输还是提醒用户, 客户端同理*/
    off_t file_size = st_file.st_size;

    /* 如果是两个参数 则对文件内指针进行定位 */
    if ( cnt == 2 ) { 
        lseek(fd, client_size, SEEK_SET);
        file_size -= client_size;      
    }

    /* 先发送文件长度 */
    ret = sendn(task->peerfd, &file_size, sizeof(file_size));
    if ( ret < 0 ) { perror("sendn"); goto end; }

    /* 文件传输零拷贝 */
    int fds[2];
    ret = pipe(fds);
    if ( ret < 0 ) { perror("fds"); return; }
    long sendSize = 0;
    while( sendSize < file_size ) {
        ret = splice(fd, NULL, fds[1], NULL, TRANS_FILE_SIZE, SPLICE_F_MORE);
        ret = splice(fds[0], NULL, task->peerfd, NULL, ret, SPLICE_F_MORE);
        if ( ret < 0 ) { perror( "splice" ); goto end; }
        sendSize += ret;
    }
    printf("sendSize is %ld\n", sendSize);

end:
    /* 返回当前路径给客户端 */
    strcat(cur_path, "file send over!\n");
    getCurPath(task, cur_path);
    ret = sendn(task->peerfd, cur_path, strlen(cur_path));
    if ( ret < 0 ) { perror( "sendn" ); } 

    /* 关闭资源 */
    printf("file send over\n");
    close(fds[0]);
    close(fds[1]);
    close(fd);
    freeStrs(pstrs, cnt);
    return;
}

/* 用户登陆验证 */
void userLoginCheck1(task_t* task) {
    printf("userLoginCheck1.\n");

    ListNode* pNode = userList; /* 获取 全局变量 userList */

    /* 有用户在链表, 遍历链表查找与 peerfd想用的用户节点 */
    while(pNode != NULL) {
        user_info_t* user = (user_info_t*)pNode->val;
        if ( user->sockfd == task->peerfd ) {
            /* 拷贝用户名 */
            strcpy(user->name, task->data);
            loginCheck1(user);
            return;
        }

        pNode = pNode->next; /* 下一个节点 */
    }
}

void userLoginCheck2(task_t* task) {
    printf("userLoginCheck2.\n");

    ListNode* pNode = userList; /* 获取 全局变量 userList */

    /* 有用户在链表, 遍历链表查找与 peerfd想用的用户节点 */
    while(pNode != NULL) {
        user_info_t* user = (user_info_t*)pNode->val;
        if ( user->sockfd == task->peerfd ) {
            /* 拷贝加密密文 */
            loginCheck2(user, task->data);
            return;
        }

        pNode = pNode->next; /* 下一个节点 */
    }
}

/* 用户注册 */
void userRegisterCheck1(task_t * task) {
    printf("userRegisterCheck1.\n");

    ListNode* pNode = userList; /* 获取 全局变量 userList */

    while(pNode != NULL) {
        user_info_t * user = (user_info_t *)pNode->val;
        if(user->sockfd == task->peerfd) {
            strcpy(user->name, task->data); /* 将用户名添加到user节点中, 便于register_check1 获取用户名 */
            register_check1(user);    
            return;
        }

        pNode = pNode->next; /* 下个节点 */
    }

    return;
}

void userRegisterCheck2(task_t * task) {
    printf("userRegisterCheck2.\n");

    ListNode* pNode = userList; /* 获取 全局变量 userList */

    while(pNode != NULL) {
        user_info_t * user = (user_info_t *)pNode->val;
        if(user->sockfd == task->peerfd) {
            strcpy(user->encrypted, task->data); /* 将用户的密码密文加入到user节点中, 便于register_check2 获取和处理 */
            register_check2(user);
            return;
        }

        pNode = pNode->next; /* 下个节点 */
    }

    return;
}
