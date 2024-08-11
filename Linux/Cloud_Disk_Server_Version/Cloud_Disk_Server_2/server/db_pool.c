/*************************************************************************
    > File Name: sqlpool.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月08日 星期四 09时16分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 数据库函数实现
    > Content:
    >   1.池子创建
    >   2.销毁池子
    >   3.获取连接
    >   4.归还连接
    >   5.sql语句
 ************************************************************************/

#include "db_pool.h"

/* 连接数据库
 * 返回值 0: 创建成功 -1: 创建失败
 * 但会不释放数据库节点的空间, 保留以便后边获取连接时再尝试连接
 * */
int create_db_connect(DB_CONN_POOL* dcp, DB_NODE* node){
    if ( dcp->shutdown == 1 ) { return -1; } /* 数据库池为关闭态 */

    /* 创建 MySQL 连接句柄 */
    if( (node->pconn =  mysql_init(NULL)) == NULL) { 
        printf("create db connect is error.\n"); 
        /* free(node); */ 
        return -1; 
    }

    /* 设置连接超时时间为3s */
    int opt = 3;
    int ret = mysql_options(node->pconn, MYSQL_OPT_CONNECT_TIMEOUT, &opt);
    if ( ret != 0 ) {
        printf("connection timeout.\n");
        return -1;
    }

    /* 连接数据库 */
    unsigned int nport = atoi(dcp->port);
    node->pconn = mysql_real_connect(node->pconn, dcp->ip, dcp->user, dcp->passwd, dcp->db_name, nport, NULL, 0);
    if ( node->pconn == NULL ) { 
        printf("failed to connect mysql.\n");
        /* mysql_close(node->pconn); */
        node->conn_status = MYSQL_DISCONN;
        /* free(node); */
        return -1;
    }

    /* 连接成功 */
    node->used = 0;
    node->conn_status = MYSQL_CONNECT; /* 设置已连接 */
    // printf("===============连接建立成功===================\n");
    
    return 0;
}

/* 创建连接池
 * 返回值
 * 成功: 指向堆空间的池结构指针
 * 失败: NULL
 * */
DB_CONN_POOL* db_pool_create(const int connect_pool_num,
                             const char* ip,
                             const char* port,
                             const char* db_name,
                             const char* user,
                             const char* passwd
                            ){
    /* 设置种子, 使后边的获取连接能够随机获取 */
    srand((unsigned int)time(NULL));

    /* 声明返回的连接池变量 */
    DB_CONN_POOL* dcp = NULL;
    int conn_pool_num = connect_pool_num;

    /* 固定总有一个连接 */
    if ( connect_pool_num < 1 ) {
        printf("connect_pool_num < 1, default 1.\n");
        conn_pool_num = 1;
    }

    /* 申请连接池的结构体堆空间 */
    if( (dcp = (DB_CONN_POOL*)calloc(1, sizeof(DB_CONN_POOL))) == NULL ) {
        printf("malloc DB_CONN_POOL error.\n");
        return NULL;
    }

    /* 连接池初始化 */
    dcp->shutdown = 0;   /* 可用状态 */ 
    strcpy(dcp->ip, ip);
    strcpy(dcp->port, port);
    strcpy(dcp->db_name, db_name);
    strcpy(dcp->user, user);
    strcpy(dcp->passwd, passwd);

    /* 如果输入需要连接数 > 给定的值 , 则按给定的值 */
    if ( conn_pool_num > POOL_MAX_NUMBER) { conn_pool_num = POOL_MAX_NUMBER; }

    /* 循环创建数据库连接 */
    for( int i = 0; i < conn_pool_num; ++i ) {

        /* 申请节点的堆空间 */
        dcp->db_pool[i] = (DB_NODE*)calloc(1, sizeof(DB_NODE));
        if ( dcp->db_pool[i] == NULL ) { 
            printf("calloc error.\n");  
            return NULL; 
        }

        /* 失败 */
        // printf("===============创建连接==================\n");
        if ( create_db_connect(dcp, dcp->db_pool[i]) != 0 ) {
            /* 销毁连接池 */
            db_pool_destroy(dcp);
            /* return NULL; */
            continue;
        }

        /* 成功 */
        dcp->db_pool[i]->index = i; /* 更新节点中在连接池中的位置 */
        dcp->pool_number++; /* 连接数量+1 */
        printf("dbconnect %d has created in pool\n", i);
    }

    return dcp; /* 返回指向堆空间的指针结构体指针 */
}

