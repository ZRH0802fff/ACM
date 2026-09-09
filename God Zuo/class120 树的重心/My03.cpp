// 牛群聚集(递归版)
// 一共有n个节点，编号1~n，每个点有牛的数量
// 一共有n-1条边把所有点连通起来形成一棵树，每条边有权值
// 想把所有的牛汇聚在一点，希望走过的总距离最小
// 返回总距离最小是多少
// 利用重心的性质：
// 树上的边权如果都>=0，不管边权怎么分布，所有节点都走向重心的总距离和最小
// 测试链接 : https://www.luogu.com.cn/problem/P2986

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=100010;
int n;
int cow[maxn];
int cowsum;

int head[maxn];
int nxt[maxn<<1];
int to[maxn<<1];
int weight[maxn<<1];
int cnt;

int best,center;
int size[maxn];
int path[maxn];
ll ans;

void build(){
    for(int i=1; i<=n; ++i){
        cowsum+=cow[i];
    }
    memset(head,0,sizeof(head));
    cnt=1;
    best=INT_MAX;
    memset(path,0,sizeof(path));
    ans=0;
}

void addEdge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f){
    int maxsub=0;
    size[u]=cow[u];
    for(int e=head[u],v;e!=0; e=nxt[e]){
        v=to[e];
        if(v!=f){
            dfs(v,u);
            size[u]+=size[v];
            maxsub=max(maxsub,size[v]);
        }
    }
    maxsub=max(maxsub,cowsum-size[u]);
    if(maxsub<best){
        best=maxsub;
        center=u;
    }
}

void setPath(int u,int f){
    for(int e=head[u],v;e!=0;e=nxt[e]){
        v=to[e];
        if(v!=f){
            path[v]=path[u]+weight[e];
            setPath(v,u);
        }
    }
}

void solve(){
    dfs(1,0);
    setPath(center,0);
    for(int i=1;i<=n; ++i){
        ans+=(ll)cow[i]*path[i];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>cow[i];
    build();
    for(int i=1,u,v,w;i<n;++i){
        cin>>u>>v>>w;
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    solve();
    cout<<ans<<'\n';
    return 0;
}