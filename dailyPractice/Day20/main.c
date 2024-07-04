/*************************
Date:2024.7.4
Title:����|����
Author:JiaZiChunQiu
Content:
 *************************/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* һ�������Ƿ������� */
bool isPirme(long long n) {
    if (n < 0) {
        printf("the num is illegal\n");
        return false;
    }
    int k = (int)sqrt((double)n); // ƽ����
    int i = 2;
    for (; i <= k; i++) {
        if (n % i == 0) break;
    } // ���� i > k

    if (i > k) return true;
    else return false;
}

/* ��ӡǰn������ */
long long* generatePrimes(int n) {
    for (int i = 1; i <= n; i++) {
        if (isPirme(i)) printf("%d ", i);
    }
}


/* ���� */
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
    for (int i = 1; i <= 1000; i++) {
        if (isUglyNumber(i)) printf("%d ", i);
    }
    putchar('\n');
    return 0;
}





int main(int argc, char* argv[]) {
    generatePrimes(100);
    putchar('\n');
    return 0;
}
