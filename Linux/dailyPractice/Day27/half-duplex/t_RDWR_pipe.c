/* 
Date:2024.7.12
Title:半双工通道
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
    int fdrw = open(argv[1], O_RDWR); // 打开管道，只写
    if (fdrw == -1) error(1, errno, "open fdrw %s", argv[1]);
    
    int i = 0; // 记录次数

    while(1) {
        i++;
        write(fdrw, "hello", 5);
        printf("write %d 次 \n", i);
        sleep(5);

        char buf[50] = {0};
        read(fdrw, buf, sizeof(buf));
        printf("read:%s %d次 \n", buf, i);
    }

    return 0;
}

