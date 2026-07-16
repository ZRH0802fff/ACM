// 分组背包(模版)
// 给定一个正数m表示背包的容量，有n个货物可供挑选
// 每个货物有自己的体积(容量消耗)、价值(获得收益)、组号(分组)
// 同一个组的物品只能挑选1件，所有挑选物品的体积总和不能超过背包容量
// 怎么挑选货物能达到价值最大，返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1757
// 核心: 同组物品只选1件; 先按组号排序; 每组内枚举所有物品, dp[i][j]=max(dp[i-1][j], dp[i-1][j-cost]+val)
// 坑点: 空间压缩时 j 必须倒序(01背包), 且每组内 k 的枚举要在 j 循环内部

#include<bits/stdc++.h>
using namespace std;

struct Pd{
    int w, val, gp;
} arr[1005];

int dp1[1005][1005];
int dp2[1005];
int n, m;

int f1(){
    int teams = 1;
    for (int i = 2; i <= n;++i){
        if(arr[i-1].gp!=arr[i].gp)
            teams++;
    }
    for (int sta = 1, end = 2, i = 1; sta <= n;++i){
        while(end<=n && arr[end].gp==arr[sta].gp)
            end++;
        for (int j = 0; j <= m;++j){
            dp1[i][j] = dp1[i - 1][j];
            for (int k = sta; k < end;++k){
                if(j>=arr[k].w){
                    dp1[i][j] = max(dp1[i][j], dp1[i - 1][j - arr[k].w] + arr[k].val);
                }
            }
        }
        sta = end++;
    }
    return dp1[teams][m];
}

int f2(){
    for (int i = 0; i <= m;++i)
        dp2[i] = 0;
    for (int sta = 1, ed = 2; sta <= n;){
        while(ed<=n && arr[ed].gp==arr[sta].gp)
            ed++;
        for (int j = m; j >= 0; --j){
            for (int k = sta; k < ed;++k){
                if (j >= arr[k].w){
                    dp2[j] = max(dp2[j], dp2[j - arr[k].w] + arr[k].val);
                }
            }
        }
        sta = ed++;
    }
    return dp2[m];
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> m >> n){
        for (int i = 1; i<=n; ++i){
            cin >> arr[i].w >> arr[i].val >> arr[i].gp;
        }
        sort(arr + 1, arr + n + 1, [](const Pd &a, const Pd &b)
             { return a.gp < b.gp; });
        cout << f1() << '\n';
    }
    return 0;
}