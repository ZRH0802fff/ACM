// 飞行路线（语言提供的堆）
// Alice和Bob现在要乘飞机旅行，他们选择了一家相对便宜的航空公司
// 该航空公司一共在n个城市设有业务，设这些城市分别标记为0 ~ n−1
// 一共有m种航线，每种航线连接两个城市，并且航线有一定的价格
// Alice 和 Bob 现在要从一个城市沿着航线到达另一个城市，途中可以进行转机
// 航空公司对他们这次旅行也推出优惠，他们可以免费在最多k种航线上搭乘飞机
// 那么 Alice 和 Bob 这次出行最少花费多少
// 测试链接 : https://www.luogu.com.cn/problem/P4568
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法

#include<bits/stdc++.h>
using namespace std;

int n,m,k,s,t;
int head[10010];
int nxt[100010];
int to[100010];
int weight[100010];
int cnt;

int dt[10010][11];
int vis[10010][11];
struct Record{
    int u,use,cost;
};
struct Cmp{
    bool operator()(const Record& a, const Record& b) const {
        return a.cost>b.cost;
    }
};
priority_queue<Record,vector<Record>,Cmp> hq;

void build(){
    cnt=1;
    for(int i=0;i<n;++i){
        head[i]=0;
        for(int j=0;j<=k;++j){
            dt[i][j]=INT_MAX;
            vis[i][j]=false;
        }
    }
    hq=priority_queue<Record,vector<Record>,Cmp>();
}

void adEdge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int dijkstra(){
    dt[s][0]=0;
    hq.push({s,0,0});
    while(!hq.empty()){
        Record rec=hq.top();
        hq.pop();
        int u=rec.u;
        int use=rec.use;
        int cost=rec.cost;
        if(vis[u][use]) continue;
        vis[u][use]=true;
        if(u==t) return cost;
        for(int ei=head[u],v,w;ei>0; ei=nxt[ei]){
            v=to[ei];
            w=weight[ei];
            if(use<k && dt[v][use+1]>dt[u][use]){
                dt[v][use+1]=dt[u][use];
                hq.push({v,use+1,dt[v][use+1]});
            }
            if(dt[v][use]>dt[u][use]+w){
                dt[v][use]=dt[u][use]+w;
                hq.push({v,use,dt[v][use]});
            }
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>k>>s>>t;
    build();
    for(int i=0,u,v,w;i<m;++i){
        cin>>u>>v>>w;
        adEdge(u,v,w);
        adEdge(v,u,w);
    }
    cout<<dijkstra()<<'\n';
    return 0;
}