/*************************************************************************
    > File Name: str_util.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 12时11分27秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 将字符串，根据提供的分隔符，进行分割；并将每个分割的token放入堆空间的tokens数组中
    > Content:
 ************************************************************************/

#include "str_util.h"

/* max_tokens 是 ptokens数组的 最大大小 */
void splitString(const char* pstrs, const char* delimiter, char* ptokens[], int max_tokens, int* pconut){
    int token_count = 0; // 记录存放token数, 同时是ptokens的数组下标
    char* token = strtok((char*)pstrs, delimiter);
    
    // 保留最后一位给NULL终止符
    while(token != NULL && token_count < max_tokens - 1) {
        char* pstr = (char*)calloc(1, strlen(token) + 1); // 每次申请一个堆空间, 根据每次token分配对应大小的堆空间
        strcpy(pstr, token);
        ptokens[token_count] = pstr; // 保存堆空间的首地址
        token_count++;
        token = strtok(NULL, delimiter);
    }

    ptokens[token_count] = NULL;
    *pconut = token_count;
}

void freeStrs(char* pstrs[], int count) {
    for( int i = 0; i < count; ++i ){
        free(pstrs[i]);
    }
}
