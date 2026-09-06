#include<bits/stdc++.h>
using namespace std;

int k, n, m,ans;
int row[105];
vector<int> grid[1005];
bool vis[1005];
int mk[1005];

void dfs(int x){
    vis[x] = true;
    mk[x]++;
    for (int i = 0; i < grid[x].size();++i){
        if(!vis[grid[x][i]]){
            dfs(grid[x][i]);
        }
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> k >> n >> m;
    for (int i = 0; i < k; ++i){
        cin >> row[i];
    }
    for (int i = 0,u,v; i < m; ++i){
        cin >> u >> v;
        grid[u].push_back(v);
    }
    for (int i = 1; i <= k; ++i){
        for (int j = 1; j <= n; ++j){
            vis[j] = false;
            dfs(row[i]);
        }
    }
    for (int i = 1; i <= n; ++i){
        if(mk[i]==k)
            ans++;
    }
    cout << ans << '\n';
    return 0;
}