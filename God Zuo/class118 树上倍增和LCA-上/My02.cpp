// 树上倍增解法
// 测试链接 : https://www.luogu.com.cn/problem/P3379
#include<bits/stdc++.h>
using namespace std;

const int maxn = 500010;
const int limit = 20;

int n, m, s;
int head[maxn];
int nxt[maxn<<1];
int to[maxn<<1];
int cnt;

int deep[maxn];
int st[maxn][limit];
int power;

void build(){
    power = log2(n);
    cnt = 1;
    memset(head, 0, sizeof(head));
}

void addEdge(int u,int v){
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u,int f){
    deep[u] = deep[f] + 1;
    st[u][0] = f;
    for (int p = 1; p <= power; ++p){
        st[u][p] = st[st[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e != 0; e=nxt[e]){
        if(to[e]!=f){
            dfs(to[e], u);
        }
    }
}

int lca(int a,int b){
    if(deep[a] < deep[b]){
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
    dfs(s, 0);
    for (int i = 1, a, b; i <= m; ++i){
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
    return 0;
}