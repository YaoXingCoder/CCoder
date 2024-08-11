/*************************************************************************
    > File Name: str_util.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 11时51分48秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 字符串工具类头文件
    > Content:
 ************************************************************************/

#pragma once
#include <func.h>

/*
 * 分割字符串
 * @pstr        原字符串
 * @delimiter   分隔符
 * @ptokens     字符产数组首地址
 * @max_tokens  指定最大值
 * @pcount      传出参数, 获取分割后的字符串个数
 */
void splitString (const char* pstr, const char* delimiter, char* ptokens[], int max_tokens, int* pcount);


void freeStrs(char* pstrs[], int count);
