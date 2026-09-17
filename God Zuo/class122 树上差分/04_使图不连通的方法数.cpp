// 边差分实战
// 使图不连通的方法数
// 有n个节点，给定n-1条老边使其连接成一棵树，再给定m条新边额外加在树上
// 你可以切断两条边让这个图不连通，切断的两条边必须是一条老边和一条新边
// 返回方法数
// 测试链接 : http://poj.org/problem?id=3417
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

const int LIMIT = 17;

int power;

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

int n, m;

int num[MAXN];

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int cnt;

int deep[MAXN];

int stjump[MAXN][LIMIT];

int ans;

void build() {
    power = log2(n);
    memset(num + 1, 0, n * sizeof(int));
    cnt = 1;
    memset(head + 1, 0, n * sizeof(int));
    ans = 0;
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
    for (int e = head[u], v, w; e != 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            w = 0 + num[v];
            if (w == 0) {
                ans += m;
            } else if (w == 1) {
                ans += 1;
            } else {
                ans += 0;
            }
            num[u] += num[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    build();
    cin >> m;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    for (int i = 1, u, v, anc; i <= m; i++) {
        cin >> u >> v;
        anc = lca(u, v);
        num[u]++;
        num[v]++;
        num[anc] -= 2;
    }
    dfs2(1, 0);
    cout << ans << "\n";
    return 0;
}
