// 树上点差分模版(递归版)
// 有n个节点形成一棵树，一开始所有点权都是0
// 给定很多操作，每个操作(a,b)表示从a到b路径上所有点的点权增加1
// 所有操作完成后，返回树上的最大点权
// 测试链接 : https://www.luogu.com.cn/problem/P3128
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code01_MaxFlow2文件

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50001;

const int LIMIT = 16;

int power;

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

int num[MAXN];

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int cnt;

int deep[MAXN];

int stjump[MAXN][LIMIT];

void build(int n) {
    power = log2(n);
    memset(num + 1, 0, n * sizeof(int));
    cnt = 1;
    memset(head + 1, 0, n * sizeof(int));
}

void addEdge(int u, int v) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs1(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e != 0; e = nxt[e]) {
        if (to[e] != f) {
            dfs1(to[e], u);
        }
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs2(v, u);
        }
    }
    for (int e = head[u], v; e != 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            num[u] += num[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    build(n);
    int m;
    cin >> m;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    for (int i = 1, u, v, anc, lcafather; i <= m; i++) {
        cin >> u >> v;
        anc = lca(u, v);
        lcafather = stjump[anc][0];
        num[u]++;
        num[v]++;
        num[anc]--;
        num[lcafather]--;
    }
    dfs2(1, 0);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, num[i]);
    }
    cout << mx << "\n";
    return 0;
}
