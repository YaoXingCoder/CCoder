#include "vector.h"

/*
Date:2024.6.20
Title:ʵ�ֶ�̬����
Content:
*/
int main(void) {
	Vector* v = createNullVec();

	for (int i = 0; i < 128; i++) {
		appendVal(v, i);
	}

	destoryVec(v);
	return 0;
}
