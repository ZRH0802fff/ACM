// 01背包(模版)
// 给定一个正数t，表示背包的容量
// 有m个货物，每个货物可以选择一次
// 每个货物有自己的体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1048
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 105;
const int MAXT = 1005;

int cost[MAXM];
int val[MAXM];
int dp[MAXT];
int t, n;

// 严格位置依赖的动态规划
int compute1() {
    int f[MAXM][MAXT] = {};
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= t; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= cost[i]) {
                f[i][j] = max(f[i][j], f[i - 1][j - cost[i]] + val[i]);
            }
        }
    }
    return f[n][t];
}

// 空间压缩
int compute2() {
    fill(dp, dp + t + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = t; j >= cost[i]; j--) {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    return dp[t];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> t >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> cost[i] >> val[i];
        }
        cout << compute2() << '\n';
    }
    return 0;
}
