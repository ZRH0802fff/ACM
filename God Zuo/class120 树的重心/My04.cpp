// 删增边使其重心唯一
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 现在希望重心是唯一的节点，调整的方式是先删除一条边、然后增加一条边
// 如果树上只有一个重心，需要删掉连接重心的任意一条边，再把这条边加上(否则无法通过已经实测)
// 如果树上有两个重心，调整的方式是先删除一条边、然后增加一条边，使重心是唯一的
// 如果方案有多种，打印其中一种即可
// 比如先删除节点3和节点4之间的边，再增加节点4和节点7之间的边，那么打印:
// "3 4"
// "4 7"
// 测试链接 : https://www.luogu.com.cn/problem/CF1406C
// 测试链接 : https://codeforces.com/problemset/problem/1406/C


#include<bits/stdc++.h>
using namespace std;

const int maxn=100010;
const int maxm=200010;

int t,n;
int head[maxn];
int nxt[maxm];
int to[maxm];
int cnt;

int size[maxn];
int centers[2];
int m;

int lf,lfFa;

void build(){
    memset(head,0,sizeof(head));
    cnt=1;
    m=0;
}

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

void dfs(int u,int f){
    size[u]=1;
    int maxsub=0;
    for(int e=head[u],v;e!=0;e=nxt[e]){
        v=to[e];
        if(v!=f){
            dfs(v,u);
            size[u]+=size[v];
            maxsub=max(maxsub,size[v]);
        }
    }
    maxsub=max(maxsub,n-size[u]);
    if(maxsub<=n/2){
        centers[m++]=u;
    }
}

void find(int u,int f){
    for(int e=head[u]; e!=0;e=nxt[e]){
        if(to[e]!=f){
            find(to[e],u);
            return ;
        }
    }
    lf=u;
    lfFa=f;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        cin>>n;
        build();
        for(int i=0,u,v;i<n; ++i){
            cin>>u>>v;
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,0);
        if(m==1){
            cout << centers[0] << " " << to[head[centers[0]]] << "\n";
			cout << centers[0] << " " << to[head[centers[0]]] << "\n";
        }else{
            find(centers[0],centers[1]);
            cout<<lfFa<<' '<<lf<<'\n';
            cout<<centers[1]<<lf<<'\n';
        }
    }
    return 0;
}