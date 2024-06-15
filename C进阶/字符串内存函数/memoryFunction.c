#include <assert.h>

/*
Date:2024.6.15
Title:模拟内存函数
Content:
my_memcpy：内存拷贝
my_memmove：内存拷贝
my_memcmp：
*/

/*
模拟实现memcpy
强转为char类型，按字节依次拷贝
*/
void* my_memcpy(void* dest, void* src, int size) {
	assert(dest && src);
	void* ret = dest;
	while (size--) {
		*(char*)dest = *(char*)src;
		dest = (char*)dest + 1;
		src = (char*)src + 1;
	}
	return ret;
}

/*
模拟实现memmove
分两种，
有地址范围重叠时
dest < src，在src中前->后依次拷贝dest中的前->后
dest > src，在src中后->前依次拷贝dest中的后->前
没有范围重叠时
都可以
*/
void* my_memmove(void* dest, void* src, int num) {
	assert(dest && src);

}