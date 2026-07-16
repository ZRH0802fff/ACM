// 有一次修改机会的最长不下降子序列
// 给定一个长度为n的数组arr，和一个整数k
// 只有一次机会可以将其中连续的k个数全修改成任意一个值
// 这次机会你可以用也可以不用，请返回最长不下降子序列长度
// 1 <= k, n <= 10^5
// 1 <= arr[i] <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P8776
// 核心: 修改的K个紧贴分界点; 枚举j: left(结尾<=arr[j]) + K + rightArr[j](以arr[j]开头)
//       rightArr: 从右往左最长不上升 = 从左往右以该位置开头的最长不下降
//       分离: 用arr[j](分界值)查edp, 用arr[i](滑出窗口)入edp
// 坑点: ①别漏末尾K个(右侧空)的情况 ans=max(ans, len+K)
//       ②edp在computeRight(bs1:<最左)和主循环(bs2:>最左)复用, 二分策略不同
//       ③suffix[n-1]必须显式置0(全局数组残留)
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int arr[MAXN];
int rightArr[MAXN];
int edp[MAXN];
int n, k;

// 求最长不上升子序列长度的二分
// edp[0...len-1]是降序的，找到<num的最左位置，不存在返回-1
int bs1(int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (edp[m] < num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

// 求最长不下降子序列长度的二分
// edp[0...len-1]是不降序的，找到>num的最左位置，不存在返回-1
int bs2(int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (edp[m] > num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

// 生成辅助数组rightArr
// rightArr[j] : 一定以arr[j]做开头，arr[j...]上最长不下降子序列长度
// 关键：从右往左遍历，以arr[i]做结尾的最长不上升子序列
void computeRight() {
    int len = 0;
    for (int i = n - 1, find; i >= 0; i--) {
        find = bs1(len, arr[i]);
        if (find == -1) {
            edp[len++] = arr[i];
            rightArr[i] = len;
        } else {
            edp[find] = arr[i];
            rightArr[i] = find + 1;
        }
    }
}

int compute() {
    computeRight();
    int len = 0;
    int ans = 0;
    for (int i = 0, j = k, find, left; j < n; i++, j++) {
        find = bs2(len, arr[j]);
        left = find == -1 ? len : find;
        ans = max(ans, left + k + rightArr[j]);
        find = bs2(len, arr[i]);
        if (find == -1) {
            edp[len++] = arr[i];
        } else {
            edp[find] = arr[i];
        }
    }
    ans = max(ans, len + k);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        if (k >= n) {
            cout << n << '\n';
        } else {
            cout << compute() << '\n';
        }
    }
    return 0;
}
