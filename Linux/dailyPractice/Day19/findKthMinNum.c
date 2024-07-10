/*************************
Date:2024.7.3
Title:查找数组中第k小的元素（时间复杂度O(n)）
Author:JiaZiChunQiu
Content:
 *************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))


/*
a. 查找一个数组中第k小的元素 (思考: 能否将时间复杂度降低到O(n)呢)
int find_kth_minimum(int arr[], int n, int k);

b. 给定一个无序数组，求它的中位数

int find_median(int arr[], int n);
输入：[3, 1, 2]
输出：2
输入 [4, 1, 3, 2]
输出：2
 */

// 打印
void printArr(int arr[], int len) {
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
}

//一次分区的后中间元素的下标
int getPartationIndex(int arr[], int left, int right){
    // int pivotIdx = left + (rand() % (right - left)); // 在[left, right]区间随机选取一个pivotIdx
    int pivot = arr[left]; // 临时变量存选定的pivot数据
    int low = left, high = right;
    while(low < high){
        while(high > low && arr[high] >= pivot ) high--; // 先从右边判断
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot) low++;
        arr[high] = arr[low];
    } // low = high
    arr[low] = pivot;
    return low;
}

// 单分区的递归, 返回符合元素相等的下标
int partRecursion(int arr[], int left, int right, int k){
    int pivotIdx = getPartationIndex(arr, left, right);
    if(k - 1 == pivotIdx) return pivotIdx;
    else if (k - 1 < pivotIdx) return partRecursion(arr, left, pivotIdx - 1, k);
    else if (k - 1 > pivotIdx) return partRecursion(arr, pivotIdx + 1, right, k);
}

// 思路：快排
int find_kth_minimum(int arr[], int len, int k){
    // 判断k的合法性
    if (k < 0 || k > len) {
        printf("k is illegal value");
        return -1;
    }
    
    // 获取第k个小的元素的小标
    int idx = partRecursion(arr, 0, len - 1, k);

    return arr[idx]; // 返回元素值
}


/*
 * 无序数组求他的中位数
 */
double find_median(int arr[], int len){
    if (len % 2 == 1) {
        int midIdx = len / 2 + 1;
        return find_kth_minimum(arr, len, midIdx);
    } else {
        int left = len / 2;
        int right = len / 2 + 1;
        return (double)(find_kth_minimum(arr, len, left) + find_kth_minimum(arr, len, right)) / 2.0;
    }
}

int main(int argc, char* argv[]) {
    int arr[] = {-1, -3, -50, 10, 4, 1, 3, 2, 12, 33, 55, 0, 5};
    printf("第%d个小的的数字是%d\n", 5, find_kth_minimum(arr, ARR_SIZE(arr), 5));
    printf("中位数是%.2f\n", find_median(arr, ARR_SIZE(arr)));
    printArr(arr, ARR_SIZE(arr));
    putchar('\n');
    return 0;
}


