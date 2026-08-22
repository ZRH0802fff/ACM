#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
const int maxm=1e6+10;
vector<int> grid[maxn];
bool vis[maxn];
int n,m;

int l,r;
int qe[maxn];


void dfs(int i){
    if(vis[i]) return;
    cout<<i<<' ';
    vis[i]=true;
    for(int to:grid[i]){
        dfs(to);
    }
}

void bfs(){
    qe[r++]=1;
    vis[1]=true;
    cout<<1<<' ';
    while(l<r){
        int u=qe[l++];
        for(int to:grid[u]){
            if(!vis[to]){
                vis[to]=true;
                qe[r++]=to;
                cout<<to<<' ';
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0,u,v;i<m;++i){
        cin>>u>>v;
        grid[u].push_back(v);
    }
    for(int i=1;i<=n;++i){
        sort(grid[i].begin(),grid[i].end());
    }
    dfs(1);
    cout<<'\n';
    for(int i=0;i<=n;++i) vis[i]=false;
    bfs();
    return 0;
}