/* 
Data:2024.7.8
Title:实现ls -al
Author:JiaZiChunQiu
Content:
*/

#include <my_header.h>
#include <sys/stat.h> // chmod
#include <unistd.h> // getcwd
#include <dirent.h>
#include <errno.h> // errno
#include <error.h> // error



void ls_al(DIR* dirp) {
    struct dirent* pdirent;
    while((pdirent = readdir(dirp)) != NULL) {
        struct stat stat_buf;
        int ret = stat(pdirent->d_name, &stat_buf);
        ERROR_CHECK(ret, -1, "stat_buf");
        
        printf("%o %lu %u %u %lu %lu %s\n",
               stat_buf.st_mode, // 八进制无符号，权限数字表示
               stat_buf.st_nlink, // 无符号长整型输出，链接数
               stat_buf.st_uid, // 无符号int输出，用户id
               stat_buf.st_gid, // 无符号int输出，组id
               stat_buf.st_size, // 无符号长整型， 文件实际大小
               stat_buf.st_mtime, // 时间戳打印秒数，无符号长整型
               pdirent->d_name); // 字符串打印，文件名
    }

}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2); // 判断参数数量
    DIR* dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir"); // 判断目录流创建
    
    // 切换工作目录为参数传入的目录
    int ret = chdir(argv[1]);
    ERROR_CHECK(ret, -1, "chdir");

    ls_al(dirp); // 调用函数

    closedir(dirp);
    return 0;
}
