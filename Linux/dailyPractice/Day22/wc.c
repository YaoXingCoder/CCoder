/*
Date:2024.7.7
Title:统计一个文本中字符的个数，单词的个数以及行数
Author:JiaZiChunQiu
Content:
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 1024

/* 分析文本 */
static void run(const char* content){
    int charCount = 0;
    int wordCount = 0;
    int lineConut = 0;
    const char* curr = content;
    while(*curr != '\0'){
        if(*curr == '\n'){
            charCount++;
            lineConut++;
            curr++;
        } 
        if(isalpha(*curr)) {
            while(!isspace(*curr)){
                charCount++;
                curr++;
                if (*curr == '\n') lineConut++;
            }
            wordCount++;
        }
        charCount++;
        curr++;
    }
    printf("number of character is %d\n", charCount);
    printf("number of words is %d\n", wordCount);
    printf("number of line is %d\n", lineConut);
}

/* 用户交互输入 */
void repl(void) {
    char buff[MAX_INPUT];
    printf("Please enter:>");
    fgets(buff, MAX_INPUT, stdin);
    run(buff);
}

/* 读取文件  */ 
static char* readFile(const char* path) {
    // 创建文件流
    FILE* src = fopen(path, "rb");
    if(!src) {
        perror("readFile");
        return NULL;
    }

    // 获取文件大小
    fseek(src, 0l, SEEK_END);
    long fileSize = ftell(src);
    rewind(src); // 重新将指针指向文件起始
    
    // 创建堆空间存储文件内容
    char* buff = (char*)calloc(fileSize + 1, sizeof(char));
    if (!buff) {
        perror("readFile buff");
        return NULL;
    }

    // 将内容复制进创建的空间，最后一位置空
    fread(buff, sizeof(char), fileSize, src);
    buff[fileSize] = '\0';

    fclose(src);
    return buff;
}

/* 执行文件流程分析 */
static void runFile(const char* path) {
    char* content = readFile(path);
    run(content);
    free(content);
}

int main(int argc, char* argv[]) {
    if(argc == 1){
        repl(); // 没有参数，则进入交互界面
    } else if (argc == 2){
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage:scanner [path]\n");
        exit(1);
    }
    return 0;
}

