// 分组背包(模版)
// 给定一个正数m表示背包的容量，有n个货物可供挑选
// 每个货物有自己的体积(容量消耗)、价值(获得收益)、组号(分组)
// 同一个组的物品只能挑选1件，所有挑选物品的体积总和不能超过背包容量
// 怎么挑选货物能达到价值最大，返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1757
// 核心: 同组物品只选1件; 先按组号排序; 每组内枚举所有物品, dp[i][j]=max(dp[i-1][j], dp[i-1][j-cost]+val)
// 坑点: 空间压缩时 j 必须倒序(01背包), 且每组内 k 的枚举要在 j 循环内部
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 1005;

struct Item {
    int vol, val, group;
} arr[MAXN];

int dp[MAXM];
int m, n;

// 严格位置依赖的动态规划
int compute1() {
    // 统计有多少组
    int teams = 1;
    for (int i = 2; i <= n; i++) {
        if (arr[i - 1].group != arr[i].group) {
            teams++;
        }
    }
    // 组的编号1~teams
    // dp[i][j] : 1~i是组的范围，每个组的物品挑一件，容量不超过j的情况下，最大收益
    // dp[0][....] = 0
    int f[MAXN][MAXM] = {};
    for (int start = 1, end = 2, i = 1; start <= n; i++) {
        while (end <= n && arr[end].group == arr[start].group) {
            end++;
        }
        // start ... end-1 -> i组
        for (int j = 0; j <= m; j++) {
            // arr[start...end-1]是当前组，组号一样
            // 其中的每一件商品枚举一遍
            f[i][j] = f[i - 1][j];
            for (int k = start; k < end; k++) {
                if (j >= arr[k].vol) {
                    f[i][j] = max(f[i][j], f[i - 1][j - arr[k].vol] + arr[k].val);
                }
            }
        }
        // start去往下一组的第一个物品
        // 继续处理剩下的组
        start = end++;
    }
    return f[teams][m];
}

// 空间压缩
int compute2() {
    // dp[0][...] = 0
    fill(dp, dp + m + 1, 0);
    for (int start = 1, end = 2; start <= n;) {
        while (end <= n && arr[end].group == arr[start].group) {
            end++;
        }
        // start...end-1
        for (int j = m; j >= 0; j--) {
            for (int k = start; k < end; k++) {
                if (j >= arr[k].vol) {
                    dp[j] = max(dp[j], arr[k].val + dp[j - arr[k].vol]);
                }
            }
        }
        start = end++;
    }
    return dp[m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> m >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> arr[i].vol >> arr[i].val >> arr[i].group;
        }
        // 按组号排序
        sort(arr + 1, arr + n + 1, [](const Item& a, const Item& b) { return a.group < b.group; });
        cout << compute2() << '\n';
    }
    return 0;
}
