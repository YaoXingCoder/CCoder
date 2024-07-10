/* 
Date:2024.7.8
Title:递归复制文件
Author:JiaZiChunQiu
Content:
 */

#include <my_header.h>
#include <dirent.h> // struct dirent
#include <sys/types.h> // opendir
// 文件流
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

// basename
#include <libgen.h>

#include <error.h>
#include <errno.h>

void copyFile(char* src, char* dst, char* filename); // 复制文件
void copyDir(char* src, char* dst); // 复制目录
void _copy_dir(char* src, char* dst); // 复制目录

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);
    _copy_dir(argv[1], argv[2]);
    return 0;
}

void _copy_dir(char* src, char* dst){
    // 先创建目标的根目录
    DIR* dst_dirp = opendir(dst);
    if (dst_dirp == NULL){
        if (mkdir(dst, 0777) == -1) error(1, errno, "mkdir %s", dst);
    } else closedir(dst_dirp);
    copyDir(src, dst);
}


/* 复制文件
 * 没有则创建
 * */
void copyFile(char* src, char* dst, char* filename) {
    char tmp_src_dir[1024] = { 0 };
    char tmp_dst_dir[1024] = { 0 };

    sprintf(tmp_src_dir, "%s/%s", src, filename);
    sprintf(tmp_dst_dir, "%s/%s", dst, filename);

    int fdr = open(tmp_src_dir, O_RDONLY);
    ERROR_CHECK(fdr, -1, "copy open fdr");

    int fdw = open(tmp_dst_dir, O_WRONLY|O_CREAT|O_TRUNC, 0666);
    ERROR_CHECK(fdw, -1, "copy open fdw");

    // 循环读取
    char buf[1024] = { 0 };
    ssize_t read_count = 0;
    while((read_count = read(fdr, buf, sizeof(buf))) > 0){
        write(fdw, buf, read_count);
    }

    // 关闭流
    close(fdw);
    close(fdr);
    return;
}

/* 复制目录  */
void copyDir(char* src, char* dst) {
 
    // 如果源路径是"."和".."直接返回
    if( (strcmp(src, ".") == 0) || (strcmp(src, "..") == 0) ) return;

    // 打开目录流，创建dst目录,
    DIR* src_dirp = opendir(src);
    ERROR_CHECK(src_dirp, NULL, "cpDir opendir");

    // 创建dirent结构体
    struct dirent* pdirent;

    // 记录源文件路径，和目标路径
    char tmp_src_dir[1024] = {0};
    char tmp_dst_dir[1024] = {0};

    // 创建与src相同目录
    sprintf(tmp_dst_dir, "%s/%s", dst, basename(src)); // 目标路径拼接源路径
    DIR* dst_dirp = opendir(tmp_dst_dir); // 能带开目录已有，未打开目录为创建
    if (dst_dirp == NULL) mkdir(tmp_dst_dir, 0777); // 该目录未被创建
    else closedir(dst_dirp); // 该目录已被创建
    

    // 该目录项是目录，则调用copyDir递归复制
    while((pdirent = readdir(src_dirp)) != NULL) {

        // 该文件是目录则递归创建，县合并再进入递归
        if (pdirent->d_type == DT_DIR) {
            if ( (strcmp(pdirent->d_name, ".") == 0) || (strcmp(pdirent->d_name, "..") == 0) ) continue;
            sprintf(tmp_src_dir, "%s/%s", src, pdirent->d_name);
            copyDir(tmp_src_dir, tmp_dst_dir);
        } else if (pdirent->d_type == DT_REG) copyFile(src, tmp_dst_dir, pdirent->d_name);
    }

    closedir(src_dirp);
}
