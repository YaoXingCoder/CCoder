/* 
Date:2024.7.9
Title:cp简单实现（不包含根目录）
Author:JiaZiChunQiu
Content:
 */

#include <my_header.h>
// open, mkdir
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// dirent, readdir, opendir, closedir
#include <dirent.h>

// read
#include <unistd.h>

// error
#include <error.h>
#include <errno.h>

void cpFile(const char* src_path, const char* dst_path);
void cpDirt(const char* src_path, const char* dst_path);

void cpFile(const char* src_path, const char* dst_path) {
    // 打开流
    int fdr = open(src_path, O_RDONLY);
    if (fdr == -1) error(1, errno, "cpFile fdr %s", src_path);
    
    int fdw = open(dst_path, O_WRONLY|O_CREAT|O_TRUNC, 0766);
    if (fdw == -1) error(1, errno, "cpFile fdw %s", dst_path);

    // 临时存储变量
    char buf[1024];
    ssize_t read_count = 0;

    // 循环读写
    while( (read_count = read(fdr, buf, sizeof(buf))) > 0 ) {
        write(fdw, buf, read_count);
    }

    // 关闭
    close(fdw);
    close(fdr);
    return;

}

void cpDirt(const char* src_path, const char* dst_path) {
    // 创建目录
    if (mkdir(dst_path, 0777) == -1) error(1, errno, "cpDirt mkdir %s", dst_path);
    
    // 创建dirent目录项
    struct dirent* pdirent;
    
    // 创建目录流
    DIR* dirp = opendir(src_path);
    if (dirp == NULL) error(1, errno, "cpDirt opdir %s", src_path);

    // 循环读取目录项
    while( (pdirent = readdir(dirp)) != NULL) {
        // 跳过".."和"."
        if ( (strcmp(pdirent->d_name, ".")) == 0 || (strcmp(pdirent->d_name, "..") == 0)) continue;

        // 拼接地址
        char tmp_src_path[1024] = { 0 };
        sprintf(tmp_src_path, "%s/%s", src_path, pdirent->d_name);
        char tmp_dst_paht[1024] = { 0 };
        sprintf(tmp_dst_paht, "%s/%s", dst_path, pdirent->d_name);

        // 判断
        if (pdirent->d_type == DT_DIR) cpDirt(tmp_src_path, tmp_dst_paht);
        else cpFile(tmp_src_path, tmp_dst_paht);
    }

    closedir(dirp);
    return;
}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);
    cpDirt(argv[1], argv[2]);
    return 0;
}

