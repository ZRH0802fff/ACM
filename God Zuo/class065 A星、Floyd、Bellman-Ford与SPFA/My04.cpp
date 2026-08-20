// Bellman-Ford + SPFA优化模版（洛谷）
// 给定n个点的有向图，请求出图中是否存在从顶点1出发能到达的负环
// 负环的定义是：一条边权之和为负数的回路
// 测试链接 : https://www.luogu.com.cn/problem/P3385
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法

#include<bits/stdc++.h>
using namespace std;

int T;
int n,m;
int head[2010];
int nxt[6010];
int to[6010];
int weight[6010];
int cnt;

int dt[2010];
int updatecnt[2010];
int dq[4000001];
int l,r;
bool enter[2010];

void build(){
    cnt=1;
    l=r=0;
    for(int i=1;i<=n;++i){
        head[i]=0;
        dt[i]=INT_MAX;
        updatecnt[i]=0;
        enter[i]=false;
    }
}

void addEdge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool spfa(){
    dt[1]=0;
    updatecnt[1]++;
    dq[r++]=1;
    enter[1]=true;
    while(l<r){
        int u=dq[l++];
        enter[u]=false;
        for(int ei=head[u],v,w;ei>0;ei=nxt[ei]){
            v=to[ei];
            w=weight[ei];
            if(dt[u]+w<dt[v]){
                dt[v]=dt[u]+w;
                if(!enter[v]){
                    if(++updatecnt[v]>n-1) return true;
                    dq[r++]=v;
                    enter[v]=true;
                }
            }
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T;
    for(int _=0;_<T;++_){
        cin>>n>>m;
        build();
        for(int i=0,u,v,w;i<m;++i){
            cin>>u>>v>>w;
            if(w>=0){
                addEdge(u,v,w);
                addEdge(v,u,w);
            }else{
                addEdge(u,v,w);
            }
        }
        cout<<(spfa()? "YES":"NO")<<'\n';
    }
    return 0;
}