// 静态空间实现 : 链式前向星 + 反向索引堆
// 测试链接 : https://www.luogu.com.cn/problem/P4779
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include<bits/stdc++.h>
using namespace std;

const int MAXN=100010;
const int MAXM=200010;
int n,m,s;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

int hq[MAXN];
int where[MAXN];
int hqsize;
int dt[MAXN];


void build(){
    cnt=1;
    hqsize=0;
    for(int i=1;i<=n;++i){
        head[i]=0;
        where[i]=-1;
        dt[i]=INT_MAX;
    }
}

void addEdge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool isEmpty(){
    return hqsize==0;
}

void swap(int i,int j){
    int tmp=hq[i];
    hq[i]=hq[j];
    hq[j]=tmp;
    where[hq[i]]=i;
    where[hq[j]]=j;
}

void hqinsert(int i){
    while(dt[hq[i]]<dt[hq[(i-1)/2]]){
        swap(i,(i-1)/2);
        i=(i-1)/2;
    }
}

void add_updete_ingore(int v,int c){
    if(where[v]==-1){
        hq[hqsize]=v;
        where[v]=hqsize++;
        dt[v]=c;
        hqinsert(where[v]);
    }else if(where[v]>=0){
        dt[v]=min(dt[v],c);
        hqinsert(where[v]);
    }
}

void heapify(int i){
    int l=i*2+1;
    while(l<hqsize){
        int best=(l+1<hqsize && dt[hq[l+1]]<dt[hq[l]]) ? l+1 : l;
        best=dt[hq[best]]<dt[hq[i]] ? best : i;
        if(best==i) break;
        swap(best,i);
        i=best;
        l=i*2+1;
    }
}

int pop(){
    int ans=hq[0];
    swap(0,--hqsize);
    heapify(0);
    where[ans]=-2;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>s;
    build();
    for(int i=0,u,v,w;i<m;++i){
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }

    add_updete_ingore(s,0);
    while(!isEmpty()){
        int v=pop();
        for(int ei=head[v];ei>0;ei=nxt[ei]){
            add_updete_ingore(to[ei],dt[v]+weight[ei]);
        }
    }

    for(int i=1;i<n;++i){
        cout<<dt[i]<<' ';
    }
    cout<<dt[n]<<'\n';
    return 0;
}