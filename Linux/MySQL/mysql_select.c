/*************************************************************************
    > File Name: mysql_CAPI.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月01日 星期四 12时32分34秒
    > Mail: JiaZiChunQiu@163.com
    > Title: CAPI_连接数据库
    > Content:
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
    ret = mysql_real_query(pconn, sql_select, strlen(sql_select));
    if ( ret ) {
        printf("(%d : %s)\n", mysql_errno(pconn) , mysql_error(pconn));
        return EXIT_FAILURE;
    }else {
        /* 读取数据 */
        MYSQL_RES* pres = mysql_store_result(pconn);
        int rows = mysql_num_rows(pres);
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
