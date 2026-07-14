#include<bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
using namespace std;
int n, m;
int dp[5010][5010];

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n;++i){
        dp[i][1] = m;
    }
    for (int i = 2; i <= n;++i){
        for (int j = 2; j <= m;++j){
            dp[i][j] = (int)(((unsigned long long)dp[i - 1][j] * j) % MOD);
            dp[i][j] = (int)((unsigned long long)((dp[i - 1][j - 1] * (m - j + 1)) % MOD + dp[i][j]) % MOD);
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}