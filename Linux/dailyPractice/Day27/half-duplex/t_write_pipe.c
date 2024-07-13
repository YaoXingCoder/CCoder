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
    int fdw = open(argv[1], O_WRONLY); // 打开管道，只写
    if (fdw == -1) error(1, errno, "open fdw %s", argv[1]);

    while(1) {
        write(fdw, "hello", 5);
        printf("write once \n");
        sleep(5);
    }

    return 0;
}