/* 销毁连接池 */
void db_pool_destroy(DB_CONN_POOL* dcp) {
    if ( dcp == NULL ) { return; }

    /* 循环关闭连接句柄, 释放系节点空间 */
    for(int i = 0; i < POOL_MAX_NUMBER; ++i) {
        if ( dcp->db_pool[i] != NULL  ) {  
            mysql_close(dcp->db_pool[i]->pconn);
            pthread_mutex_destroy(&dcp->db_pool[i]->mutex);
            free(dcp->db_pool[i]);
        }
    }

    /* 释放池子的结构体堆空间 */
    free(dcp);
    printf("db_pool has destroyed.\n");
}

/* 取出一个空闲的连接
 * 使用随机值访问池子中的连接节点, 保证访问买个节点的概率相同
 * */
DB_NODE* get_db_connect(DB_CONN_POOL* dcp){
    /* 取出前的判断 */
    if ( dcp == NULL ) { return NULL; }    
    if ( dcp->shutdown == 1 ) { return NULL; }

    int index_rand = rand() % dcp->pool_number; /* 生成随机下标 */
    int i = 0;

    /* 循环对池子进行连接获取 */
    for(; i < dcp->pool_number; ++i ) {
        index_rand = (index_rand + 1) % dcp->pool_number; /* 下标 + 1 */
        /* 对该节点的句柄使用加锁 */
        if ( !pthread_mutex_trylock(&dcp->db_pool[i]->mutex) ) {

            /* 句柄状态为未连接, 尝试连接*/
            if ( dcp->db_pool[i]->conn_status == MYSQL_DISCONN ) {
                if( create_db_connect(dcp, dcp->db_pool[index_rand]) != 0 ) {
                    /* 重新连接失败 */
                    release_node(dcp, dcp->db_pool[index_rand]);
                    continue;
                }
            }

            /* 成功获取, 且状态为连接状态 */
            int ping_res = mysql_ping(dcp->db_pool[index_rand]->pconn);
            /* 状态有效, 但连接不上, 更改状态并释放 */
            if ( ping_res != 0 ) {
                printf("mysql ping error.\n");
                dcp->db_pool[index_rand]->conn_status = MYSQL_DISCONN;
                release_node(dcp, dcp->db_pool[index_rand]);
            } 
            /* 状态有效, 能连接上数据库, 退出循环 */
            else {
                dcp->db_pool[index_rand]->used = 1; /* 标记正在使用 */
                dcp->busy_number++;
                break;
            }
        }
    }

    /* 遍历所有未找到可用连接句柄 */
    if ( i == dcp->pool_number ) { return NULL; }
    else { return dcp->db_pool[index_rand]; }
}

/* 释放连接
 *
 * */
void release_node(DB_CONN_POOL* dcp, DB_NODE* node) {
    node->used = 0;
    dcp->busy_number--;
    pthread_mutex_unlock(&node->mutex);
}

/* 插入数据 到 用户表
 * insert into `user_info`(`uname`, `salt`, `cryptpasswd`, `path_id`) values ('name', 'salt', 'crypt
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
                      const char* path_id){
    /* 获取一个数据库连接 */
    DB_NODE* node = get_db_connect(dcp);

    /* 安全存储 */
    char statement[1024] = { 0 };

    char uname_esc[128] = { 0 };
    char salt_esc[128] = { 0 };
    char cryptpasswd_esc[128] = { 0 };
    char path_id_esc[128] = { 0 };
    mysql_real_escape_string(node->pconn, uname_esc, uname, strlen(uname));
    mysql_real_escape_string(node->pconn, salt_esc, salt, strlen(salt));
    mysql_real_escape_string(node->pconn, cryptpasswd_esc, cryptpasswd, strlen(cryptpasswd));
    mysql_real_escape_string(node->pconn, path_id_esc, path_id, strlen(path_id));

    /* 拼接 */
    snprintf(statement, sizeof(statement),
             "insert into `user_info`(`uname`, `salt`, `cryptpasswd`, `path_id`) values ('%s', '%s', '%s', '%s')",
             uname_esc, salt_esc, cryptpasswd_esc, path_id_esc);

    /* 执行语句 */
    int ret = mysql_real_query(node->pconn, statement, strlen(statement));
    int rows = 0; /* 记录影响的行数 */
    if ( ret ) {
        /* 失败 */
        printf("%d : %s\n", mysql_errno(node->pconn) , mysql_error(node->pconn));
        return -1;
        /* return EXIT_FAILURE; */
    }else {
        /* 成功 */
        rows = mysql_affected_rows(node->pconn);
        printf("Query OK, %d rows has affected.\n", rows);
    }

    /* 归还连接 */
    release_node(dcp, node);

    return rows;
}

