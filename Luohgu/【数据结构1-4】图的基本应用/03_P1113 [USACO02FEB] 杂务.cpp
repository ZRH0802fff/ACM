#include<bits/stdc++.h>
using namespace std;

const int maxn=1e4+10;
const int maxm=1e6+10;
int n;
int ans[maxn][2];
int fans;

int head[maxn];
int nxt[maxm];
int to[maxm];
int cnt;

int indegree[maxn];
int l,r;
int qe[maxn];

void build(){
    for(int i=1;i<=n;++i){
        head[i]=0;
        indegree[i]=0;
    }
    cnt=1;
    l=r=0;
}

void addEdge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    build();
    for(int i=1,u,v,w;i<=n;++i){
        cin>>v>>w;
        ans[v][0]=w;
        while(cin>>u){
            if(u==0) break;
            addEdge(u,v);
            indegree[v]++;
        }
    }

    for(int i=1;i<=n;++i){
        if(indegree[i]==0){
            qe[r++]=i;
        }
    }
    while(l<r){
        int u=qe[l++];
        fans=max(fans,ans[u][1]+ans[u][0]);
        for(int ei=head[u],v;ei!=0;ei=nxt[ei]){
            v=to[ei];
            ans[v][1]=max(ans[v][1],ans[u][1]+ans[u][0]);
            if(--indegree[v]==0){
                qe[r++]=v;
            }
        }
    }
    cout<<fans<<'\n';
    return 0;
}