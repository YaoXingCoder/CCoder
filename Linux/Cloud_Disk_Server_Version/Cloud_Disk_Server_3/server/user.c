/*************************************************************************
    > File Name: user.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 22时18分12秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 用户登录验证
    > Content: 
    >   1.用户名验证
    >   2.密码验证
    >   3.定位到用户的云端空间
    >   4.用户注册
 ************************************************************************/

#include "user.h"
#include "db_pool.h"
#include "thread_pool.h"

extern DB_CONN_POOL* dcp;

/* 从passwd总获取salt */
void get_setting(char* setting, char *passwd) {

    int i, j;
    for(i = 0, i = 0; passwd[i] && j != 4; ++i){
        if ( passwd[i] == '$' ) { ++j; }
    }
    /* 出循环时 i为下标 在第四个的$下个字符处, 因为要复制len带上第四个$, 所以此时 i-1 就是需要复制的长度 */
    strncpy(setting, passwd, i); /* -1 不带随后 salt 的 &(第四个) */
}

/* 
 * 用户名验证 
 * 通过后将salt发回
 * */
void loginCheck1(user_info_t* user){
    printf("loginCheck1.\n");
    train_t t;
    int ret;
    memset(&t, 0, sizeof(t));
    struct spwd* sp = getspnam(user->name); // 根据用户名从/etc/shadow中获取密码
    
    /* 用户不存在 */
    if ( sp == NULL ) {
        t.len = 0;
        t.type = TASK_LOGIN_SECTION1_RESP_ERROR;
        ret = sendn(user->sockfd, &t, 8);
        printf("check1 send %d bytes.\n", ret);
        return;
    }

    /* 用户存在情况 */
    char setting[100] = { 0 };
    strcpy(user->encrypted, sp->sp_pwdp); /* /etc/shadow中的加密密码, 放入用户信息结构体 */
    get_setting(setting, sp->sp_pwdp); // 获取加密产生的salt
    /* printf("login_salt is %s, len is: %ld\n", setting, strlen(setting)); */

    t.len = strlen(setting);
    strncpy(t.buff, setting, t.len); // 将加密产生的salt, 存入信息头
    ret = sendn(user->sockfd, &t, 8 + t.len); // 将salt发送给用户, 以便用户使用其加密密码
    /* printf("check1 send %d bytes.\n", ret); */
}

/* 
 * 密码验证 
 * 存储信息
 * */
void loginCheck2(user_info_t* user, const char* encrypted){
    printf("loginCheck2.\n");
    int ret;
    train_t t;
    memset(&t, 0, sizeof(t));

    /* 验证成功 */
    if (strcmp(user->encrypted, encrypted) == 0) { // 将用户链表节点的密文与client传输的密文比较
        user->status = STATUS_LOGIN; // 更新状态
        t.type = TASK_LOGIN_SECTION2_RESP_OK; // 消息头类型
        
        /* 更改用户路径到 用户的空间 并存入用户信息中*/
        char pwd[128] = { 0 };
        getcwd(pwd, sizeof(pwd));
        char* tmp  = strrchr(pwd, '/');
        int len_tmp = strlen(tmp);
        int len_pwd = strlen(pwd);
        strncpy(user->pwd, pwd, len_pwd - len_tmp + 1); // +1为了带上路径上的 /
        strcat(user->pwd, "user");

        /* 有数据库时根据数据库存储的用户工作空间进行定位 */
        chdir(user->pwd); // 切换到用户的工作空间

        strcpy(t.buff, "\033[0m\033[1;32m~$ \033[0m"); // 将server的路径返回给用户
        t.len = (strlen(t.buff));
        ret = sendn(user->sockfd, &t, 8 + t.len);
    } else {
        /* 登陆失败 */
        t.type = TASK_LOGIN_SECTION2_RESP_ERROR;
        printf("Login failed.\n");
        ret = sendn(user->sockfd, &t, 8);
    }

    printf("check2 send %d bytes.\n", ret);
    return;
}

#define PREFIX "$y$"
#define LEVEL 5 // 加密等级(1-11)，0为默认值

// @zg 

/*  在服务器收到来自客户端的用户名后，判断用户是否存在 
 *  */
void register_check1(user_info_t* user) {
    printf("REGISTER_CHECK_1.\n");

    train_t t;
    int ret = 0;

    /* 查询数据库是否存在该用户 */
    ret = mysql_select_t(dcp, TB_USER, USER_NAME, USER_NAME, user->name, NULL);

    /* 用户已存在, 告知客户端 */
    if ( ret > 0 ) {
        printf("user name is existed.\n");
        t.len = 0;
        t.type = TASK_REGISTER_SECTION1_RESP_ERROR;
        ret = sendn(user->sockfd, &t, 8 + t.len);
        /* printf("check1 send %d bytes\n", ret); */
        return;
    }
    
    /* 用户不存在, 可以创建 生成盐值字段 salt */
    char* setting = crypt_gensalt(PREFIX, LEVEL, NULL, 0);
    /* printf("salt is %s\n", setting); */

    /* 将盐值打包发送给客户端 */
    memset(&t, 0, sizeof(t));
    t.len = strlen(setting);
    t.type = TASK_REGISTER_SECTION1_RESP_OK;
    strncpy(t.buff, setting, t.len);
    ret = sendn(user->sockfd, &t, 8 + t.len);
    
    return;
}

/* 处理用户第二次发送的加密后的 密码密文
 * 密文为 crypt格式：$perfix$options$saltstr$hash
 * salt:                    $y$j9T$E2wU8Ix917S4z4ZHZgcjJ1
 * salt_len:                29
 * 拼接后的密文(encrypted): $y$j9T$E2wU8Ix917S4z4ZHZgcjJ1$XNJXhQOW5rcpLjYnAjqS9F.PDAMinyDInD3pnV/Lb4.
 * encrypted_len:           73
 * 后边hash 为用户密码的哈希处理
 * */
void register_check2(user_info_t* user) {
    printf("REGISTER_CHECK_2.\n");

    int ret = 0;
    train_t t;

    /* 获取 setting 值 */
    char setting[32]= {0};
    get_setting(setting, user->encrypted); /* 从客户传输的buff中, 获取加密密文的盐值 */

    /* 插入用户到user_info表中 */
    int rows = mysql_insert_user(dcp, user->name, setting, user->encrypted, "0");

    /* 给客户端回复一则注册成功的消息 */
    memset(&t, 0, sizeof(t));
    t.len = 0;
    t.type = TASK_REGISTER_SECTION2_RESP_OK;
    t.len = strlen("Registration succeeded");
    strcpy(t.buff, "Registration succeeded");
    ret = sendn(user->sockfd, &t, 8 + t.len);
    printf("send is %d\n", ret);
    
    return;
}
