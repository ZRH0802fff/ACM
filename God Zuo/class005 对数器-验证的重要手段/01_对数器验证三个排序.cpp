// 对数器 —— 验证的重要手段
// 对数器：当你写的算法没有在线测试(OJ)可测时，用「暴力解 + 随机样本 + 对拍」来自我验证。
//
// 方法论：
//   1. 写一个容易实现、能保证正确的暴力解（方法B）
//   2. 写你想验证的最优解（方法A）
//   3. 写随机样本产生器（长度、值范围都可控）
//   4. 让 A、B 跑同一份随机输入，比对结果（对拍）
//   5. 结果不一致就打印出错的短样本，代入 debug；一致则多测成千上万组
//   6. 小数据验证通过后，再逐步放大数据量
//
// 本节用「选择排序 / 冒泡排序 / 插入排序」三个思路完成排序这一功能，两两对拍，
// 任何一个写错（比如选择排序 i 笔误成从 1 开始）都能被立刻抓出来。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;   // 随机数组最大长度

int arr[MAXN];   // 原始随机数组
int arr1[MAXN];  // 拷贝1（选择排序）
int arr2[MAXN];  // 拷贝2（冒泡排序）
int arr3[MAXN];  // 拷贝3（插入排序）

// 选择排序
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 冒泡排序
void bubbleSort(int arr[], int n) {
    for (int end = n - 1; end > 0; end--) {
        for (int i = 0; i < end; i++) {
            if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);
        }
    }
}

// 插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) {
            swap(arr[j], arr[j + 1]);
        }
    }
}

// 随机数组生成器：把全局 arr 填成长度 n、每个值在 [1, v] 的随机数组
// Math.random() -> [0,1) 的小数；(int)(Math.random() * v) + 1 -> [1, v] 的整数
// C++ 用 rand() % v + 1 得到 [1, v] 的整数
void randomArray(int n, int v) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % v + 1;
    }
}

// 拷贝数组：src -> dst（长度 n）
void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

// 判断两个数组（长度 n）每个位置是否都相等
bool sameArray(int a[], int b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main() {
    srand(time(0));
    int N = 100;            // 随机数组最大长度
    int V = 1000;           // 随机数组每个值在 [1, V]
    int testTimes = 50000;  // 测试次数

    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++) {
        int n = rand() % N;   // 长度在 [0, N-1]
        randomArray(n, V);    // 生成随机数组到 arr
        copyArray(arr, arr1, n);
        copyArray(arr, arr2, n);
        copyArray(arr, arr3, n);
        selectionSort(arr1, n);
        bubbleSort(arr2, n);
        insertionSort(arr3, n);
        if (!sameArray(arr1, arr2, n) || !sameArray(arr1, arr3, n)) {
            cout << "出错了!" << endl;
            cout << "原始数组: ";
            for (int j = 0; j < n; j++) cout << arr[j] << " ";
            cout << endl;
            cout << "选择排序: ";
            for (int j = 0; j < n; j++) cout << arr1[j] << " ";
            cout << endl;
            cout << "冒泡排序: ";
            for (int j = 0; j < n; j++) cout << arr2[j] << " ";
            cout << endl;
            cout << "插入排序: ";
            for (int j = 0; j < n; j++) cout << arr3[j] << " ";
            cout << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
