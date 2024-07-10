/*************************
Date:2024.7.4
Title:判断一个数是不是丑数
Author:JiaZiChunQiu
Content:
 *************************/

#include <stdio.h>
#include <stdbool.h>

/* 丑数 */
bool isUglyNumber(long long n) {
    if (n == 0) return false;
    while (n != 1) {
        if (n % 2 == 0) n /= 2;
        else if (n % 3 == 0) n /= 3;
        else if (n % 5 == 0) n /= 5;
        else return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    for(int i = 1; i <= 1000; i++) {
        if (isUglyNumber(i)) printf("%d ", i);
    }
    putchar('\n');
    return 0;
}

