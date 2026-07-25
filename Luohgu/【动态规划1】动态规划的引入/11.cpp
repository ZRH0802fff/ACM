#include<bits/stdc++.h>
using namespace std;

int n, m, cn, cm;
int marr[9][2];
int dx[8] = {2, 2, 1, -1, -2, -2, -1, 1};
int dy[8] = {1, -1, -2, -2, -1, 1, 2, 2};
long long dp[23][23];

bool isM(int x,int y){
    for (int i = 0,tx,ty; i < 9;++i){
        tx = marr[i][0];
        ty = marr[i][1];
        if(tx==x && ty==y){
            return true;
        }
    }
    return false;
}

int main(){
    cin >> n >> m >> cn >> cm;
    marr[0][0] = cn;
    marr[0][1] = cm;
    for (int i = 1; i < 9; ++i){
        int x = cn + dx[i-1];
        int y = cm + dy[i-1];
        marr[i][0] = x;
        marr[i][1] = y;
    }
    dp[0][0] = 1;
    for (int i = 0; i <= n; ++i){
        for (int j = 0; j <= m; ++j){
            if(!isM(i,j)){
                if(i>0)
                    dp[i][j] += dp[i - 1][j];
                if(j>0)
                    dp[i][j] += dp[i][j - 1];
            }
        }
    }
    cout << dp[n][m] << '\n';
    return 0;
}