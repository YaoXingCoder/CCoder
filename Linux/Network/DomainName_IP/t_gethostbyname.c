/*************************************************************************
    > File Name: t_gethostbyname.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月19日 星期五 20时58分45秒
    > Mail: JiaZiChunQiu@163.com
    > Title: gethostbyname, 通过域名获取到IP地址, 并输出IP(点分十进制)到终端
    > Content:
 ************************************************************************/

#include <my_header.h>
// gethostbyname
#include <netdb.h>
// inet_ntop
#include <arpa/inet.h>

#define ADDR_SIZE 128

int main (int argc, char* argv[]) {
    ARGS_CHECK(argc, 2); // 命令行参数足不足2
    
    // 获得hostent结构体
    struct hostent *pHost = gethostbyname(argv[1]);
    ERROR_CHECK(pHost, NULL, "gethostbyname is NULL");

    printf("h_name is %s\n", pHost->h_name); // 真是主机名称
    for(int i = 0; pHost->h_aliases[i] != NULL; i++) {
        printf("h_aliases_%d is %s\n", i, pHost->h_aliases[i]); // 别名列表
    }
    printf("h_addrtype is %d\n", pHost->h_addrtype); // ip地址类型
    printf("h_lenght is %d\n", pHost->h_length); // ip长度
    char buff[ADDR_SIZE] = {0};
    for(int i = 0; pHost->h_addr_list[i] != NULL; i++) {
        memset(buff, 0, ADDR_SIZE);
        inet_ntop(pHost->h_addrtype, pHost->h_addr_list[i], buff, sizeof(buff));
        printf("h_addr_list_%d is %s\n", i, buff); 
    }

    printf("AF_INET is %d\n AF_INET6 is %d\n", AF_INET, AF_INET6);

    return 0;
}
