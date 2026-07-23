#include <bits/stdc++.h>
using namespace std;

int n, w;
int dp[10005];
int val[105];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; ++i){
        for (int j = val[i]; j <= w; ++j){
            dp[j] = min(dp[j], dp[j - val[i]] + 1);
        }
    }
    cout << dp[w] << '\n';
    return 0;
}