#include<bits/stdc++.h>
using namespace std;
int n;
string INF = "yizhong";
char grid[110][110];
bool memo[110][110];
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

void dfs(int x,int y,int op,int tal){
    for (int i = 0; i < 5;++i){
        x = x + dx[op];
        y = y + dy[op];
        tal += 1;
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != INF[tal - 1])
            return;
    }
    for (int i = 0; i < 7;++i){
        memo[x][y] = true;
        x -= dx[op];
        y -= dy[op];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n;++i){
        for (int j = 0; j < n;++j)
            cin >> grid[i][j];
    }
    for (int i = 0; i < n;++i){
        for (int j = 0; j < n;++j){
            if (grid[i][j]=='y'){
                for (int k = 0; k < 8;++k){
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if(nx>=0 && nx<n && ny>=0 && ny<n && grid[nx][ny]=='i'){
                        dfs(nx, ny, k, 2);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (memo[i][j]){
                cout << grid[i][j];
            }else{
                cout << '*';
            }
        }
        cout << '\n';
    }
    return 0;
}