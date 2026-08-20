// 牛牛的背包问题 & 世界冰球锦标赛
// 牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容量为w。
// 牛牛家里一共有n袋零食, 第i袋零食体积为v[i]。
// 牛牛想知道在总体积不超过背包容量的情况下,他一共有多少种零食放法(总体积为0也算一种放法)。
// 输入描述：
// 输入包括两行
// 第一行为两个正整数n和w(1 <= n <= 30, 1 <= w <= 2 * 10^9),表示零食的数量和背包的容量
// 第二行n个正整数v[i](0 <= v[i] <= 10^9),表示每袋零食的体积
// 输出描述：
// 输出一个正整数, 表示牛牛一共有多少种零食放法。
// 测试链接 : https://www.luogu.com.cn/problem/P4799
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40;
const int MAXM = 1 << 20;

long long arr[MAXN];
long long lsum[MAXM];
long long rsum[MAXM];

int n;
long long w;

// arr[i..e-1]范围上展开，到达e就停止
// 返回值 : ans数组填到了什么位置！
int f(int i, int e, long long s, long long w, long long ans[], int j) {
    if (s > w) {
        return j;
    }
    // s <= w
    if (i == e) {
        ans[j++] = s;
    } else {
        // 不要arr[i]位置的数
        j = f(i + 1, e, s, w, ans, j);
        // 要arr[i]位置的数
        j = f(i + 1, e, s + arr[i], w, ans, j);
    }
    return j;
}

long long compute() {
    int lsize = f(0, n >> 1, 0, w, lsum, 0);
    int rsize = f(n >> 1, n, 0, w, rsum, 0);
    sort(lsum, lsum + lsize);
    sort(rsum, rsum + rsize);
    long long ans = 0;
    for (int i = lsize - 1, j = 0; i >= 0; i--) {
        while (j < rsize && lsum[i] + rsum[j] <= w) {
            j++;
        }
        ans += j;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> w) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << compute() << '\n';
    }
    return 0;
}