/* 插入数据 到 虚拟子表 
 * 返回值
 *      成功: 影响行数
 *      失败: -1
 * insert into `virtual_file`(`parent_id`, `filename`, `owner_id`, `hash_val`, `filesize`, `type`, `path`)
 * values ('parent_id', 'filename', 'owner_id', 'hash_val', 'type', 'path')
 * 返回值 受影响的行数
 * */
int mysql_insert_virtual(DB_CONN_POOL* dcp,
                         const char* parent_id,
                         const char* filename,
                         const char* owner_id,
                         const char* hash_val,
                         const char* filesize,
                         const char* type,
                         const char* path){
    /* 获取一个数据库连接 */
    DB_NODE* node = get_db_connect(dcp);

    /* 安全存储
     * 报错 gcc 提示固定文本部分的长度可能在 139 字节左右
     * insert相关的字符串 strlen 长度为152, 
     * 7 * 127（因为-1是 128为'\0'）空间大小应该为 139 + 7 * 128 = 1028
     * 所以大小为 [139, 1028]
     * */
    char statement[2048] = { 0 };

    char parent_id_esc[128] = { 0 };
    char filename_esc[128] = { 0 };
    char owner_id_esc[128] = { 0 };
    char hash_val_esc[128] = { 0 };
    char filesize_esc[128] = { 0 };
    char type_esc[128] = { 0 };
    char path_esc[128] = { 0 };
    mysql_real_escape_string(node->pconn, parent_id_esc, parent_id, strlen(parent_id));
    mysql_real_escape_string(node->pconn, filename_esc, filename, strlen(filename));
    mysql_real_escape_string(node->pconn, owner_id_esc, owner_id, strlen(owner_id));
    mysql_real_escape_string(node->pconn, hash_val_esc, hash_val, strlen(hash_val));
    mysql_real_escape_string(node->pconn, filesize_esc, filesize, strlen(filesize));
    mysql_real_escape_string(node->pconn, type_esc, type, strlen(type));
    mysql_real_escape_string(node->pconn, path_esc, path, strlen(path));

    /* 拼接 */
    snprintf(statement, sizeof(statement),
             "insert into `virtual_file`(`parent_id`, `filename`, `owner_id`, `hash_val`, `filesize`, `type`, `path`)"
             "values ('%s', '%s', '%s', '%s', '%s', '%s', '%s')",
             parent_id_esc, filename_esc, owner_id_esc, hash_val_esc, filesize_esc, type_esc, path_esc);

    /* 执行语句 */
    int ret = mysql_real_query(node->pconn, statement, strlen(statement));
    int rows = 0; /* 记录影响的行数 */
    if ( ret ) {
        /* 失败 */
        printf("%d : %s\n", mysql_errno(node->pconn) , mysql_error(node->pconn));
        return -1;
        /* return EXIT_FAILURE; */
    }else {
        /* 成功 */
        rows = mysql_affected_rows(node->pconn);
        printf("Query OK, %d rows has affected.\n", rows);
    }

    /* 归还连接 */
    release_node(dcp, node);

    return rows;
}

/* 插入数据 到 全局文件表 
 * insert into `global_file`( `file_hash`, `file_name`, `filesize`) values ('file_hash', 'file_name', 'filesize')
 * 返回值 
 *      成功: 受影响行数
 *      失败: -1
 * file_hash    文件哈希值
 * file_name    文件名
 * filesize     文件大小
 * */
