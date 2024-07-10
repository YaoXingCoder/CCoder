/* 
Date:2024.7.9
Title:目录文件递归删除（后序）
Author:JiaZiChunQiu
Content:
 */

#include <my_header.h>
// opdir
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
// error
#include <error.h>
#include <errno.h>
// unlink
#include <unistd.h>

void delDirt(const char* path) {
    //打开目录
    DIR* dirp = opendir(path);
    if (dirp == NULL ) error(1, errno, "delDirt open %s", path);

    // 创建目录项结构体
    struct dirent* pdirent;

    // 遍历目录流
    while((pdirent = readdir(dirp)) != NULL) {
        // 掠过"."和".."
        if ( (strcmp(pdirent->d_name, ".") == 0) || (strcmp(pdirent->d_name, "..") == 0) ) continue;

        // 拼接路径
        char tmp_path[1024] = {0};
        sprintf(tmp_path, "%s/%s", path, pdirent->d_name);

        // 递归遍历目录，删除文件
        if (pdirent->d_type == DT_DIR) delDirt(tmp_path);
        else while(unlink(tmp_path) == 0);
    }
    // 删除目录
    if (rmdir(path) == -1) error(1, errno, "delDirt rmdir %s", path);
    closedir(dirp);
}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    delDirt(argv[1]);
    return 0;
}

