/* 
Date:
Title:
Author:
Content:
 */

#include <my_header.h>
// fork
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < 3; i++){
        fork();
        // printf("a"); // 24个a
        // sleep(1);
        printf("a\n"); // 14个a
    }    
    return 0;
}

