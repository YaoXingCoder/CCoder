/*************************************************************************
    > File Name: bussiness.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 22时52分21秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 对客户端的消息接收处理和子线程的任务类型判断
    > Content:
    >   1.客户端信息头处理
    >   2.客户端子线程类型判断分配
    >   3.日志消息记录函数
    >   4.命令枚举类的映射
 ************************************************************************/

#include "thread_pool.h"
#include "linked_list.h"
#include "user.h"

#define SERVER_LOG_PAHT "/home/coder/CLearning/Linux/Cloud_Disk_Server_Version/Cloud_Disk_Server_2/log/cloud_server" /* 日志存储相对路径 相对于程序执行的server */
#define LOG_BUFF_SIZE 4096

extern ListNode* userList;

/* 根据客户端发送的数据进行相关判断, 是文件上传还是命令, 并将该任务添加到队列中 */
void handleMessage(int sockfd, int epfd, task_queue_t* que){

    /* 获取数据长度 
     * 消息格式统一为
     * task_t 格式: 长度 + 命令类型 + 内容
     * */
    int length = -1;
    int ret = recvn(sockfd, &length, sizeof(length));
    if ( ret == 0 ) { goto end; }
    printf("\n\n====handleMessage====\nrecv length is %d\n", length);

    /* 消息类型 */
    CmdType cmdType = -1;
    ret = recvn(sockfd, &cmdType, sizeof(cmdType));
    if ( ret == 0 ) { goto end; }
    printf("recv cmd type: %d\n", cmdType);

    /* 创建任务节点 */
    task_t* ptask = (task_t*)calloc(1, sizeof(task_t));
    ptask->peerfd = sockfd;
    ptask->epfd = epfd;
    ptask->type = cmdType;

    /* length > 0 客户端有数据传送 */
    if ( length > 0 ) {
        ret = recvn(sockfd, ptask->data, length); /* 根据length, 获取消息内容 */ 
        if (ret > 0) {
            /* 因为上传任务, 客户端会频繁的发送消息, 所以先断掉主线程的监听 */
            if ( ptask->type == CMD_TYPE_PUTS ) { delEpollReadfd(epfd, sockfd); } //上传文件, 暂时从epoll中删除监听 
            taskEnque(que, ptask); // 在任务队列中添加任务
        }
    }
    /* length == 0 表示客户端只是发送命令 */ 
    else if ( length == 0 ) { 
        taskEnque(que, ptask);
    } // 添加任务 
 
end:
    /* 客户端断开连接 */
    if (ret == 0) {
        printf("\nconn %d is closed.\n", sockfd);
        delEpollReadfd(epfd, sockfd);
        close(sockfd);
        deleteNode2(&userList, sockfd);
    }
}

/* 子线程调用 */
void doTask(task_t * task) {
    assert(task);
    record_log(task); /* 任务执行记录 */

    /* 命令处理 */
    switch(task->type) {
    case CMD_TYPE_PWD:              pwdCommand(task);           break; // 1
    case CMD_TYPE_CD:               cdCommand(task);            break; // 2
    case CMD_TYPE_LS:               lsCommand(task);            break; // 3
    case CMD_TYPE_MKDIR:            mkdirCommand(task);         break; // 4
    case CMD_TYPE_RMDIR:            rmdirCommand(task);         break; // 5
    case CMD_TYPE_TREE:             treeCommand(task);          break; // 6
    case CMD_TYPE_NOTCMD:           notCommand(task);           break; // 7
    case CMD_TYPE_PUTS:             putsCommand(task);      
                                    addEpollReadfd(task->epfd, task->peerfd); /* 因为上传时关闭, 结束时再将添加到读就绪 */
                                    break; // 7
    case CMD_TYPE_GETS:             getsCommand(task);          break; // 8

    /* 用户登录 */
    case TASK_LOGIN_SECTION1:       userLoginCheck1(task);      break;
    case TASK_LOGIN_SECTION2:       userLoginCheck2(task);      break;

    /* 用户注册 */
    case TASK_REGISERT_SECTION1:    userRegisterCheck1(task);   break;
    case TASK_REGISTER_SECTION2:    userRegisterCheck2(task);   break;
    }


}

/* 日志记录函数 
 * 通过task获取指定, 拼接后, 输出到指定文件
 * */
void record_log(task_t* pt) {
    /* openlog 打开并写入 */
    if ( access(SERVER_LOG_PAHT, F_OK) != 0) { 
        int ret = open(SERVER_LOG_PAHT, O_CREAT, 0777);
        if ( ret < 0 ) { perror("open log"); return; }
    }
    
    /* 打开日志, 
     * "CLoud_Disk_Server" 日志记录中 标识
     * LOCAL0 为用户自定义 设置了存储路径为log/cloud_server
     * */
    openlog("Cloud_Disk_Server", LOG_PID | LOG_CONS, LOG_LOCAL0);

    /* 获取用户ip */
    user_info_t* user;
    findByPeerfd(userList, pt->peerfd, &user);

    /* 处理命令, 拼接字符串 */
    char log_buff[LOG_BUFF_SIZE] = { 0 };
    sprintf(log_buff, "%s's IP: %s    CMD_TYPE: %s    DATA: %s", 
            user->name,
            user->ip,
            getStrCmdType(pt->type), 
            pt->data);

    /* 写入数据到日志文件 */
    syslog(LOG_INFO, "%s", log_buff);
    
    /* 关闭资源 */
    closelog();
}

 /* 命令枚举类映射, 用于日志类根据cmdtype 获取 字符串
  *
  * 返回值: 
  *     命令正确: 获取命令对应字符串
  *i    命令错误: NULL
  * cmd_t: CmdTpye 枚举值
  * */
char* getStrCmdType(CmdType cmd_t) {
    switch(cmd_t) {
    
    /* 命令 */
    case CMD_TYPE_PWD:                  return "PWD";
    case CMD_TYPE_LS:                   return "LS";
    case CMD_TYPE_CD:                   return "CD";
    case CMD_TYPE_MKDIR:                return "MKDIR";
    case CMD_TYPE_RMDIR:                return "RMDIR";
    case CMD_TYPE_PUTS:                 return "PUTS";
    case CMD_TYPE_GETS:                 return "GETS";
    case CMD_TYPE_NOTCMD:               return "NOTCMD";

    /* 用户登录 */
    case TASK_LOGIN_SECTION1:           return "Login_SECTION_1";
    case TASK_LOGIN_SECTION2:           return "Login_SECTION_2";

    /* 用户注册 */
    case TASK_REGISERT_SECTION1:        return "REGISTER_SECTION1";
    case TASK_REGISTER_SECTION2:        return "REGISTER_SECTION2";

    /* 都不符合则提示 并返回NULL */
    default:                            {
                                            printf("Invaild CMD TYPE\n");
                                            return NULL;
                                        }
    }
}


