/*************************************************************************
    > File Name: test.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月10日 星期六 10时43分03秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <my_header.h>

int main (int argc, char* argv[]) {
    printf("str len is %ld\n", strlen("insert into `virtual_file`(`parent_id`, `filename`, `owner_id`, `hash_val`, `filesize`, `type`, `path`)" "values ('%s', '%s', '%s', '%s', '%s', '%s', '%s')"));
    return 0;
}
