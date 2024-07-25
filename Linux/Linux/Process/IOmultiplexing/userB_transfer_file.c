/*************************************************************************
    > File Name: userA_FIFO.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月17日 星期三 23时06分03秒
    > Mail: JiaZiChunQiu@163.com
    > Tiltle: 有名管道全双工通信
    > Content: 
    >   1.读打开管道
    >   2.先读取文件的名字大小, int
    >   3.再读取文件的名字
    >   4.读取文件大小long类型, 将创建的文件扩容到大小
    >   5.循环读取文件内容, 显示接收内容大小long类型
    >   6.再根据大小将文件内容写入到文件中
 ************************************************************************/

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// write
#include <unistd.h>

#define MAX_FILENAME 64
#define MAX_FILE 4096


// this is userB
int main (int argc, char* argv[]) {
    // 读打开管道
    int fdr = open("1.pipe", O_RDONLY);

    // 读取文件名长度, 和文件内容
    int len_filename = 0;
    int ret = read(fdr, &len_filename, sizeof(int));
    ERROR_CHECK(ret, -1, "read fdr len_filename");
    char str_filename[MAX_FILENAME] = {0};
    ret = read(fdr, str_filename, len_filename);
    ERROR_CHECK(ret, -1, "read fdr str_filename");

    // 读取文件长度
    long len_fileSize = 0;
    ret = read(fdr, &len_fileSize, sizeof(long));
    ERROR_CHECK(ret, -1, "read len_fileSize");

    // 创建文件夹, 并切换路径到当前目录
    ret = mkdir("cpfile", 0777);
    // ERROR_CHECK(ret, -1, "mkdir");
    ret = chdir("cpfile");
    ERROR_CHECK(ret, -1, "chdir");

    // 创建文件并扩容其大小
    int newfdw = open(str_filename, O_WRONLY|O_CREAT|O_TRUNC, 0664);
    ERROR_CHECK(newfdw, -1, "open newfd");
    ret = ftruncate(newfdw, len_fileSize);
    ERROR_CHECK(ret, -1, "ftruncate");

    // 循环读取管道并写入到文件
    char recvFile[MAX_FILE] = { 0 };
    long len_read = 0;
    sleep(1);
    while( read(fdr, &len_read, sizeof(long)) != 0 ) {
        read(fdr, recvFile, len_read);
        printf("len_read is %ld\n", len_read);
        // printf("recvFile is %s\n", recvFile);
        write(newfdw, recvFile, len_read); 
        memset(recvFile, 0, MAX_FILE);
    }

    // 关闭流
    close(newfdw);
    close(fdr);
    return 0;
}
