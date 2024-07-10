/*************************
Date:2024.7.3
Title:循环有序的数组找出最小的元素
Author:JiaZiChunQiu
Content:
 *************************/

#include <stdio.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/*
假定一个数组有 n 个元素，这 n 个元素各不相同，并且循环有序，请找出最小的那个元素。
int findMin(int arr[], int n);

示例1：
输入：[3, 4, 5, 1, 2]
输出：1

示例2：
输入：[4,5,6,7,0,1,2]
输出：0
*/

// 二分查找
int findMin(int arr[], int len) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = left + (right - left >> 1);
        if (arr[right] < arr[mid]) left = mid + 1; // 先从右边判断，认为有序是递增有序的
        else if (arr[left] < arr[mid]) right = mid - 1;
        else {
            if ( mid > 0 && arr[mid - 1] < arr[mid]) right = mid;
            else return arr[mid];
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    int arr[] = {4, 5, 6, 7, 0, 1, 2};
    printf("最小元素为：%d\n", findMin(arr, ARR_SIZE(arr)));
    return 0;
}
