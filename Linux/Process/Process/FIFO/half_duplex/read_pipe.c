/*************************************************************************
    > File Name: write_pipe.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月17日 星期三 22时42分10秒
    > Mail: JiaZiChunQiu@163.com
    > Tiltle: 有名管道半双工通信
    > Content: 读端
 ************************************************************************/

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// write
#include <unistd.h>

#define MAX_LINE 1024

int main(int argc, char* argv[]) {
    // 打开管道
    int p1 = open("1.pipe",O_RDONLY);
    if (p1 == -1) { error(1, errno, "open 1.pipe"); }

    // 缓冲字符数组
    char buf[MAX_LINE];
    while(1) {
        int ret = read(p1, buf, MAX_LINE);
        if (ret == -1) { error(1, errno, "read 1.pipe"); }
        else if (ret == 0) break;
        printf("writer said %s\n", buf);
    }

    return 0;
}
