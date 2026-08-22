#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
const int maxm=1e5+10;

int head[maxn];
int nxt[maxm];
int to[maxm];
int cnt;
int n,m;
int ans[maxn];

void build(){
    cnt=1;
    for(int i=1;i<=n;++i){
        head[i]=0;
        ans[i]=0;
    }
}

void addEdge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int cur,int val){
    if(ans[cur]!=0) return;
    ans[cur]=val;
    for(int ei=head[cur],v;ei!=0;ei=nxt[ei]){
        v=to[ei];
        dfs(v,val);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    build();
    for(int i=0,u,v;i<m;++i){
        cin>>u>>v;
        addEdge(v,u);
    }

    for(int i=n;i>=1;--i){
        if(ans[i]==0){
            dfs(i,i);
        }
    }
    
    for(int i=1;i<n;++i){
        cout<<ans[i]<<' ';
    }
    cout<<ans[n]<<'\n';
    return 0;
}
