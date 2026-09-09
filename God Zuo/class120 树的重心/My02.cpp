// 教父
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 返回所有重心点
// 树的重心第二种求解方式
// 以某个节点为根时，每颗子树的节点数不超过总节点数的一半，那么这个节点是重心
// 测试链接 : http://poj.org/problem?id=3107

#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;

int n;
int head[maxn];
int nxt[maxn<<1];
int to[maxn<<1];
int cnt;

int size[maxn];
int maxsub[maxn];

int center[2];
int m;

void build(){
    memset(head,0,sizeof(head));
    cnt=1;
    m=0;
}

void addEdge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int f){
    size[u]=1;
    maxsub[u]=0;
    for(int e=head[u],v; e!=0; e=nxt[e]){
        v=to[e];
        if(v!=f){
            dfs(v,u);
            size[u]+=size[v];
            maxsub[u]=max(maxsub[u],size[v]);
        }
    }
    maxsub[u]=max(maxsub[u],n-size[u]);
    // if(maxsub[u]<=n/2){
    //     center[m++]=u;
    // }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1,u,v;i<n; ++i){
        cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,0);
    
    for(int i=0;i<n; ++i){
        if(maxsub[i]<=n/2){
            center[m++]=i;
        }
    }
    if (m == 1) {
		cout << center[0] << "\n";
	} else { // m == 2
		cout << center[0] << " " << center[1] << "\n";
	}
	return 0;
}