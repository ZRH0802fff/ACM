#include<bits/stdc++.h>
using namespace std;

int n, w;
int val[10005];
int dp[10005];
int mod = 1e9 + 7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n;++i)
        cin >> val[i];
    for (int i = 0; i <= n;++i)
        dp[i] == 0;
    dp[0] = 1;
    for (int i = 1; i <= n; ++i){
        for (int j = val[i]; j <= w;++j){
            dp[j] = (dp[j] + dp[j - val[i]]) % mod;
        }
    }
    cout << dp[w] << '\n';
    return 0;
}