#include<bits/stdc++.h>
using namespace std;

int n, m;
int dp[10010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    dp[0] = 1;
    for (int i = 1,val; i <= n; ++i){
        cin >> val;
        for (int j = m; j >= val;--j){
            dp[j] += dp[j-val];
        }
    }
    cout << dp[m] << '\n';
    return 0;
}