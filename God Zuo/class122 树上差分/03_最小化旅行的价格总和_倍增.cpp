// 最小化旅行的价格总和(倍增方法求lca)
// 有n个节点形成一棵树，每个节点上有点权，再给定很多路径
// 每条路径有开始点和结束点，路径代价就是从开始点到结束点的点权和
// 所有路径的代价总和就是旅行的价格总和
// 你可以选择把某些点的点权减少一半，来降低旅行的价格总和
// 但是要求选择的点不能相邻
// 返回旅行的价格总和最少能是多少
// 测试链接 : https://leetcode.cn/problems/minimize-the-total-price-of-the-trips/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51;

const int LIMIT = 6;

int power;

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

int price[MAXN];

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

int no, yes;

void dp(int u, int f) {
    int n = price[u] * num[u];
    int y = (price[u] / 2) * num[u];
    for (int e = head[u], v; e != 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dp(v, u);
            n += min(no, yes);
            y += no;
        }
    }
    no = n;
    yes = y;
}

class Solution {
public:
    // 题目给定点的编号从0号点开始，代码中调整成从1号点开始
    int minimumTotalPrice(int n, vector<vector<int>>& es, vector<int>& ps, vector<vector<int>>& ts) {
        build(n);
        for (int i = 0, j = 1; i < n; i++, j++) {
            price[j] = ps[i];
        }
        for (auto& edge : es) {
            addEdge(edge[0] + 1, edge[1] + 1);
            addEdge(edge[1] + 1, edge[0] + 1);
        }
        dfs1(1, 0);
        int u, v, anc, lcafather;
        for (auto& trip : ts) {
            u = trip[0] + 1;
            v = trip[1] + 1;
            anc = lca(u, v);
            lcafather = stjump[anc][0];
            num[u]++;
            num[v]++;
            num[anc]--;
            num[lcafather]--;
        }
        dfs2(1, 0);
        dp(1, 0);
        return min(no, yes);
    }
};

int main() {
    Solution sol;
    // n = 4, 边 : 0-1, 0-2, 1-3
    // price = [100, 50, 20, 40]
    // trips = [[3,1],[1,2],[3,2]]
    // 期望输出 : 330
    int n = 4;
    vector<vector<int>> es = { {0, 1}, {0, 2}, {1, 3} };
    vector<int> ps = { 100, 50, 20, 40 };
    vector<vector<int>> ts = { {3, 1}, {1, 2}, {3, 2} };
    cout << sol.minimumTotalPrice(n, es, ps, ts) << "\n";
    return 0;
}
