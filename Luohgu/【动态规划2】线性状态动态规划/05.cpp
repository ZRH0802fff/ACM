#include<bits/stdc++.h>
using namespace std;

string s;
int n,lens;
int dp[45][100010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s >> n;
    lens = s.length();
    for (int j = 0; j < n;++j){
        dp[0][j] = INT_MAX;
    }
    for (int i = 0; i < lens; ++i){
        dp[i][0] = INT_MAX;
    }
    dp[0][(int)s[0]] = 0;
    for (int i = 1; i < lens;++i){
        int num = (int)s[i];
        for (int j = num; j <= n;++j){
            dp[i][j] = min(dp[i - 1][j], dp[i][j - num]+1);
        }
    }
    cout << dp[lens][n] << '\n';
    return 0;
}