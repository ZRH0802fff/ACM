// 所有直径的公共部分(递归版)
// 给定一棵树，边权都为正
// 打印直径长度、所有直径的公共部分有几条边
// 测试链接 : https://www.luogu.com.cn/problem/P3304

#include<bits/stdc++.h>
using namespace std;

const int maxn=200010;

int n;
int head[maxn];
int nxt[maxn];
int to[maxn];
int weight[maxn];
int cnt;

int sta,ed;
long long dist[maxn];
int last[maxn];

long long length;
bool longPath[maxn];
int comEdge;

void build(){
    cnt=1;
    memset(head,0,sizeof(head));
    memset(longPath,0,sizeof(longPath));
}

void addEdge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f,long long c){
    last[u]=f;
    dist[u]=c;
    for(int e=head[u];e!=0;e=nxt[e]){
        if(to[e]!=f){
            dfs(to[e],u,c+weight[e]);
        }
    }
}

void road(){
    dfs(1,0,0);
    sta=1;
    for(int i=2;i<=n;++i){
        if(dist[i]>dist[sta]){
            sta=i;
        }
    }
    dfs(sta,0,0);
    ed=1;
    for(int i=2;i<=n;++i){
        if(dist[i]>dist[ed]){
            ed=i;
        }
    }
    length=dist[ed];
}

long long maxdistEx(int u,int f,long long c){
    long long ans=c;
    for(int e=head[u],v;e!=0;e=nxt[e]){
        v=to[e];
        if(!longPath[v] && v!=f){
            ans=max(ans,maxdistEx(v,u,c+weight[e]));
        }
    }
    return ans;
}

void slove(){
    road();
    for(int i=ed; i!=0; i=last[i]){
        longPath[i]=true;
    }
    int l=sta;
    int r=ed;
    long long maxDist;
    for(int i=last[ed];i!=sta;i=last[i]){
        maxDist=maxdistEx(i,0,0);
        if(maxDist==length-dist[i]){
            r=i;
        }
        if(maxDist==dist[i] && l==sta){
            l=i;
        }
    }
    if(l==r){
        comEdge=0;
    }else{
        comEdge=1;
        for(int i=last[r];i!=l;i=last[i]){
            comEdge++;
        }
    }
}

int main(){
    cin >> n;
	build();
	for (int i = 1, u, v, w; i < n; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	slove();
    cout<<length<<'\n'<<comEdge<<'\n';
    return 0;
}