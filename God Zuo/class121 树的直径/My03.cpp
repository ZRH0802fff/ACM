// 造公园
// 一共n个节点，编号1~n，有m条边连接，边权都是1
// 所有节点可能形成多个连通区，每个连通区保证是树结构
// 有两种类型的操作
// 操作 1 x   : 返回x到离它最远的点的距离
// 操作 2 x y : 如果x和y已经连通，那么忽略
//              如果不连通，那么执行连通操作，把x和y各自的区域连通起来
//              并且要保证连通成的大区域的直径长度最小
// 测试链接 : https://www.luogu.com.cn/problem/P2195

#include<bits/stdc++.h>
using namespace std;

const int maxn=300010;
int n,m,q;
int head[maxn];
int nxt[maxn<<1];
int to[maxn<<1];
int cnt;

int father[maxn];
int dist[maxn];
int diameter[maxn];

void build(){
    cnt=1;
    memset(head,0,sizeof(head));
    for(int i=1;i<=n; ++i) father[i]=i;
    memset(dist,0,sizeof(dist));
    memset(diameter,0,sizeof(diameter));
}

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

int find(int i){
    if(i!=father[i]){
        father[i]=find(father[i]);
    }
    return father[i];
}

void dp(int u,int f){
    for(int e=head[u],v;e!=0; e=nxt[e]){
        v=to[e];
        if(v!=f){
            dp(v,u);
            diameter[u]=max(diameter[u],max(diameter[v],dist[u]+dist[v]+1));
            dist[u]=max(dist[u],dist[v]+1);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>q;
    build();
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
        u=find(u);
        v=find(v);
        father[u]=v;
    }
    for(int i=1;i<=n;++i){
        if(i==father[i]){
            dp(i,0);
        }
    }
    for(int i=1,op,x,y;i<=q; ++i){
        cin>>op;
        if(op==1){
           cin>>x;
           x=find(x);
           cout<<diameter[x]<<'\n'; 
        }else{
            cin>>x>>y;
            x=find(x);
            y=find(y);
            if(x!=y){
                father[x]=y;
                diameter[y] = max((diameter[x] + 1) / 2 + (diameter[y] + 1) / 2 + 1,max(diameter[x], diameter[y]));
            }
        }
    }
    return 0;
}