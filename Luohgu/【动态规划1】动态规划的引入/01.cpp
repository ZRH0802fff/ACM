#include<bits/stdc++.h>
using namespace std;

int n, w;
int dp[1005][10005];
int val[1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n;++i)
        cin >> val[i];
    for (int j = 0; j <= w;++j){
        dp[0][j] = 0x3f3f3f3f;
    }
    for (int i = 0; i <= n; ++i)
        dp[i][0] = 0;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= w; ++j){
            dp[i][j] = dp[i - 1][j];
            if(val[i]<=j){
                dp[i][j] = min(dp[i][j], dp[i][j - val[i]] + 1);
            }
        }
    }
    // for (int i = 0; i <= n;++i){
    //     for (int j = 0; j <= w;++j){
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
        cout << dp[n][w] << '\n';
    return 0;
}