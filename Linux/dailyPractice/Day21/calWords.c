/*************************
Date:2024.7.4
Title:计算文件行数，单词书，字符数
Author:JiaZiChunQiu
Content:
 *************************/

#include <stdio.h>
#include <string.h>


// 获取文件
void getFileStream(void) {
    char filePath[128];
    printf("请输入命令:>");
    fgets(filePath, strlen(filePath), stdin);
    FILE* src = popen(filePath, "r");
    if (!src) perror("getFileStream");
    char buff[1024];
    while(fgets(buff, sizeof(buff), src)) {
        printf("%s", buff);
    }
    pclose(src);
}

int main(int argc, char* argv[]) {
    getFileStream();
    return 0;
}

