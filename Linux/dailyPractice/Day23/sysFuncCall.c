/* 
Data:
Title:
Author:
Content:
*/

#include <my_header.h>
#include <sys/stat.h> // chmod
#include <unistd.h> // getcwd
#include <dirent.h>
#include <errno.h> // errno
#include <error.h> // error



void ls_01(DIR* dirp) {
    struct dirent* pdirent;
    long loc; // 用于记录位置
    while((pdirent = readdir(dirp)) != NULL) {
        printf("inode num = %lu, reclen = %hu, type = %u, name = %s\n",
               pdirent->d_ino, // inode编号
               pdirent->d_reclen, // 无符号短整型
               pdirent->d_type, // 无符号整型
               pdirent->d_name); // 字符数组
        if (strcmp("file1", pdirent->d_name) == 0) {
            loc = telldir(dirp); // 记录指针位置
        }
    }

    printf("============================\n");
    seekdir(dirp, loc); // 指回记录的位置
    pdirent = readdir(dirp); // 读取记录位置信息

    printf("inode num = %lu, reclen = %hu, type = %u, name = %s\n",
           pdirent->d_ino, // inode编号
           pdirent->d_reclen, // 无符号短整型
           pdirent->d_type, // 无符号整型
           pdirent->d_name); // 字符数组
    
}

int main(int argc, char* argv[]) {

    // 更改目录的权限
    // chmod 系统函数调用
    // ARGS_CHECK(argc, 2);
    // int ret = chmod(argv[1], 0775); // chmod调用
    // ERROR_CHECK(ret, -1, "chmod");

    // 获取目录路径
    // char path[1024] = {0};
    // char *p = getcwd(path, sizeof(path));
    // ERROR_CHECK(p, NULL, "getcwd");
    // printf("cwd = %s\n", path);
    
    // 模拟ls，使用指着定位
    // ARGS_CHECK(argc, 2);
    // DIR* dirp = opendir(argv[1]);
    // ERROR_CHECK(dirp, NULL, "opendir");
    // ls_01(dirp);
    // closedir(dirp);
    
     //  error 错误信息输出
     // char* cwd = getcwd(NULL, 0);
     // if (cwd == NULL) {
     //     error(1, errno, "getcwd");
     // }
     // printf("%s\n", cwd);
     // free(cwd);
    
     // stat简单调用
     ARGS_CHECK(argc, 2);
     DIR* dirp = opendir(argv[1]);
     // ERROR_CHECK(dirp, NULL, "stat");
     if (!dirp)  error(1, errno, "stat"); 
     struct dirent* pdirent = readdir(dirp);
     struct stat stat_buf;
     int ret = stat(pdirent->d_name, &stat_buf);
     
     printf("inode num = %lu, reclen = %hu, type = %u, name = %s\n",
            pdirent->d_ino, // inode编号
            pdirent->d_reclen, // 无符号短整型
            pdirent->d_type, // 无符号整型
            pdirent->d_name); // 字符数组
     printf("mode = %o, nlink = %lu, uid = %u, gid = %u, time = %lu\n",
            stat_buf.st_mode,
            stat_buf.st_nlink,
            stat_buf.st_uid,
            stat_buf.st_gid,
            stat_buf.st_mtime);
    return 0;
}

