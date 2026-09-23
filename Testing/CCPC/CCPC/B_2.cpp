#include<bits/stdc++.h>
using namespace std;

int n, w;
int val[6];
int wei[6];
int dp[6][36];
int k;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    n = 6;
    cin >> k;
    for (int i = 1; i <= n; ++i){
        cin >> val[i];
        val[i]++;
        wei[i] = i;
    }
    for (int i = 0; i < 6; ++i){
        dp[i][0] = 0;
    }
    for (int j = 0; j <= 36; ++j){
        dp[0][j] = 100;
    }
     for (int i = 1; i < 6; ++i){
        for (int j = val[i]; j <= 36; ++j){
            dp[i][j] = min(dp[i - 1][j], dp[i][j - val[i]] + wei[i]);
        }
    }
    for (int i = 0; i < 6; ++i){
        for (int j = 0; j <= 36; ++j){
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
    // for (int j = 19; j <= 36; ++j){
    //     if(dp[5][j]==k){

    //     }
    // }
    return 0;
}