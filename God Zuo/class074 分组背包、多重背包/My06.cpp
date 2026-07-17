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

const int maxn = 105;
const int maxm = 55005;
int val[maxn];
int cost[maxn];
int dp[maxm];
int n, m,maxv;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m){
        maxv = 0;
        for (int i = 1; i <= n;++i){
            cin >> val[i] >> cost[i];
            maxv = maxv > val[i] ? maxv : val[i];
        }
        int sm = m;
        m += maxv;
        dp[0] = 0;
        for (int i = 1; i <= m;++i)
            dp[i] = INT_MAX;
        for (int i = 1; i <= n;++i){
            for (int j = val[i]; j <= m;++j){
                if(dp[j-val[i]]!=INT_MAX)
                dp[j] = min(dp[j], dp[j - val[i]] + cost[i]);
            }
        }
        int ans = INT_MAX;
        for (int j = sm; j <= m;++j)
            ans = ans < dp[j] ? ans : dp[j];
        cout << ans << '\n';
    }
    return 0;
}