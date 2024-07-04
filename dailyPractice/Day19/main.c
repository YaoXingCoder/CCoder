/*************************
Date:2024.7.3
Title:���������е�kС��Ԫ�أ�ʱ�临�Ӷ�O(n)��
Author:JiaZiChunQiu
Content:
a. ����һ�������е�kС��Ԫ�� (˼��: �ܷ�ʱ�临�ӶȽ��͵�O(n)��)
b. ����һ���������飬��������λ��
c. Hָ��
 *************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))


/*
a. ����һ�������е�kС��Ԫ�� (˼��: �ܷ�ʱ�临�ӶȽ��͵�O(n)��)
int find_kth_minimum(int arr[], int n, int k);

b. ����һ���������飬��������λ��

int find_median(int arr[], int n);
���룺[3, 1, 2]
�����2
���� [4, 1, 3, 2]
�����2
 */

// ��ӡ
void printArr(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

//һ�η����ĺ��м�Ԫ�ص��±�
int getPartationIndex(int arr[], int left, int right) {
    // int pivotIdx = left + (rand() % (right - left)); // ��[left, right]�������ѡȡһ��pivotIdx
    int pivot = arr[left]; // ��ʱ������ѡ����pivot����
    int low = left, high = right;
    while (low < high) {
        while (high > low && arr[high] >= pivot) high--; // �ȴ��ұ��ж�
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) low++;
        arr[high] = arr[low];
    } // low = high
    arr[low] = pivot;
    return low;
}

// �������ĵݹ�, ���ط���Ԫ����ȵ��±�
int partRecursion(int arr[], int left, int right, int k) {
    int pivotIdx = getPartationIndex(arr, left, right);
    if (k - 1 == pivotIdx) return pivotIdx;
    else if (k - 1 < pivotIdx) return partRecursion(arr, left, pivotIdx - 1, k);
    else if (k - 1 > pivotIdx) return partRecursion(arr, pivotIdx + 1, right, k);
}

// ˼·������
int find_kth_minimum(int arr[], int len, int k) {
    // �ж�k�ĺϷ���
    if (k < 0 || k > len) {
        printf("k is illegal value");
        return -1;
    }

    // ��ȡ��k��С��Ԫ�ص�С��
    int idx = partRecursion(arr, 0, len - 1, k);

    return arr[idx]; // ����Ԫ��ֵ
}


/*
 * ������������λ��
 */
double find_median(int arr[], int len) {
    if (len % 2 == 1) {
        int midIdx = len / 2 + 1;
        return find_kth_minimum(arr, len, midIdx);
    } else {
        int left = len / 2;
        int right = len / 2 + 1;
        return (double)(find_kth_minimum(arr, len, left) + find_kth_minimum(arr, len, right)) / 2.0;
    }
}

//int main(int argc, char* argv[]) {
//    int arr[] = { -1, -3, -50, 10, 4, 1, 3, 2, 12, 33, 55, 0, 5 };
//    printf("��%d��С�ĵ�������%d\n", 5, find_kth_minimum(arr, ARR_SIZE(arr), 5));
//    printf("��λ����%.2f\n", find_median(arr, ARR_SIZE(arr)));
//    printArr(arr, ARR_SIZE(arr));
//    putchar('\n');
//    return 0;
//}


/*
����һ���������� citations ������ citations[i] ��ʾ�о��ߵĵ� i ƪ���ı����õĴ�����citations �Ѿ����� �������� �����㲢���ظ��о��ߵ� h ָ����
h ָ���Ķ��壺h ���������ô�������high citations����һ��������Ա�� h ָ����ָ���������� ��n ƪ�����У����� �� h ƪ���ķֱ����������� h �Ρ�
������Ʋ�ʵ�ֶ���ʱ�临�Ӷȵ��㷨��������⡣
*/

int hIndex(int* citations, int citationsSize) {
    return binarySearch(citations, citationsSize);
}


int binarySearch(int arr[], int len) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = left + (right - left >> 1);
        if (arr[mid] < len - mid) left = mid + 1;
        else right = mid - 1;
    }
    return len - left;
}


// ���ֲ���
int findMin(int arr[], int len) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = left + (right - left >> 1);
        if (arr[right] < arr[mid]) left = mid + 1; // �ȴ��ұ��жϣ���Ϊ�����ǵ��������
        else if (arr[left] < arr[mid]) right = mid - 1;
        else {
            if (mid > 0 && arr[mid - 1] < arr[mid]) right = mid;
            else return arr[mid];
        }   
    }
}

int main(int argc, char* argv[]) {
    int arr[] = { 6,7,0,1,2,3};
    printf("��СԪ��Ϊ��%d\n", findMin(arr, ARR_SIZE(arr)));
    return 0;
}
