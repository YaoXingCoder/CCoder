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
	int fd_read = open("pipe1.pipe", O_RDONLY);

	sleep(10);
	char buf[4096] = {0};
	while(1){
	   read(fd_read, buf, sizeof(buf));
	   printf("read \n");
	   sleep(2);
	}

	close(fd_read);
	return 0;
}