int mysql_insert_global(DB_CONN_POOL* dcp,
                        const char* file_hash,
                        const char* file_name,
                        const char* file_size){
    /* 获取一个数据库连接 */
    DB_NODE* node = get_db_connect(dcp);

    /* 防止安全存储 */
    char statement[512] = { 0 };

    char file_hash_esc[128] = { 0 };
    char file_name_esc[128] = { 0 };
    char file_size_esc[128] = { 0 };
    mysql_real_escape_string(node->pconn, file_hash_esc, file_hash, strlen(file_hash));
    mysql_real_escape_string(node->pconn, file_name_esc, file_name, strlen(file_name));
    mysql_real_escape_string(node->pconn, file_size_esc, file_size, strlen(file_size));

    /* 拼接 */
    snprintf(statement, sizeof(statement),
             "insert into `global_file`( `file_hash`, `file_name`, `file_size`) values ('%s', '%s', '%s')",
             file_hash_esc, file_name_esc, file_size_esc);

    /* 执行语句 */
    int ret = mysql_real_query(node->pconn, statement, strlen(statement));
    int rows = 0; /* 记录影响的行数 */
    if ( ret ) {
        /* 失败 */
        printf("%d : %s\n", mysql_errno(node->pconn) , mysql_error(node->pconn));
        return -1;
        /* return EXIT_FAILURE; */
    }else {
        /* 成功 */
        rows = mysql_affected_rows(node->pconn);
        printf("Query OK, %d rows has affected.\n", rows);
    }

    /* 归还连接 */
    release_node(dcp, node);

    return rows;
}



/* 单行单列查询 从 用户表 通过
 * select `result` from `table` where `field` = 'name'
 * 返回值为
 *      成功: 受影响行数
 *      未查询到: 0
 *      失败: -1
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
                   char* res){
    /* 获取一个数据库连接 */
    DB_NODE* node = get_db_connect(dcp);

    /* 安全存储 */
    char statement[1024] = { 0 };

    /* 获取表名 条件名*/
    const char* result_get = getTableField(result);
    const char* table_name = getTableName(table);
    const char* where_field_get = getTableField(where_field);

    char result_esc[128] = { 0 };
    char table_esc[128] = { 0 };
    char where_field_esc[128] = { 0 };
    char where_value_esc[128] = { 0 };
    mysql_real_escape_string(node->pconn, result_esc, result_get, strlen(result_get));
    mysql_real_escape_string(node->pconn, table_esc, table_name, strlen(table_name));
    mysql_real_escape_string(node->pconn, where_field_esc, where_field_get, strlen(where_field_get));
    mysql_real_escape_string(node->pconn, where_value_esc, where_value, strlen(where_value));

    /* 拼接 */
    snprintf(statement, sizeof(statement),
             "select `%s` from `%s` where `%s` = '%s'",
             result_esc, table_esc, where_field_esc, where_value_esc);

    /* 执行语句 */
    int ret = mysql_real_query(node->pconn, statement, strlen(statement));
    int rows = 0; /* 记录影响的行数 */
    if ( ret ) {
        /* 失败 */
        printf("%d : %s\n", mysql_errno(node->pconn) , mysql_error(node->pconn));
        return -1;
        /* return EXIT_FAILURE; */
    }else {
        /* 成功 */
        MYSQL_RES* pres = mysql_store_result(node->pconn);
        rows = mysql_affected_rows(node->pconn);

        if( pres ) {
            /* 判空 */
            MYSQL_ROW row = NULL;
            row = mysql_fetch_row(pres);
            if ( row == NULL ) { 
                mysql_free_result(pres);
                return rows;
            }
            /* 结果复制到传出参数 */
            if ( res != NULL ) { strcpy(res, row[0]); } 
        }

        mysql_free_result(pres); /* 释放结果集 */
    }

    /* 归还连接 */
    release_node(dcp, node);

    return rows;
}

