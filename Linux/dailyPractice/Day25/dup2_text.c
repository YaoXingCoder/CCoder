#include <my_header.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
    ERROR_CHECK(fd,-1,"open");

    printf("start.\n"); // 先printf输出一句话
    
    int temp=dup(STDOUT_FILENO); // 先备份标准输出的文件描述符
    
    dup2(fd, STDOUT_FILENO); // 将标准输出重定向指向文件
    printf("How are you?");
    
    dup2(temp, STDOUT_FILENO); // 将标准输出重新终端
    printf("I'm fine, and you?\n");
    
    dup2(fd, STDOUT_FILENO); // 再将标准输出重定向到文件
    printf("Me too.\n");

    close(fd);
    return 0;
}
