#include<bits/stdc++.h>
using namespace std;

const int maxn=1505;
const int maxm=50010;

int n,m,ans;
int head[maxn];
int nxt[maxm];
int to[maxm];
int weight[maxm];
int cnt;

int dt[maxn];
int qe[4000010];
int l,r;
bool enter[maxn];

void build(){
    for(int i=0;i<=n;++i){
        head[i]=0;
        enter[i]=false;
        dt[i]=INT_MAX;
    }
    cnt=1;
    l=r=0;
}

void addEdgee(int u,int v, int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    build();
    for(int i=0,u,v,w;i<m;++i){
        cin>>u>>v>>w;
        addEdgee(u,v,-w);
    }

    dt[1]=0;
    qe[r++]=1;
    enter[1]=true;
    while(l<r){
        int u=qe[l++];
        enter[u]=false;
        for(int ei=head[u],v,w;ei>0;ei=nxt[ei]){
            v=to[ei];
            w=weight[ei];
            if(dt[u]+w<dt[v]){
                dt[v]=dt[u]+w;
                if(!enter[v]){
                    qe[r++]=v;
                    enter[v]=true;
                }
            }
        }
    }
    cout<<(dt[n]==INT_MAX?-1:-dt[n])<<'\n';
    return 0;
}