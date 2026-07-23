#include<bits/stdc++.h>
using namespace std;

int m, n;
int w[105];
int v[105];
int dp[1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= n; ++i){
        cin >> w[i] >> v[i];
    }
    for (int i = 1; i <= n; ++i){
        for (int j = m; j >= w[i]; --j){
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    cout << dp[m] << '\n';
    return 0;
}