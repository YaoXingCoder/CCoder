/* 
Date:2024.7.12
Title:全双工通信
Author:JiaZiChunQiu
Content:
1.pipe A写入B读取
2.pipe B写入A读取
 */

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// error
#include <error.h>
#include <errno.h>
// bzero
#include <strings.h>
// write
#include <unistd.h>


int main(int argc, char* argv[]) {
    int write_stream = open("1.pipe", O_WRONLY);
    int read_stream = open("2.pipe", O_RDONLY);

    while(1) {
        char buf[60];
        bzero(buf, sizeof(buf));

        // 标准读入，写入到1.pipe
        int read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
        if (read_stdin == 0) break; // 用户按下ctrl+d;终止标准输入
        write(write_stream, buf, read_stdin);

        bzero(buf, sizeof(buf));

        // 读取2.pipe，打印到标准输出
        int read_num = read(read_stream, buf, sizeof(buf));
        if (read_num == 0) {
            printf("对方断开连接\n");
            break;
        }

        printf("UserB said:%s\n", buf);
    }

    close(write_stream);
    close(read_stream);
    return 0;
}

