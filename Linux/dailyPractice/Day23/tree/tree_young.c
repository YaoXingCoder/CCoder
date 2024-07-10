/* 
Date:2024.7.8
Title:实现tree
Author:JiaZiChunQiu
Content:
 */

#include <my_header.h>                                                   
#include <dirent.h>

static int dirs = 0;
static int files = 0;

void dfs_print(char* dirpath, int width){
    // 打开目录流
    DIR* dirp = opendir(dirpath);
    ERROR_CHECK(dirp, NULL, "opendir");

    struct dirent* pdirent; // 记录目录项
    
    // 循环读取目录项
    while((pdirent = readdir(dirp)) != NULL) {
        // 跳过 "." 和 ".."
        if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0 ) continue;
        
        // 打印前缀和索引，构建树形结构
        printf("└");
        for(int i = 0; i < width; i++) {
            printf("—");
        }

        // 打印当前目录或文件的名称
        printf("%s\n", pdirent->d_name);

        // 目录则深度遍历
        if (pdirent->d_type == DT_DIR) {
            dirs++;

            // 需要拼凑绝对路径
            char curr_path[1024] = {0};
            sprintf(curr_path, "%s/%s", dirpath, pdirent->d_name);
            
            // 进入递归
            dfs_print(curr_path, width + 1);
        } else {
            files++;
        } // 不是目录统一认为时文件
    }

    // 关闭流
    closedir(dirp);
}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2); // 检测是否两个参数
    printf("%s\n", argv[1]); // 打印根目录
    dfs_print(argv[1], 4); // 根，根与文件的间隔
    printf("\n%d directories, %d files\n", dirs, files); // 打印目录，文件数
    return 0;
}

