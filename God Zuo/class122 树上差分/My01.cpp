// 树上点差分模版(递归版)
// 有n个节点形成一棵树，一开始所有点权都是0
// 给定很多操作，每个操作(a,b)表示从a到b路径上所有点的点权增加1
// 所有操作完成后，返回树上的最大点权
// 测试链接 : https://www.luogu.com.cn/problem/P3128
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈

#include<bits/stdc++.h>
using namespace std;

const int maxn = 50010;
const int limit = 16;

int n, k;
int power;
int num[maxn];

int head[maxn];
int nxt[maxn << 1];
int to[maxn << 1];
int cnt;

int deep[maxn];
int st[maxn][limit];

int ans;

void build(){
    power=log2(n);
    memset(num, 0, sizeof(num));
    cnt = 1;
    memset(head, 0, sizeof(head));
    ans = 0;
}

void addEdge(int u,int v){
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs1(int u,int f){
    deep[u] = deep[f] + 1;
    st[u][0] = f;
    for (int p = 1; p <= power; ++p){
        st[u][p] = st[st[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e != 0; e=nxt[e]){
        if(to[e]!=f){
            dfs1(to[e], u);
        }
    }
}

int lca(int a,int b){
    if(deep[a]<deep[b]){
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = power; p >= 0; --p){
        if(deep[st[a][p]]>=deep[b]){
            a = st[a][p];
        }
    }
    if(a==b){
        return a;
    }
    for (int p = power; p >= 0; --p){
        if(st[a][p]!=st[b][p]){
            a = st[a][p];
            b = st[b][p];
        }
    }
    return st[a][0];
}

void dfs2(int u,int f){
    for (int e = head[u], v; e != 0; e=nxt[e]){
        v = to[e];
        if(v!=f){
            dfs2(v, u);
            num[u] += num[v];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    build();
    for (int i = 1, u, v; i < n; ++i){
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    for (int i = 1, u, v, anc, lcaf; i <= k; ++i){
        cin >> u >> v;
        anc = lca(u, v);
        lcaf=st[anc][0];
        num[u]++;
        num[v]++;
        num[anc]--;
        num[lcaf]--;
    }
    dfs2(1, 0);

    for (int i = 0; i <= n; ++i){
        ans = max(ans, num[i]);
    }
    cout << ans << '\n';
    return 0;
}