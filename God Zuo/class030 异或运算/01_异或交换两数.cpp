// 用异或运算交换两数的值

#include <bits/stdc++.h>
using namespace std;

// 当i!=j，没问题，会完成交换功能
// 当i==j，会出错
// 所以知道这种写法即可，并不推荐
void swapXor(int arr[], int i, int j) {
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
}

int main() {
    int a = -2323;
    int b = 10;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << a << endl;
    cout << b << endl;

    int arr[] = {3, 5};
    swapXor(arr, 0, 1);
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    swapXor(arr, 0, 0);
    cout << arr[0] << endl;

    return 0;
}
