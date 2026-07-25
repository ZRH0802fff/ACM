#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e6 + 7;
int n, m;
int dp[105][105];
int a[105];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n;++i)
        cin >> a[i];
    for (int i = 0; i <= n;++i){
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m;++j){
            for (int k = 0; k <= min(j,a[i]); ++k){
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % MOD;
            }
        }
    }
    cout << dp[n][m] << '\n';
    return 0;
}

/*
题意：
    n种花摆m盆，第i种花有ai盆
    摆花时同一种花放一起，且不同种类的花按序号依次摆
    求不同的方案数
核心点：
    不要陷入多重背包的陷阱
    dp[i][j]表示用前i种花摆j盆
    dp[i][j]=sum dp[i][j-n*ai] 0<=n<=ai
*/