/* 更新 到 用户表
 * update `table` set `set_field` = 'set_value' where `where_field` = 'where_value'
 * 返回值 
 *      成功: 受影响的列数
 *      失败: -1
 * table        表名
 * set_field    需要设置的列
 * set_val      设置列值
 * where_field  条件
 * where_value  条件值
 * */
int mysql_update_t(DB_CONN_POOL* dcp,
                   DB_TABLE table,
                   TABLE_FIELD set_field,
                   const char* set_val,
                   TABLE_FIELD where_field,
                   const char* where_value){
    /* 获取一个数据库连接 */
    DB_NODE* node = get_db_connect(dcp);

    /* 安全存储 */
    char statement[1024] = { 0 };

    /* 获取表名 字段名 条件名*/
    const char* table_name = getTableName(table);
    const char* set_field_get = getTableField(set_field);
    const char* where_field_get = getTableField(where_field);

    char table_esc[128] = { 0 };
    char set_field_sec[128] = { 0 };
    char set_val_sec[128] = { 0 };
    char where_field_esc[128] = { 0 };
    char where_value_esc[128] = { 0 };
    mysql_real_escape_string(node->pconn, table_esc, table_name, strlen(table_name));
    mysql_real_escape_string(node->pconn, set_field_sec, set_field_get, strlen(set_field_get));
    mysql_real_escape_string(node->pconn, set_val_sec, set_val, strlen(set_val));
    mysql_real_escape_string(node->pconn, where_field_esc, where_field_get, strlen(where_field_get));
    mysql_real_escape_string(node->pconn, where_value_esc, where_value, strlen(where_value));

    /* 拼接 */
    snprintf(statement, sizeof(statement),
             "update `%s` set `%s` = '%s' where `%s` = '%s'",
             table_esc, set_field_sec, set_val_sec, where_field_esc, where_value_esc);

    /* 执行语句 */
    int ret = mysql_real_query(node->pconn, statement, strlen(statement));
    int rows = 0; /* 记录影响的行数 */
    if ( ret ) {
        /* 失败 */
        printf("%d : %s\n", mysql_errno(node->pconn) , mysql_error(node->pconn));
        return -1;
        /* return EXIT_FAILURE; */
    }else {
        rows = mysql_affected_rows(node->pconn);
        printf("Query OK, %d rows has affected.\n", rows);
    }

    /* 归还链接 */
    release_node(dcp, node);

    return rows;
}

/* 删除 从 用户表
 * delete from `table` where `where_filed` = 'where_value'
 * 返回值 
 *      成功: 受影响的列数
 *      失败: -1
 * table        表名
 * where_filed  条件字段
 * where_value  条件值
 */
int mysql_delete_t(DB_CONN_POOL* dcp,
                   DB_TABLE table,
                   TABLE_FIELD where_field,
                   const char* where_value){
    /* 获取一个数据库连接 */
    DB_NODE* node = get_db_connect(dcp);

    /* 安全存储 */
    char statement[512] = { 0 };

    /* 获取表名 字段名 条件名*/
    const char* table_name = getTableName(table);
    const char* where_field_get = getTableField(where_field);

    char table_esc[128] = { 0 };
    char where_field_esc[128] = { 0 };
    char where_value_esc[128] = { 0 };
    mysql_real_escape_string(node->pconn, table_esc, table_name, strlen(table_name));
    mysql_real_escape_string(node->pconn, where_field_esc, where_field_get, strlen(where_field_get));
    mysql_real_escape_string(node->pconn, where_value_esc, where_value, strlen(where_value));

    /* 拼接 */
    snprintf(statement, sizeof(statement),
             "delete from `%s` where `%s` = '%s'",
             table_esc, where_field_esc, where_value_esc);

    /* 执行语句 */
    int ret = mysql_real_query(node->pconn, statement, strlen(statement));
    int rows = 0; /* 记录影响的行数 */
    if ( ret ) {
        /* 失败 */
        printf("%d : %s\n", mysql_errno(node->pconn) , mysql_error(node->pconn));
        return -1;
        /* return EXIT_FAILURE; */
    }else {
        rows = mysql_affected_rows(node->pconn);
        printf("Query OK, %d rows has affected.\n", rows);
    }

    /* 归还链接 */
    release_node(dcp, node);

    return rows;
}


