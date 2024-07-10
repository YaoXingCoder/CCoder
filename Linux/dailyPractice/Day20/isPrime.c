/*************************
Date:2024.7.4
Title:素数
Author:JiaZiChunQiu
Content:
 *************************/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* 一个整数是否是素数 */
bool isPirme(long long n){
    if (n < 0) {
        printf("the num is illegal\n");
        return false;
    }
    int k = (int)sqrt((double) n); // 平方根
    int i = 2;
    for (; i <= k; i++) {
        if ( n % i == 0 ) break;
    } // 结束 i > k

    if (i > k) return true;
    else return false;
}

/*一种高效的方法*/
bool isPrime_3(int num){
 //两个较小数另外处理
 if(num == 2 || num == 3)
  return true;
 //不在6的倍数两侧的一定不是质数
 if(num % 6 != 1 && num % 6 != 5)
  return false;

 int i;
 //在6的倍数两侧的也可能不是质数 
 for(i = 2;i <= sqrt(num);i += 6){
  if(num % i == 0 || num % (i + 2) == 0)
   return false;
 } 
 
 //排除所有，剩余的是质数
 return true; 
}



/* 打印前n个素数 */
long long* generatePrimes(int n) {
    for (int i = 1; i <= n; i++) {
        if (isPirme(i)) printf("%d ", i);
    }
}


int main(int argc, char* argv[]) {
    generatePrimes(1000);
    putchar('\n');
    return 0;
}

