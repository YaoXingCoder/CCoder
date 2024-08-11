/*************************************************************************
    > File Name: config.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 12时40分47秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 将server.conf 配置文件中的 键值对存入 哈希表中
    > Content:
 ************************************************************************/

#include "config.h"

void readConfig(const char* filename, HashTable* ht){
    FILE* fp = fopen(filename, "rw");
    // printf("filename is %s\n", filename);
    if ( fp == NULL ) {
        printf("fopen file %s error.\n", filename);
        return;
    }

    /* 每次读取一行数据, 存放哈希表 */
    char buf[128] = { 0 };
    while( fgets(buf, sizeof(buf), fp) != NULL) {
        char* strs[3] = { 0 }; // 读取分割后在堆中的字符串
        int pcount = 0; // 分割字符串的个数
        splitString(buf, "=", strs, 3, &pcount);
        // printf("pcount is %d\n", pcount);
        // for( int i = 0; i < pcount; i++ ) {
        //     printf("strs[%d] is %s\n", i, strs[i]);
        // }
        // putchar('\n');
        char* value = (char*)calloc(1, strlen(strs[1]) + 1);
        strcpy(value, strs[1]); // strs[0] = key, strs[1] = value;
        insert(ht, strs[0], value); // 插入, 三参数传入strs[1]产生错误, 
                                    // 因为strs[1]为局部变量传入的是地址, 函数结束后该函数中的空间被释放, 所以值变得不确定
                                    // 二参数为什么没问题呢？因为insert中对第二参数时copy的，对三参数时直接指针互相赋值
        freeStrs(strs, pcount);
    }
    fclose(fp);
}
