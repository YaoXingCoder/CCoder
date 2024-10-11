/*************************************************************************
    > File Name: tree_t.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月12日 星期一 23时22分31秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <my_header.h>
#include <dirent.h>
#include <unistd.h>


static int get_tree_recur(int sockfd, const char* dirpath, int width) {
    DIR* dirp = opendir(".");
    if ( dirp == NULL ) { perror( "cmd.c get_tree_recur opendir"); return -1; }

    struct dirent* pdirent; /* 记录目录项 */

    /* 循环读取当前目录下的目录项 */
    while ( (pdirent = readdir(dirp)) != NULL ) {
        /* 忽略目录的. 和 .. */
        if( strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0  ) { continue; }

        /* 记录前缀和索引 */
        char prefix[32] = { 0 };
        /* strcat(prefix, "└"); */
        for( int i = 0; i < width; ++i) { 
            if ( i % 4 == 0 ) { strcat(prefix, "└"); continue; }
            strcat(prefix, "一"); 
        }

        /* 发送当前的目录名给客户端 */
        char filename[512] = { 0 };
        sprintf(filename, "%s%s\n", prefix, pdirent->d_name);
        /* int ret = sendn(sockfd, filename, strlen(filename)); */
        printf("%s", filename);

        /* 判断当前文件是否是目录 */
        if ( pdirent->d_type == DT_DIR ) {
            int ret = chdir(pdirent->d_name); /* 切换到子目录下 */
            get_tree_recur(sockfd, ".", width + 4); /* 遍历目录 */
            ret = chdir(".."); /* 切换回父目录 */
        }
    }

    /* 关闭资源 */
    closedir(dirp);
    return 0;
}

int main (int argc, char* argv[]) {
    get_tree_recur(1, ".", 4);
    return 0;
}
