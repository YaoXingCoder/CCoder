/*************************************************************************
    > File Name: sqlpool.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月08日 星期四 09时16分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 数据库结构体, 函数声明
    > Content:
 ************************************************************************/

#ifndef _SQLPOOL_H
#define _SQLPOOL_H

#include <mysql/mysql.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define IP_LEN          16  /* IP */
#define PORT_LEN        5   
#define DBNAME_LEN      64
#define USER_LEN        64
#define PASSWD_LEN      64
#define POOL_MAX_NUMBER 20  /* 最大可连接数量 */

/* 数据库状态 
 * 0 表示连接
 * 1 表示未连接
 * */
typedef enum {
    MYSQL_CONNECT, /* 默认值为0 */
    MYSQL_DISCONN
}CONN_STATUS;

/* 数据库连接结构体 */
typedef struct _DB_NODE{
    MYSQL*          pconn;      /* 数据库结构指针 */
    int             used;       /* 使用标志: 1: 使用 0:未使用 */
    int             index;      /* 在池子中的位置(下标) */
    CONN_STATUS     conn_status; /* 数据库连接状态 */
    pthread_mutex_t mutex;  /* 互斥锁 ？ */
}DB_NODE;

/* 数据库连接池结构体 */
typedef struct _DB_CONN_POOL {
    int         shutdown;                   /* 数据库状态 */
    DB_NODE*    db_pool[POOL_MAX_NUMBER];   /* 池子, 指向数据库连接结构体节点 */
    int         pool_number;                /* 总连接数量 */
    int         busy_number;                /* 已使用数量 */
    char        ip[IP_LEN];                 /* ip */
    char        port[PORT_LEN];             /* port */
    char        db_name[DBNAME_LEN];        /* 数据库名字 */
    char        user[USER_LEN];             /* 数据库用户名 */
    char        passwd[PASSWD_LEN];         /* 密码 */
}DB_CONN_POOL;

typedef enum{
    TB_USER = 1,
    TB_VIRTUAL,
    TB_GLOBAL
}DB_TABLE;

/* 所有表的字段 */
typedef enum{
    /* 用户表字段 */
    USER_ID = 1,
    USER_NAME,
    USER_SALT,
    USER_CRYPTPASSWD,
    USER_PATH,

    /* 虚拟文件表字段 */
    VF_VFB_ID,
    VF_PARENT_ID,
    VF_FILENAME,
    VF_OWNER_ID,
    VF_HASH_VAL,
    VF_FILESIZE,
    VF_TYPE,
    VF_PATH,

    /* 全局文件表字段 */
    GF_FILE_HASH,
    GF_FILE_NAME,
    GF_FILE_SIZE
}TABLE_FIELD;

/* 创建连接池 */
DB_CONN_POOL* db_pool_create(const int connect_pool_num,
                               const char* ip,
                               const char* port,
                               const char* db_name,
                               const char* user,
                               const char* passwd
                               );

/* 连接数据库  */
int create_db_connect(DB_CONN_POOL* dcp, DB_NODE* node);

/* 销毁连接池 */
void db_pool_destroy(DB_CONN_POOL* dcp);

/* 取出连接 */
DB_NODE* get_db_connect(DB_CONN_POOL* dcp);

/* 释放节点
 * 使用标识 used 置 0
 * 连接池忙碌数量 busy_number - 1
 * 解除节点的锁 unlock  node->mutex
 * */
void release_node(DB_CONN_POOL* dcp, DB_NODE* node);

/* 插入数据 到 用户表
 * insert into `user_info`(`uname`, `salt`, `cryptpasswd`, `path_id`) values ('name', 'salt', 'cryptpasswd', path_id)
 * 返回值 受影响的行数
 * uname        插入用户名
 * salt         盐值
 * cryptpasswd  加密后密码
 * path_id      用户路径 int 标识
 * */
int mysql_insert_user(DB_CONN_POOL* dcp,
                           const char* uname,
                           const char* salt,
                           const char* cryptpasswd,
                           const char* path_id);

/* 插入数据 到 虚拟子表
 * insert into `virtual_file`(`parent_id`, `filename`, `owner_id`, `hash_val`, `filesize`, `type`, `path`)
 * values ('parent_id', 'filename', 'owner_id', 'hash_val', 'filesize', 'type', 'path')
 * 返回值 受影响的行数
 * */
int mysql_insert_virtual(DB_CONN_POOL* dcp,
                         const char* parent_id,
                         const char* filename,
                         const char* owner_id,
                         const char* hash_val,
                         const char* filesize,
                         const char* type,
                         const char* path);

/* 插入数据 到 全局文件表
 * insert into `global_file`( `file_hash`, `file_name`, `filesize`) values('file_hash', 'file_name', 'filesize')
 * 返回值 受影响的行数
 * */
int mysql_insert_global(DB_CONN_POOL* dcp,
                        const char* file_hash,
                        const char* file_name,
                        const char* file_size);

/* 单行单列查询 从 用户表 通过
 * select `result` from `table` where `field` = 'name'
 * 返回值为 0: 成功   非0: 失败
 * result       返回值字段
 * table        表名
 * where_field  字段名
 * where_value  字段值
 * res          传出参数, 接收返回的结果字符串
 * */
int mysql_select_t(DB_CONN_POOL* dcp,
                   DB_TABLE table,
                   TABLE_FIELD result,
                   TABLE_FIELD where_field,
                   const char* where_value,
                   char* res);


/* 更新 到 用户表
 * update `table` set `set_field` = 'set_val' where `where_field` = 'where_value'
 * 返回值 受影响的列数
 * table        表名
 * set_field    需要设置的列
 * set_value    设置列值
 * where_field  条件
 * where_value  条件值
 * */
int mysql_update_t(DB_CONN_POOL* dcp,
                   DB_TABLE table,
                   TABLE_FIELD set_field,
                   const char* set_val,
                   TABLE_FIELD where_field,
                   const char* where_value);

/* 删除 从 用户表
 * delete from `table` where `where_filed` = 'where_value'
 * 返回值 受影响的列数
 * table        表名
 * where_filed  条件字段
 * where_value  条件值
 */
int mysql_delete_t(DB_CONN_POOL* dcp,
                   DB_TABLE table,
                   TABLE_FIELD where_field,
                   const char* where_value);

/* 根据表字段枚举值获取对应字符串， 即表字段枚举映射 */
char* getTableField(TABLE_FIELD tb_field);

/* 获取表名字段字符串 */
char* getTableName(DB_TABLE tb_name);

#endif

