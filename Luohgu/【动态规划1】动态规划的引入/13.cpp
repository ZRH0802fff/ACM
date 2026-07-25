#include<bits/stdc++.h>
using namespace std;

int n, m;
long long  dp[10000010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= n; ++i){
        long long wei, val;
        cin >> wei >> val;
        for (int j = wei; j <= m; ++j){
            dp[j] = max(dp[j], dp[j - wei] + val);
        }
    }
    cout << dp[m] << '\n';
    return 0;
}