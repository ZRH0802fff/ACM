// 拓扑排序模版（牛客）
// 邻接表建图（动态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include<bits/stdc++.h>
using namespace std;

int head[200010];
int nxt[200010];
int to[200010];
int cnt;

int pq[200010];
int l,r;
int idge[200010];
int ans[200010];
int n,m;

void build(int n){
    cnt=1;
    for(int i=0;i<=n;++i){
        head[i]=0;
        idge[i]=0;
    }
}

void addEdge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    build(n);
    for(int i=0,u,v;i<m;++i){
        cin>>u>>v;
        addEdge(u,v);
        idge[v]++;
    }

    l=r=0;
    for(int i=1;i<=n; ++i){
        if(idge[i]==0) pq[r++]=i;
    }

    int fill=0;
    while(l<r){
        int cur=pq[l++];
        ans[fill++]=cur;
        for(int ei=head[cur];ei!=0;ei=nxt[ei]){
            if(--idge[to[ei]]==0){
                pq[r++]=to[ei];
            }
        }
    }

    if(fill==n){
        for(int i=0;i<n-1;++i){
            cout<<ans[i]<<' ';
        }
        cout<<ans[n-1]<<'\n';
    }else{
        cout<<-1<<'\n';
    }
    return 0;
}