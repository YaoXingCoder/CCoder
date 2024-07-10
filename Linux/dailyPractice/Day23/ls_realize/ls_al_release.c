#include <my_header.h>
#include <sys/stat.h> // chmod
#include <unistd.h> // getcwd
#include <dirent.h>
#include <errno.h> // errno
#include <error.h> // error
#include <sys/types.h>
#include <pwd.h> //getpwuid
#include <grp.h> //getgrgid
#include <time.h> // localtime


void set_type_mode(mode_t mode, char* mode_str){

    switch (mode & S_IFMT) {
    case S_IFBLK: mode_str[0] = 'b'; break;
    case S_IFCHR: mode_str[0] = 'c'; break;
    case S_IFDIR: mode_str[0] = 'd'; break;
    case S_IFIFO: mode_str[0] = 'p'; break;
    case S_IFLNK: mode_str[0] = 'l'; break;
    case S_IFREG: mode_str[0] = '-'; break;
    case S_IFSOCK: mode_str[0] = 's'; break;
    default:mode_str[0] = '?'; break;
    }
   
    // 所有者权限
    mode_str[1] = (mode & 0400) ? 'r' : '-';
    mode_str[2] = (mode & 0200) ? 'w' : '-';
    mode_str[3] = (mode & 0100) ? 'x' : '-';

    // 组权限
    mode_str[4] = (mode & 0040) ? 'r' : '-';
    mode_str[5] = (mode & 0020) ? 'w' : '-';
    mode_str[6] = (mode & 0010) ? 'x' : '-';

    // 其他用户权限
    mode_str[7] = (mode & 0004) ? 'r' : '-';
    mode_str[8] = (mode & 0002) ? 'w' : '-';
    mode_str[9] = (mode & 0001) ? 'x' : '-';

    // 设置字符串结束符
    mode_str[10] = '\0';
}

// 获取格式化的时间字符串
void get_time_str(time_t mtime, char* time_str) {
    char mon_arr[][10] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    struct tm* tm_val = localtime(&mtime); // 获取到tm结构体指针
    sprintf(time_str, "%s %02d %02d:%02d", 
            mon_arr[tm_val->tm_mon], // 月份
            tm_val->tm_mday, // 天
            tm_val->tm_hour, // 时
            tm_val->tm_min); // 分
}

int main(int argc, char* argv[]) {
    char* dir_name;
    if(argc == 1) dir_name = ".";
    else if (argc == 2) dir_name = argv[1];
    else {
        fprintf(stderr, "args num error!\n");
        exit(-1);
    }

    // 打开指定目录
    DIR* dirp = opendir(dir_name);
    ERROR_CHECK(dirp, NULL, "opendir");

    // 改变当前工作目录
    int ret = chdir(dir_name); 
    ERROR_CHECK(ret, -1, "chdir");

    struct dirent* pdirent;
    while((pdirent = readdir(dirp)) != NULL) {
        // 拼接文件路径，如果上面没有chdir切换目录，这里就需要做绝对路径的拼接操作
        // char path[1024] = {0};
        // sprintf(path, "%s%s%s", argv[1], "/", pdirent->d_name);
        // 或者也可以用strcpy以及strcat函数进行复制拼接获取最终目录
        // strcpy(path, argv[1]);
        // strcat(path, "/");
        // strcat(path, pdirent->d_name);
        struct stat stat_buf;
        int ret = stat(pdirent->d_name, &stat_buf);
        ERROR_CHECK(ret, -1, "stat_buf");

        // 获取类型和权限
        char mode_str[1024] = { 0 }; // 存储
        set_type_mode(stat_buf.st_mode, mode_str);

        // 获取时间
        char time_str[1024] = { 0 }; // 存储
        get_time_str(stat_buf.st_mtime, time_str);

        printf("%s %lu %s %s %lu %s %s\n",
               mode_str, // 类型和权限
               stat_buf.st_nlink, // 链接数
               getpwuid(stat_buf.st_uid)->pw_name, // 用户id
               getgrgid(stat_buf.st_gid)->gr_name, // 组id
               stat_buf.st_size, // 无符号长整型， 文件实际大小
               time_str, // 时间年月日
               pdirent->d_name); // 字符串打印，文件名
    }

    // 关闭
    closedir(dirp);
    return 0;
}
