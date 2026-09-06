#include<bits/stdc++.h>
using namespace std;

int n;
string s;
int MOD = 998244353;
int dp[5005][5005];

int f(int l,int r){
    if(l==r)
        return 1;
    if(dp[l][r]!=-1)
        return dp[l][r];
    int ans;
    if(s[l]==s[r]){
        ans=(f(l+1,r)+f(l,r-1))
    }
}

int main(){
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; ++i){
        dp[i][i] = 1;

    }
}