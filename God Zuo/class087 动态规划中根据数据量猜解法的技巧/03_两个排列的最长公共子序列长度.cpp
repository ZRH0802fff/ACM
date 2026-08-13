// 两个排列的最长公共子序列长度
// 给出由1~n这些数字组成的两个排列
// 求它们的最长公共子序列长度
// n <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1439
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int a[MAXN];
int b[MAXN];
int where[MAXN];
int endsArr[MAXN];
int n;

int bs(int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (endsArr[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

// 讲解072 - 最长递增子序列及其扩展
int lis() {
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs(len, b[i]);
        if (find == -1) {
            endsArr[len++] = b[i];
        } else {
            endsArr[find] = b[i];
        }
    }
    return len;
}

int compute() {
    for (int i = 0; i < n; i++) {
        where[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        b[i] = where[b[i]];
    }
    return lis();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        cout << compute() << "\n";
    }
    return 0;
}
