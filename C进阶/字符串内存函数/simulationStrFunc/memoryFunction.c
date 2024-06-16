#include <assert.h>

/*
Date:2024.6.15
Title:ģ���ڴ溯��
Content:
my_memcpy���ڴ濽��
my_memmove���ڴ濽��
my_memcmp���ڴ�Ƚ�
*/

/*
ģ��ʵ��memcpy
ǿתΪchar���ͣ����ֽ����ο���
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
ģ��ʵ��memmove
�����֣�
�е�ַ��Χ�ص�ʱ
dest < src����src��ǰ->�����ο���dest�е�ǰ->��
dest > src����src�к�->ǰ���ο���dest�еĺ�->ǰ
û�з�Χ�ص�ʱ,������
�����֣������ص�û����������
1. dest < src ��ǰ���
2. dest > src �Ӻ���ǰ��
ÿ���滻һ���ֽ�
*/
void* my_memmove(void* dest, void* src, int size) {
	assert(dest && src);
	void* ret = dest;
	if (dest < src) {
		while (size--) {
			*(char*)dest = *(char*)src;
			dest = (char*)dest + 1;
			src = (char*)src + 1;
		}
	}
	if (dest > src) {
		while (size--) {
			*((char*)dest + size) = *((char*)src + size);
		}
	}
	return ret;
}