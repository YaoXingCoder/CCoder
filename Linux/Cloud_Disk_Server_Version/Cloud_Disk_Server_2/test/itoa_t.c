/*************************************************************************
    > File Name: itoa_t.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月07日 星期三 17时50分09秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 将整数转换为字符串
    > Content:
 ************************************************************************/

#include <my_header.h>

int main (int argc, char* argv[]) {

    int i = 123123;
    char c[64] = {0};
    sprintf(c, "%d", i);
    printf("%s", c);
    putchar('\n');
    sprintf(c + strlen(c), " %s", "asdfv");
    printf("%s\n", c);

    return 0;
}
