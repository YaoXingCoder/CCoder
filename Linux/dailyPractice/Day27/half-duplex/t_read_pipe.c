/* 
Date:2024.7.12
Title:管道使用
Author:JiaZiChunQiu
Content:

 */


#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// error
#include <error.h>
#include <errno.h>
// write
#include <unistd.h>

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    int fdr = open(argv[1], O_RDONLY); // 打开管道，只写
    if (fdr == -1) error(1, errno, "open fdr %s", argv[1]);

    while(1) {
        char buf[50] = {0};
        read(fdr, buf, sizeof(buf));
        printf("read: %s\n", buf);
    }

    return 0;
}

