#include <my_header.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<error.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc , char* argv[]){

    if(argc != 3) error(1, 0, "Usage: %s  src dst \n",argv[0]);

    int srcfd = open(argv[1], O_RDONLY);
    if(srcfd == -1) error(1, errno,"open %s failed \n",argv[1]);

    int dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(dstfd == -1) error(1, errno,"open %s failed \n",argv[2]);

    char buff[1024];
    int n = 0;
    while((n = read(srcfd, buff, sizeof(buff))) > 0 ){
        write(dstfd, buff, n);
    }

    close(dstfd);
    close(srcfd);
    return 0;
}