/* 根据user表的枚举值获取对应字符串， 即user枚举映射 */
char* getTableField(TABLE_FIELD tb_field){    
    switch(tb_field){
        /* 用户表字段 */
    case USER_ID:           return "uid";
    case USER_NAME:         return "uname";
    case USER_SALT:         return "salt";
    case USER_CRYPTPASSWD:  return "cryptpasswd";
    case USER_PATH:         return "path_id";

                            /* 虚拟文件表字段 */
    case VF_VFB_ID:         return "vfb_id";
    case VF_PARENT_ID:      return "parent_id";
    case VF_FILENAME:       return "filename";
    case VF_OWNER_ID:       return "owner_id";
    case VF_HASH_VAL:       return "hash_val";
    case VF_FILESIZE:       return "filesize";
    case VF_TYPE:           return "type";
    case VF_PATH:           return "path";

                            /* 全局文件表字段 */
    case GF_FILE_HASH:      return "file_hash";
    case GF_FILE_NAME:      return "file_name";
    case GF_FILE_SIZE:      return "file_size";

    default:                {
                                printf("Invalid Field\n");
                                return NULL;
                            }

    }
}

/* 获取表名字段字符串 */
char* getTableName(DB_TABLE tb_name){
    switch(tb_name) {
    case TB_USER:       return "user_info";
    case TB_VIRTUAL:    return "virtual_file";
    case TB_GLOBAL:     return "global_file";
    default:            {
                            printf("Invalid Table\n");
                            return NULL;
                        }
    }
}

/* 测试 
 * 无视即可
 * */
/* int main(void) { */
/*     DB_CONN_POOL* dcp = db_pool_create(1, "127.0.0.1", "3306", "mydb", "root", "123456"); */
/*     if ( dcp == NULL ) { printf("dcp is NULL"); } */

    /* 测试user插入语句 */
    /* int rows_insert_user = mysql_insert_user(dcp, */ 
    /*                              "root", */ 
    /*                              "$y$j9T$q0Cg0lKGGfOV0Ii1wOFRt0$", */
    /*                              "$y$j9T$q0Cg0lKGGfOV0Ii1wOFRt0$T9oyglrGHkBsN83wgydzokq8er7V.b/oY5cZvHJiRiD", */
    /*                              "0"); */
    /* printf("mysql_insert_usertable rows is %d\n", rows_insert_user); */


    /* 测试virtual插入语句 */
    /* int rows_insert_virtual = mysql_insert_virtual(dcp, */
    /*                             "1", */
    /*                             "user", */
    /*                             "1", */
    /*                             "%$afasdfas", */
    /*                             "123321", */
    /*                             "2", */
    /*                             "../user"); */
    /* printf("mysql_insert_virtual rows is %d\n", rows_insert_virtual); */


    /* 测试global插入数据 */
    /* int rows_insert_global = mysql_insert_global(dcp, "$#$@asdfasdf123123", "123123", "1231232131"); */
    /* printf("mysql_insert_global rows is %d\n", rows_insert_global); */

    /* 测试查询语句 */
    /* char res[128] = { 0 }; */
    /* int rows_select_t = mysql_select_t(dcp, */
    /*                                    TB_USER, */
    /*                                    USER_NAME, */
    /*                                    USER_ID, */
    /*                                    "0", */
    /*                                    res); */
    /* printf("mysql_insert_global rows is %d, res is %s\n", rows_select_t, res); */

    /* 测试更新语句 */
    /* int rows_update_t = mysql_update_t(dcp, */
    /*                                    TB_USER, */
    /*                                    USER_NAME, */
    /*                                    "123", */
    /*                                    USER_ID, */
    /*                                    "2"); */
    /* printf("mysql_update_t rows is %d\n", rows_update_t); */


    /* 测试删除语句 */
    /* int rows_update_t = mysql_delete_t(dcp, */
    /*                                    TB_USER, */
    /*                                    USER_ID, */
    /*                                    "2"); */
    /* printf("rows_update_t is %d\n", rows_update_t); */
    /* db_pool_destroy(dcp); */
    /* return 0; */
/* } */
