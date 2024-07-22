/*************************************************************************
    > File Name: userA_FIFO.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月17日 星期三 23时06分03秒
    > Mail: JiaZiChunQiu@163.com
    > Tiltle: 有名管道全双工通信
    > Content: 
    >   1.编写程序 A 和 B。
    >   2.因为管道是字节流, 是没有边界的, 所以文件名字, 文件内容, 都需要实现读取并计算好
    >   3.且双方要实现规定好接收顺序, 以防数据读取出现错乱

    >   4.A 负责将文件的名字, 长度和内容通过管道发送 B
    >   5.B 需要新建一个目录/文件, 并将该文件存储起来
 ************************************************************************/

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// close
#include <unistd.h>

#define MAX_FILE  4096

/* User A */
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);

    // 打开管道和文件
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open read");
    int fdw = open("1.pipe", O_WRONLY);
    ERROR_CHECK(fdw, -1, "open 1.pipe");

    // 用户数据缓冲
    char sendFile[MAX_FILE] = {0};
    
    // 计算文件名长度, 并写入管道
    int len_filename = strlen(argv[1]);
    strcpy(sendFile, argv[1]);
    printf("sendFile is %s\n", sendFile);
    write(fdw, &len_filename, sizeof(int)); // 先将文件长度发送过去
    write(fdw, sendFile, len_filename); // 将文件名字发送过去

    // 计算文件大小, 将文件大小发送, 便于另一方, 将文件截断到相应的大小
    long len_file = lseek(fdr, 0, SEEK_END);
    lseek(fdr, 0, SEEK_SET); // 重置指针偏移量
    write(fdw, &len_file, sizeof(long));

    // 循环读取文件, 并将读取的内容写入管道
    long len_read = 0;
    while((len_read = read(fdr, sendFile, MAX_FILE)) != 0) {
        write(fdw, &len_read, sizeof(long));
        printf("len_read is %ld\n", len_read);
        // printf("sendFile is %s\n", sendFile);
        write(fdw, sendFile, len_read);
        memset(sendFile, 0, MAX_FILE);
        sleep(1);
    }

    // 关闭通道
    close(fdr);
    close(fdw);
    return 0;
}
