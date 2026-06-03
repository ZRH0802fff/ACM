#include<bits/stdc++.h>
using namespace std;

int n, girph[33][33];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int i, int j){
    if(i<0 || j<0 || i>=n || j>=n || girph[i][j]!=0)
        return;
    girph[i][j] = 2;
    for (int t = 0; t < 4;++t)
        dfs(i + dx[t], j + dy[t]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n;++i){
        for (int j = 0; j < n;++j)
            cin >> girph[i][j];
    }
    for (int i = 0; i < n;++i){
        if (girph[0][i] == 0)
            dfs(0, i); 
        if (girph[n - 1][i] == 0)
            dfs(n - 1, i); 
        if (girph[i][0] == 0)
            dfs(i, 0); 
        if (girph[i][n - 1] == 0)
            dfs(i, n - 1);
    }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (girph[i][j] == 2)
                    cout << 0 << ' ';
                else if (girph[i][j] == 0)
                    cout << 2 << " ";
                else
                    cout << 1 << ' ';
            }
            cout << "\n";
        }
    return 0;
}