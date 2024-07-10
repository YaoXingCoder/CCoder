/* 
Date:2024.7.9
Title:实现mmap文件复制
Author:JiaZiChunQiu
Content:
请编写一个小程序，使用 mmap 实现文件的复制。
#include <func.h>
int main(int argc, char* argv[]) {
    // ./mmap_cp src dst
}
 */

#include <my_header.h>
// open, fstat
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// error
#include <errno.h>
#include <error.h>
// ftruncate
#include <unistd.h>
// mmap
#include <sys/mman.h>

#define BLOCKS_MAXSIZE (1024 * 1024 * 8) // 8MB

void mmap_cp(char* src_path, char* dst_path) {
    // 文件流
    int fdr = open(src_path, O_RDONLY);
    if (fdr == -1) error(1, errno, "mmap_cp open %s", src_path);
    
    int fdw = open(dst_path, O_RDWR|O_CREAT|O_TRUNC, 644);
    if (fdw == -1) error(1, errno, "mmap_cp open %s", dst_path);

    // 获取源文件大小，通过stat结构体
    struct stat sbuf;
    int ret = fstat(fdr, &sbuf);
    if (ret == -1) error(1, errno, "mmap_cp fstat %s", src_path);

    // 通过stat获取的文件大小，设置目标文件的大小
    off_t src_size = sbuf.st_size;
    ret = ftruncate(fdw, src_size);
    if (ret == -1) error(1, errno, "mmap_cp ftruncate %s", dst_path);

    // 循环映射复制
    off_t bytes_cpied = 0; // 记录复制大小
    while(bytes_cpied < src_size) {
        // 每次复制字节数
        off_t curr_block_size = (bytes_cpied + BLOCKS_MAXSIZE > src_size) ? (src_size - bytes_cpied) : BLOCKS_MAXSIZE;
        
        // 映射源文件
        void* srcp = mmap(NULL, curr_block_size, PROT_READ, MAP_SHARED, fdr, bytes_cpied);

        // 映射目标文件
        void* dstp = mmap(NULL, curr_block_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdw, bytes_cpied);

        // 执行内存复制
        memcpy(dstp, srcp, curr_block_size);

        // 解除映射
        munmap(srcp, curr_block_size);
        munmap(dstp, curr_block_size);

        // 更新已复制字节数
        bytes_cpied += curr_block_size;
    }

    // 清理资源
    close(fdr);
    close(fdw);
    return;
}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);
    mmap_cp(argv[1], argv[2]);
    return 0;
}
