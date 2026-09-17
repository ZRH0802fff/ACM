// 运输计划，java递归版
// 有n个节点，给定n-1条边使其连接成一棵树，每条边有正数边权
// 给定很多运输计划，每个运输计划(a,b)表示从a去往b
// 每个运输计划的代价就是沿途边权和，运输计划之间完全互不干扰
// 你只能选择一条边，将其边权变成0
// 你的目的是让所有运输计划代价的最大值尽量小
// 返回所有运输计划代价的最大值最小能是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2680
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// 本节课Code05_TransportPlan3文件就是C++的实现

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300001;

const int MAXM = 300001;

int n;

int m;

// num[i] : i节点和其父节点的边，有多少代价>=limit的运输计划用到
int num[MAXN];

// 链式前向星建图需要
int headEdge[MAXN];

int edgeNext[MAXN << 1];

int edgeTo[MAXN << 1];

int edgeWeight[MAXN << 1];

int tcnt;

// tarjan算法需要
int headQuery[MAXN];

int queryNext[MAXM << 1];

int queryTo[MAXM << 1];

int queryIndex[MAXM << 1];

int qcnt;

bool visited[MAXN];

int unionfind[MAXN];

int quesu[MAXM];

int quesv[MAXM];

// distance[i] : 头节点到i号点的距离，tarjan算法过程中更新
int dist[MAXN];

// lca[i] : 第i号运输计划的两端点lca，tarjan算法过程中更新
int lca[MAXM];

// cost[i] : 第i号运输计划代价是多少，tarjan算法过程中更新
int cost[MAXM];

// 所有运输计划的最大代价，tarjan算法过程中更新
int maxCost;

void build() {
    tcnt = qcnt = 1;
    memset(headEdge + 1, 0, n * sizeof(int));
    memset(headQuery + 1, 0, n * sizeof(int));
    memset(visited + 1, 0, n * sizeof(bool));
    for (int i = 1; i <= n; i++) {
        unionfind[i] = i;
    }
    maxCost = 0;
}

void addEdge(int u, int v, int w) {
    edgeNext[tcnt] = headEdge[u];
    edgeTo[tcnt] = v;
    edgeWeight[tcnt] = w;
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

void tarjan(int u, int f, int w) {
    visited[u] = true;
    dist[u] = dist[f] + w;
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            tarjan(v, u, edgeWeight[e]);
        }
    }
    for (int e = headQuery[u], v, i; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            i = queryIndex[e];
            lca[i] = find(v);
            cost[i] = dist[u] + dist[v] - 2 * dist[lca[i]];
            maxCost = max(maxCost, cost[i]);
        }
    }
    unionfind[u] = f;
}

// 至少要减少多少边权
int atLeast;

// 超过要求的运输计划有几个
int beyond;

bool dfs(int u, int f, int w) {
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            if (dfs(v, u, edgeWeight[e])) {
                return true;
            }
        }
    }
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            num[u] += num[v];
        }
    }
    return num[u] == beyond && w >= atLeast;
}

// 只能把一条边的权值变成0
// 还要求每个运输计划的代价都要<=limit
// 返回能不能做到
bool f(int limit) {
    atLeast = maxCost - limit;
    memset(num + 1, 0, n * sizeof(int));
    beyond = 0;
    for (int i = 1; i <= m; i++) {
        if (cost[i] > limit) {
            num[quesu[i]]++;
            num[quesv[i]]++;
            num[lca[i]] -= 2;
            beyond++;
        }
    }
    return beyond == 0 || dfs(1, 0, 0);
}

int compute() {
    tarjan(1, 0, 0);
    int l = 0, r = maxCost, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (f(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    build();
    cin >> m;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        quesu[i] = u;
        quesv[i] = v;
        addQuery(u, v, i);
        addQuery(v, u, i);
    }
    cout << compute() << "\n";
    return 0;
}
