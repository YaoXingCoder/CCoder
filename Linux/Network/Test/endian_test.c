/*************************************************************************
    > File Name: endian_test.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月18日 星期四 22时38分07秒
    > Mail: JiaZiChunQiu@163.com
    > Tiltle: 测试大端小端
    > Content: 
 ************************************************************************/

#include <my_header.h>

int main() {
    long long long_num = 0x1122334455667788;
    char* p_long = (char*)&long_num;
    printf("long long: %x\n", *p_long);

    int int_num = 0x11223344;
    char* p_int = (char*)&int_num;
    printf("int: %x\n", *p_int);

    return 0;
}
