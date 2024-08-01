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
    const char* sql_insert = "insert into `Student`(`name`, `s_birth`, `s_sex`) values ('纷纭', '2000-12-12', '男')";
    int ret = mysql_real_query(pconn, sql_insert, strlen(sql_insert));
    if ( ret ) {
        printf("%d : %s\n", mysql_errno(pconn) , mysql_error(pconn));
        return EXIT_FAILURE;
    }else {
        /* 查询写入情况 */
        int rows = mysql_affected_rows(pconn);
        printf("QUERY OK, %d rows has affected.\n", rows);
    }
    mysql_close(pconn);
    return 0;
}
