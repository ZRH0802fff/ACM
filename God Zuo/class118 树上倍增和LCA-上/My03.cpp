// tarjan算法解法
// 测试链接 : https://www.luogu.com.cn/problem/P3379

#include<bits/stdc++.h>
using namespace std;

const int maxn = 500010;

int n, m, s;

int headE[maxn];
int nxtE[maxn << 1];
int toE[maxn << 1];
int cntE;

int headQ[maxn];
int nxtQ[maxn << 1];
int toQ[maxn << 1];
int cntQ;
int idxQ[maxn << 1];

bool vis[maxn];
int father[maxn];
int ans[maxn];

void build(){
    cntE = cntQ = 1;
    memset(headE, 0, sizeof(headE));
    memset(headQ, 0, sizeof(headQ));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) father[i]=i;
}

void addEdge(int u,int v){
    nxtE[cntE] = headE[u];
    toE[cntE] = v;
    headE[u] = cntE++;
}

void addQuery(int u,int v, int i){
    nxtQ[cntQ] = headQ[u];
    toQ[cntQ] = v;
    idxQ[cntQ] = i;
    headQ[u] = cntQ++;
}

int find(int i){
    if(i !=father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

void tarjan(int u,int f){
    vis[u] = true;
    for (int e = headE[u], v; e != 0; e = nxtE[e]){
        v = toE[e];
        if(v!=f){
            tarjan(v, u);
            father[v] = u;
        }
    }

    for (int e = headQ[u], v; e != 0; e=nxtQ[e]){
        v = toQ[e];
        if(vis[v]){
            ans[idxQ[e]] = find(v);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    build();
    for (int i = 1, u, v; i < n; ++i){
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1, u, v; i <= m; ++i){
        cin >> u >> v;
        addQuery(u, v, i);
        addQuery(v, u, i);
    }

    tarjan(s, 0);
    for (int i=1; i <= m; ++i){
        cout << ans[i] << '\n';
    }
    return 0;
}