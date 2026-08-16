// 购买足量干草的最小花费
// 有n个提供干草的公司，每个公司都有两个信息
// cost[i]代表购买1次产品需要花的钱
// val[i]代表购买1次产品所获得的干草数量
// 每个公司的产品都可以购买任意次
// 你一定要至少购买h数量的干草，返回最少要花多少钱
// 测试链接 : https://www.luogu.com.cn/problem/P2918
// 核心: 完全背包变种——"至少h"而非"不超过t"; 关键: m = h + maxv(扩充背包)
//       dp[i][j] = min(dp[i-1][j], dp[i][j-val[i]]+cost[i])
//       答案 = min(dp[n][h..m])
// 坑点: ①必须扩充背包到 h+maxv, 因为可能多买才更便宜
//       ②求min, dp初始化INF, dp[0]=0 ③完全背包j正序
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 55005;

int val[MAXN];
int cost[MAXN];
int dp[MAXM];
int n, h, maxv, m;

// dp[i][j] : 1...i里挑公司，购买严格j磅干草，需要的最少花费
// 1) dp[i-1][j]
// 2) dp[i][j-val[i]] + cost[i]
// 两种可能性中选最小
// 但是关于j需要进行一定的扩充: 可能多买一些干草反而更便宜
int compute1() {
    vector<vector<int>> f(n + 1, vector<int>(m + 1, INT_MAX));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= val[i] && f[i][j - val[i]] != INT_MAX) {
                f[i][j] = min(f[i][j], f[i][j - val[i]] + cost[i]);
            }
        }
    }
    int ans = INT_MAX;
    // >= h: h, h+1, ..., m
    for (int j = h; j <= m; j++) {
        ans = min(ans, f[n][j]);
    }
    return ans;
}

// 空间压缩
int compute2() {
    fill(dp, dp + m + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = val[i]; j <= m; j++) {
            if (dp[j - val[i]] != INT_MAX) {
                dp[j] = min(dp[j], dp[j - val[i]] + cost[i]);
            }
        }
    }
    int ans = INT_MAX;
    for (int j = h; j <= m; j++) {
        ans = min(ans, dp[j]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> h) {
        maxv = 0;
        for (int i = 1; i <= n; i++) {
            cin >> val[i] >> cost[i];
            maxv = max(maxv, val[i]);
        }
        // 最核心的一句：扩充背包！
        // 因为"至少h"，可能多买反而更便宜，所以把背包容量扩充到 h + maxv
        m = h + maxv;
        cout << compute2() << '\n';
    }
    return 0;
}
