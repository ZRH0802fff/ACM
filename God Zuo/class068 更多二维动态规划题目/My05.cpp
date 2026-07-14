#include<bits/stdc++.h>
using namespace std;

string s1, s2;
int n, m;
int dp[1010][1010];

int main(){
    cin >> s1;
    cin >> s2;
    n = s1.length();
    m = s2.length();
    for (int i = 0; i <= m;++i)
        dp[i][0] = i;
    for (int i = 1; i <= n;++i){
        for (int j = 1; j <= m;++j){
            if(s1[i-1]==s2[i-1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j]=dp[i-1][j]+1;
        }
    }
    int ans = INT_MAX;
    for (int j = 0; j <= m;++j){
        if(dp[n][j]<ans)
            ans = dp[n][j];
    }
    cout << ans << endl;
    return 0;
}