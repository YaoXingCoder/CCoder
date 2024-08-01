/*************************************************************************
    > File Name: mysql_CAPI.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月01日 星期四 12时32分34秒
    > Mail: JiaZiChunQiu@163.com
    > Title: CAPI_连接数据库
    > Content: 
    >   1.select查询结果集
 ************************************************************************/

#include <my_header.h>
#include <mysql/mysql.h>

int main (int argc, char* argv[]) {
    /* 获取mysql对象 */
    MYSQL conn;
    MYSQL* pconn = mysql_init(&conn); // 初始化连接
    
    /* mysql对象初始化, 并连接 */
    pconn = mysql_real_connect(pconn, "localhost", "root", "123456", "mydb", 0, NULL, 0);
    if ( pconn == NULL ) {
        printf("%d : %s\n", mysql_errno(pconn) , mysql_error(pconn));
        return EXIT_FAILURE;
    }
    printf("conn has connected\n");

    /* 执行sql语句 */
    // const char* sql_insert = "insert into `Student`(`name`, `s_birth`, `s_sex`) values ('纷纭', '2000-12-12', '男')";
    const char* sql_select = "select * from `Student`";
    int ret = mysql_real_query(pconn, sql_select, strlen(sql_select));

    /* 不能在不处理完上一次的查询后, 执行第二次查询 */
    // ret = mysql_real_query(pconn, sql_select, strlen(sql_select));
    if ( ret ) {
        printf("(%d : %s)\n", mysql_errno(pconn) , mysql_error(pconn));
        return EXIT_FAILURE;
    }else {
        /* 读取数据 */
        // MYSQL_RES* pres = mysql_store_result(pconn); // 结果集存储在客户端
        MYSQL_RES* pres = mysql_use_result(pconn); // 不会存储到客户端, 不会真正获取数据, 只是一个结果集的指针
        int rows = mysql_num_rows(pres);  // 这是rows还没有获取数据
        int cols = mysql_num_fields(pres);
        printf("rows: %d, cols %d\n", rows, cols);
        if ( pres ) {
            /* 读取结果集的列信息 */
            MYSQL_FIELD* pfield = NULL;
            while((pfield = mysql_fetch_field(pres)) != NULL) {
                printf("%s\t", pfield->name); // 列名
            }
            printf("\n");

            /* 读取结果集的每一行数据 */
            MYSQL_ROW prow = NULL;
            // 调用一次获取一行, mysql_fetch_row这时才能获取数据
            while((prow = mysql_fetch_row(pres)) != NULL) {
                for(int i = 0; i < cols; ++i) {
                    printf("%s\t", prow[i]);
                }
                printf("\n");
            }
        }
        mysql_free_result(pres); // 释放res结构体空间
    }
    mysql_close(pconn);
    return 0;
}
