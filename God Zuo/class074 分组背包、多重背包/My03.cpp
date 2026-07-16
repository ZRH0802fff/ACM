// 完全背包(模版)
// 给定一个正数t，表示背包的容量
// 有m种货物，每种货物可以选择任意个
// 每种货物都有体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1616
// 核心: 与01背包唯一区别——j从cost[i]到t正序(表示同一物品可多次选)
//       dp[i][j] = max(dp[i-1][j], dp[i][j-cost[i]]+val[i])
//       注意对比: 01背包是dp[i-1][j-cost], 完全背包是dp[i][j-cost]
// 坑点: ①j必须正序(不是倒序!) ②数据量大, dp用long long ③二维版本会MLE


#include<bits/stdc++.h>
using namespace std;

const int maxm = 10005;
const int maxn = 10000010;
int cost[maxm];
int val[maxm];
long long dp[maxn];
int t, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>t>>m){
        for (int i = 1; i <= m;++i){
            cin >> cost[i] >> val[i];
        }
        for (int i = 0; i <= t;++i)
            dp[i] = 0;
        for (int i = 1; i <= m;++i){
            for (int j = cost[i]; j <= t;++j){
                dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
            }
        }
        cout << dp[t] << '\n';
    }
    return 0;
}