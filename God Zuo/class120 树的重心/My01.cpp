// 平衡行为
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 返回重心点，返回重心点最大子树的节点数
// 树的重心第一种求解方式
// 以某个节点为根时，最大子树的节点数最少，那么这个节点是重心
// 测试链接 : http://poj.org/problem?id=1655

#include<bits/stdc++.h>
using namespace std;

const int maxn=20010;

int T;
int n;

int head[maxn];
int nxt[maxn<<1];
int to[maxn<<1];
int cnt;

int size[maxn];
int center;
int best;

void addEdge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void build(){
    cnt=1;
    memset(head,0,sizeof(head));
    best=INT_MAX;
}

void dfs(int u,int f){
    size[u]=1;
    int maxsub=0;
    for(int e=head[u],v;e!=0; e=nxt[e]){
        v=to[e];
        if(v!=f){
            dfs(v,u);
            size[u]+=size[v];
            maxsub=max(maxsub,size[v]);
        }
    }
    maxsub=max(maxsub,n-size[u]);
    if(maxsub<best || (maxsub==best && u<center)){
        best=maxsub;
        center=u;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T;
    while(T--){
        cin>>n;
        build();
        for(int i=1,u,v;i<n; ++i){
            cin>>u>>v;
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,0);
        cout<<center<<' '<<best<<'\n';
    }
    return 0;
}