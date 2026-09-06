#include<bits/stdc++.h>
using namespace std;

int n, m;

vector<int> grid[1010];
bool vis[1010];
int cur_zhan[1010];
bool is_bian[1010][1010];

int indegree[1010];
struct Zhan{
    int id, lv;
};
Zhan q[1000010];
int l, r;
int mlv = 1;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1,s; i <= m; ++i){
        cin >> s;
        memset(vis, 0, 1010);
        for (int j = 1; j <= s; ++j){
            cin >> cur_zhan[j];
            vis[cur_zhan[j]] = true;
        }
        for (int i = cur_zhan[1]; i <= cur_zhan[s]; ++i){
            if(vis[i]) continue;
            for (int j = 1; j <= s; ++j){
                if(!is_bian[i][cur_zhan[j]]){
                    indegree[cur_zhan[j]]++;
                    grid[i].push_back(cur_zhan[j]);
                    is_bian[i][cur_zhan[j]] = true;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i){
        if(indegree[i]==0){
            q[r++] = {i, 1};
        }
    }
    while(l<r){
        Zhan sta = q[l++];
        for (int i = 0; i < grid[sta.id].size(); ++i){
            indegree[grid[sta.id][i]]--;
            if (indegree[grid[sta.id][i]]==0){
                q[r++] = {grid[sta.id][i], sta.lv+1};
                mlv = max(mlv, sta.lv + 1);
            }
        }
    }

    cout << mlv << '\n';
    return 0;
}