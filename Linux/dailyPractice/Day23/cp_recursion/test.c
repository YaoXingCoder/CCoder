/* 
Date:
Title:
Author:
Content:
 */

#include <my_header.h>
#include <libgen.h>
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    char* buf = basename(argv[1]);
    printf("%s\n", buf);
    return 0;
}

