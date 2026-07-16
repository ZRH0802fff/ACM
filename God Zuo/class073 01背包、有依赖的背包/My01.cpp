// 01背包(模版)
// 给定一个正数t，表示背包的容量
// 有m个货物，每个货物可以选择一次
// 每个货物有自己的体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1048
#include <bits/stdc++.h>
using namespace std;

int cost[105];
int val[105];
int dp1[105][1005];
int dp2[1005];
int t, n;

int f1(){
    for (int i = 1; i <= n; ++i){
        for (int j = 0; j <= t;++j){
            dp1[i][j] = dp1[i - 1][j];
            if(cost[i]<=j){
                dp1[i][j] = max(dp1[i][j], dp1[i-1][j - cost[i]] + val[i]);
            }
        }
    }
    return dp1[n][t];
}

int f2(){
    for (int i = 1; i <= n;++i){
        for (int j = t; j >= cost[i]; --j){
            dp2[j] = max(dp2[j], dp2[j - cost[i]] + val[i]);
        }
    }
    return dp2[t];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t >> n;
    for (int i = 1; i <= n;++i)
        cin >> cost[i]>>val[i];
    cout << f1() << '\n';
    return 0;
}