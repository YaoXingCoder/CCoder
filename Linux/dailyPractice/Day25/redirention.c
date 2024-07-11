#include <my_header.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    close(STDIN_FILENO);    // 关闭标准输入流的文件描述符
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);
    // 此时文件描述符0已经分配给了新打开的一个文件, 也就是说标准输入被重定向到从文件中读数据
    int a;
    scanf("%d",&a);     // 把文件中的第一个数字读出来
    printf("a = %d\n", a);
    return 0;
}
