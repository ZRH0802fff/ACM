#include<bits/stdc++.h>
using namespace std;

const int maxn=500010;
int n;

int head[maxn];
int nxt[maxn<<1];
int to[maxn<<1];
int weight[maxn<<1];
int cnt;

int dist[maxn];
int ans[maxn];
int length;

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	memset(dist + 1, 0, n * sizeof(int));
	memset(ans + 1, 0, n * sizeof(int));
    length=0;
}

void addEdge(int u, int v, int w) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt++;
}

void dp(int u,int f){
    for(int e=head[u],v; e!=0; e=nxt[e]){
        v=to[e];
        if(v!=f) dp(v,u);
    }
    for(int e=head[u],v; e!=0; e=nxt[e]){
        v=to[e];
        if(v!=f){
            ans[u]=max(ans[u],dist[u]+dist[v]+weight[e]);
            dist[u]=max(dist[u],dist[v]+weight[e]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    build();
    for(int i=1,u,v,w ;i<n; ++i){
        cin>>u>>v>>w;
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dp(1,0);
    
    for(int i=1; i<=n; ++i){
        length=max(length,ans[i]);
    }
    cout<<length<<'\n';
    return 0;
}