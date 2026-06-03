//注意起点标记已走过
//注意是采用的0-base下标还是1-base下标
#include<bits/stdc++.h>
using namespace std;

int n, m, t, sx, sy, fx, fy,ans;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool memo[10][10];

void dfs(int i,int j){
    if(i==fx && j==fy){
        ans += 1;
        return;
    }
    for (int k = 0; k < 4;++k){
        int nx = i + dx[k];
        int ny = j + dy[k];
        if(nx>=1 && nx<=n && ny>=1 and ny<=m && memo[nx][ny]==true){
            memo[nx][ny] = false;
            dfs(nx, ny);
            memo[nx][ny] = true;
        }
    }
}

int main(){
    cin >> n >> m >> t;
    cin >> sx >> sy >> fx >> fy;
    for (int i = 1; i <= n;++i){
        for (int j = 1; j <= m;++j)
            memo[i][j] = true;
    }
    for (int i = 0; i < t;++i){
        int tx, ty;
        cin >> tx >> ty;
        memo[tx][ty] = false;
    }
    memo[sx][sy] = false;
    dfs(sx, sy);
    cout << ans << endl;
    return 0;
}