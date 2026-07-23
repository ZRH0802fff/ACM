#include<bits/stdc++.h>
using namespace std;

int n;
int griph[1005][1005];
int dp[1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= i; ++j){
            cin >> griph[i][j];
        }
    }
    for (int i = 1; i <= n; ++i)
        dp[i] = griph[n][i];
    for (int i = n-1; i > 0; --i){
        for (int j = 1; j <= i; ++j){
            dp[j] = max(dp[j], dp[j + 1]) + griph[i][j];
        }
    }
    cout << dp[1] << '\n';
    return 0;
}