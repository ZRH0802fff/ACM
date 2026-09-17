// 最小化旅行的价格总和(tarjan方法求lca)
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

const int MAXM = 101;

int price[MAXN];

int num[MAXN];

int headEdge[MAXN];

int edgeNext[MAXN << 1];

int edgeTo[MAXN << 1];

int tcnt;

int headQuery[MAXN];

int queryNext[MAXM << 1];

int queryTo[MAXM << 1];

int queryIndex[MAXM << 1];

int qcnt;

bool visited[MAXN];

int unionfind[MAXN];

int father[MAXN];

int ans[MAXM];

void build(int n) {
    memset(num + 1, 0, n * sizeof(int));
    tcnt = qcnt = 1;
    memset(headEdge + 1, 0, n * sizeof(int));
    memset(headQuery + 1, 0, n * sizeof(int));
    memset(visited + 1, 0, n * sizeof(bool));
    for (int i = 1; i <= n; i++) {
        unionfind[i] = i;
    }
}

void addEdge(int u, int v) {
    edgeNext[tcnt] = headEdge[u];
    edgeTo[tcnt] = v;
    headEdge[u] = tcnt++;
}

void addQuery(int u, int v, int i) {
    queryNext[qcnt] = headQuery[u];
    queryTo[qcnt] = v;
    queryIndex[qcnt] = i;
    headQuery[u] = qcnt++;
}

int find(int i) {
    if (i != unionfind[i]) {
        unionfind[i] = find(unionfind[i]);
    }
    return unionfind[i];
}

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            tarjan(v, u);
        }
    }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            ans[queryIndex[e]] = find(v);
        }
    }
    unionfind[u] = f;
    father[u] = f;
}

void dfs(int u, int f) {
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            dfs(v, u);
        }
    }
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            num[u] += num[v];
        }
    }
}

int no, yes;

void dp(int u, int f) {
    int n = price[u] * num[u];
    int y = (price[u] / 2) * num[u];
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
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
        int m = ts.size();
        for (int i = 0, j = 1; i < m; i++, j++) {
            addQuery(ts[i][0] + 1, ts[i][1] + 1, j);
            addQuery(ts[i][1] + 1, ts[i][0] + 1, j);
        }
        tarjan(1, 0);
        for (int i = 0, j = 1, u, v, lca, lcafather; i < m; i++, j++) {
            u = ts[i][0] + 1;
            v = ts[i][1] + 1;
            lca = ans[j];
            lcafather = father[lca];
            num[u]++;
            num[v]++;
            num[lca]--;
            num[lcafather]--;
        }
        dfs(1, 0);
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
