#include <bits/stdc++.h>
using namespace std;

int n, m;
long long dp[55][55];
int MOD = 1000000007;

int main()
{
    cin >> n >> m;
    for (int j = 0; j < n; ++j)
        dp[0][j] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            dp[i][j] = 0;
            for (int k = 0; k < i; ++k)
            {
                dp[i][j] = (dp[i][j] + (dp[k][j - 1] * dp[i - k - 1][j - 1]) % MOD) % MOD;
            }
        }
    }
    cout << dp[n][m] << endl;
}