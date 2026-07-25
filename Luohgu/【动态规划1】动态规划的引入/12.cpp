#include<bits/stdc++.h>
using namespace std;

int n, m;
int dp[20010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m;
    cin >> n;
    for (int i = 1,val,wei; i <= n; ++i){
        cin >> val;
        wei = val;
        for (int j = m; j >=wei; --j)
            dp[j] = max(dp[j], dp[j - wei] + val);
    }
    cout << m - dp[m] << '\n';
    return 0;
}


/*

题意：
    给出n个箱子的体积尽量的去填充m的体积，返回剩余空间的最大值
核心点：
    转化为01背包，每一个物品的价值和体积相同
    dp[i][j]表示选前i个物品，体积不超过j的最大价值
    dp[n][m]就是前n个物品体积不超过m的最大价值，又因为价值等于体积，所以就是前n个物品不超过m的最大体积
    最终答案就等于m-dp[m]

*/