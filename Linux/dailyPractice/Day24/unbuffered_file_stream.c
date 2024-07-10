/* 
Date:2024.7.9
Title:无缓冲流文件练习
Author:JiaZiChunQiu
Content:

a. 以 O_RDWR | O_CREAT | O_TRUNC 的方式打开文件 text1。
b. 将文件的大小截断为 40959。
c. 将文件位置偏移到文件末尾。
d. 写入数据 "Hello world"。
e. 使用 fstat 获取 st_blocks (实际占用磁盘的块数)

 */

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// error
#include <error.h>
#include <errno.h>
// write
#include <unistd.h>

void realize(char* path) {
    // 文件描述符
    int fd = open(path, O_RDWR|O_CREAT|O_TRUNC, 0664);
    if (fd == -1) error(1, errno, "realize open %s", path);
   
    // 写入数据
    write(fd, "On my way~", 12);

    // 截断,文件大小比实际大小大，造成文件空洞
    ftruncate(fd, 40959);
    
    //将文件位置偏移到文件末尾
    int off = lseek(fd, 0, SEEK_CUR); // 当前位置
    printf("the filepoint location is %d\n", off);
    off = lseek(fd, 0, SEEK_END); // 移至文件末尾
    printf("the filepoint location is %d\n", off);

    // 再次写入数据
    write(fd, "Hello world", 11);

    // 获取fstat
    struct stat sbuf;
    int ret = fstat(fd, &sbuf);
    if (ret == -1) error(1, errno, "realize fstat %s", path);

    // 输出fstat的部分信息
    printf("number of 512B blocks is %d\n", sbuf.st_blocks);

    // 关闭
    close(fd);
    return;
}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    realize(argv[1]);
    return 0;
}

