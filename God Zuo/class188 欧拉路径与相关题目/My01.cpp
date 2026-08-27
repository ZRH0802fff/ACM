// 有向图的欧拉路径
// 图中有n个点，m条有向边，每条边给出两个端点
// 如果存在欧拉路径，输出字典序最小的结果，如果不存在打印No
// 1 <= n <= 10^5
// 1 <= m <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P7771

#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
const int maxm=2e5+10;
int n,m;

struct Edge{
    int u,v;
};
bool EdgeCmp(Edge e1,Edge e2){
    if (e1.u!=e2.u) return e1.u<e2.u;
    return e1.v<e2.v;
}
Edge edgeArr[maxm];

int head[maxn];
int nxt[maxm];
int to[maxm];
int cntg;

int cur[maxn];
int outDeg[maxn];
int inDeg[maxn];

int path[maxm];
int cntp;

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void connect(){
    sort(edgeArr+1,edgeArr+m+1,EdgeCmp);
    for(int l=1,r=1;l<=m;l=++r){
        while(r+1<=m && edgeArr[l].u==edgeArr[r+1].u) r++;
        for(int i=r,u,v;i>=l;--i){
            u=edgeArr[i].u;
            v=edgeArr[i].v;
            outDeg[u]++;
            inDeg[v]++;
            addEdge(u,v);
        }
    }
    for(int i=1;i<=n;++i){
        cur[i]=head[i];
    }
}

int directSta(){
    int sta=-1,end=-1;
    for(int i=1,v;i<=n;++i){
        v=outDeg[i]-inDeg[i];
        if(v<-1 || v>1 || (v==1 && sta!=-1) || (v==-1 && end!=-1)) return -1;
        if(v==1) sta=i;
        if(v==-1) end=i;
    }
    if((sta==-1)^(end==-1)) return -1;
    if(sta!=-1) return sta;
    for(int i=1;i<=n;++i){
        if(outDeg[i]>0) return i;
    }
    return -1;
}

void euler(int u){
    for(int e=cur[u];e>0;e=cur[u]){
        cur[u]=nxt[e];
        euler(to[e]);
    }
    path[++cntp]=u;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        cin>>edgeArr[i].u>>edgeArr[i].v;
    }
    connect();
    int sta=directSta();
    if(sta==-1){
        cout<<"No"<<'\n';
    }else{
        euler(sta);
        if(cntp!=m+1){
            cout<<"No\n";
        } else {
            for(int i=cntp;i>=1;--i){
                cout<<path[i]<<' ';
            }
            cout<<'\n';
        }
    }
    return 0;
}