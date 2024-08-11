/*************************************************************************
    > File Name: syslog_t.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月07日 星期三 02时23分48秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 日志文件测试
    > Content:
 ************************************************************************/

#include <func.h>
#include <sys/syslog.h>
#include <syslog.h>

int main (int argc, char* argv[]) {
    /* openlog("syslog_t", LOG_PID | LOG_CONS, LOG_USER); */
    openlog("syslog_t", LOG_PID | LOG_CONS, LOG_USER);

    // 记录不同级别的日志
    syslog(LOG_INFO, "This is an informational message.");
    syslog(LOG_WARNING, "This is a warning message.");
    syslog(LOG_ERR, "This is an error message.");

    // 模拟一些操作
    sleep(3);

    // 记录更多日志消息
    syslog(LOG_INFO, "Another informational message.");
    syslog(LOG_ERR, "Another error message.");

    // 关闭日志系统
    closelog();

    return 0;
}
