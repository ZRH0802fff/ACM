#include <bits/stdc++.h>
using namespace std;

int n, w;
int dp[10005];
int val[1005];
int MOD = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    dp[0] = 1;
    for (int i = 1; i <= w; ++i){
        for (int j = 1; j <= n;++j){
            if (i >= val[j]){
                dp[i] = (dp[i] + dp[i - val[j]]) % MOD;
            }
        }
    }
        cout << dp[w] << '\n';
    return 0;
}