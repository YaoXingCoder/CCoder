/* 
Date:2024.7.12
Title:管道使用
Author:JiaZiChunQiu
Content:

 */


#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// error
#include <error.h>
#include <errno.h>
// write
#include <unistd.h>

int main(int argc,char*argv[]) {
	int fd_write = open("pipe1.pipe", O_WRONLY);

	char buf[4096] = {0};
	int times = 0;
	while(1){
	   write(fd_write, buf, sizeof(buf));
	   printf("write times: %d \n", ++times);
	}

	close(fd_write);
	return 0;
}
