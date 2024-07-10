/* 
Date:2024.7.8
Title:Linux系统调用实现文件复制
Author:JiaZiChunQiu
Content:
 */

#include <my_header.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open read");

    int fdw = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    ERROR_CHECK(fdw, -1, "open write");

    char buf[BUFFER_SIZE] = {0};
    ssize_t read_count;
    while((read_count = read(fdr, buf, sizeof(buf))) > 0) {
        write(fdw, buf, read_count);
    }

    // 关闭
    close(fdr);
    close(fdw);
    
    return 0;
}

