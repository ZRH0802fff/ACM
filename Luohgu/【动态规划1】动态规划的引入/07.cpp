#include<bits/stdc++.h>
using namespace std;

struct Point{
    int val;
    int x, y;
} p[10010];

int n, m,ans=0;
int grid[105][105];
int dp[105][105];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0,idx=0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> grid[i][j];
            p[idx].val = grid[i][j];
            p[idx].x = i;
            p[idx++].y = j;
        }
    }
    sort(p, p + n*m, [](const Point &a, const Point &b)
         { return a.val < b.val; });
    for (int i = 0,x,y,md; i < n*m; ++i){
        md = 0;
        x = p[i].x;
        y = p[i].y;
        for (int dt = 0,sx,sy; dt < 4;++dt){
            sx = x + dx[dt];
            sy = y + dy[dt];
            if(sx>=0 && sx<n && sy>=0 && sy<m && grid[sx][sy]<p[i].val && dp[sx][sy]>md){
                md = dp[sx][sy];
            }
        }
        dp[x][y] = md + 1;
        if(md+1>ans)
            ans = md + 1;
    }
    cout << ans << '\n';
    return 0;
}