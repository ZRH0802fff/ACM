// 树的直径模版(两遍dfs)
// 给定一棵树，边权可能为负，求直径长度
// 测试链接 : https://www.luogu.com.cn/problem/U81904
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 会有无法通过的用例，因为树上有负边

#include<bits/stdc++.h>
using namespace std;

const int maxn=500010;
int n;

int head[maxn];
int nxt[maxn<<1];
int to[maxn<<1];
int weight[maxn<<1];
int cnt;

int sta,ed;
int length;

int dist[maxn];
int last[maxn];

void addEdge(int u, int v, int w) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt++;
}

void build(){
    memset(head,0,sizeof(head));
    cnt=1;
}

void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int e=head[u],v; e!=0; e=nxt[e]){
        v=to[e];
        if(v!=f){
            dfs(v,u,weight[e]);
        }
    }
}

void road(){
    dfs(1,0,0);
    sta=1;
    for(int i=2;i<=n; ++i){
        if(dist[i]>dist[sta]) sta=i;
    }
    
    dfs(sta,0,0);
    ed=1;
    for(int i=2;i<=n;++i){
        if(dist[i]>dist[ed]) ed=i;
    }
    length=dist[ed];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    build();
    for(int i=1,u,v,w; i<n; ++i){
        cin>>u>>v>>w;
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    road();
    cout<<length<<'\n';
    return 0;
}