// 运输计划，java迭代版
// 有n个节点，给定n-1条边使其连接成一棵树，每条边有正数边权
// 给定很多运输计划，每个运输计划(a,b)表示从a去往b
// 每个运输计划的代价就是沿途边权和，运输计划之间完全互不干扰
// 你只能选择一条边，将其边权变成0
// 你的目的是让所有运输计划代价的最大值尽量小
// 返回所有运输计划代价的最大值最小能是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2680
// 提交以下的code，提交时请把类名改成"Main"
// 有时候可以完全通过，有时候会有一个测试用例超时
// 因为这道题根据C++的运行时间，制定通过标准，根本没考虑java的用户
// 本节课Code05_TransportPlan3文件就是C++的实现
// 两个版本的逻辑完全一样，C++版本可以通过所有测试

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300001;

const int MAXM = 300001;

int n;

int m;

int num[MAXN];

int headEdge[MAXN];

int edgeNext[MAXN << 1];

int edgeTo[MAXN << 1];

int edgeWeight[MAXN << 1];

int tcnt;

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

// find方法的递归版改迭代版
int stk[MAXN];

int find(int i) {
    int size = 0;
    while (i != unionfind[i]) {
        stk[size++] = i;
        i = unionfind[i];
    }
    while (size > 0) {
        unionfind[stk[--size]] = i;
    }
    return i;
}

// tarjan方法的递归版改迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
int ufwe[MAXN][4];

int stackSize, u, fa, w, e;

void push(int u, int fa, int w, int e) {
    ufwe[stackSize][0] = u;
    ufwe[stackSize][1] = fa;
    ufwe[stackSize][2] = w;
    ufwe[stackSize][3] = e;
    stackSize++;
}

void pop() {
    --stackSize;
    u = ufwe[stackSize][0];
    fa = ufwe[stackSize][1];
    w = ufwe[stackSize][2];
    e = ufwe[stackSize][3];
}

void tarjan(int root) {
    stackSize = 0;
    push(root, 0, 0, -1);
    while (stackSize > 0) {
        pop();
        if (e == -1) {
            visited[u] = true;
            dist[u] = dist[fa] + w;
            e = headEdge[u];
        } else {
            e = edgeNext[e];
        }
        if (e != 0) {
            push(u, fa, w, e);
            if (edgeTo[e] != fa) {
                push(edgeTo[e], u, edgeWeight[e], -1);
            }
        } else {
            for (int q = headQuery[u], v, i; q != 0; q = queryNext[q]) {
                v = queryTo[q];
                if (visited[v]) {
                    i = queryIndex[q];
                    lca[i] = find(v);
                    cost[i] = dist[u] + dist[v] - 2 * dist[lca[i]];
                    maxCost = max(maxCost, cost[i]);
                }
            }
            unionfind[u] = fa;
        }
    }
}

// 至少要减少多少边权
int atLeast;

// 超过要求的运输计划有几个
int beyond;

// dfs方法的递归版改迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
bool dfs(int root) {
    stackSize = 0;
    push(root, 0, 0, -1);
    while (stackSize > 0) {
        pop();
        if (e == -1) {
            e = headEdge[u];
        } else {
            e = edgeNext[e];
        }
        if (e != 0) {
            push(u, fa, w, e);
            if (edgeTo[e] != fa) {
                push(edgeTo[e], u, edgeWeight[e], -1);
            }
        } else {
            for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
                v = edgeTo[e];
                if (v != fa) {
                    num[u] += num[v];
                }
            }
            if (num[u] == beyond && w >= atLeast) {
                return true;
            }
        }
    }
    return false;
}

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
    return beyond == 0 || dfs(1);
}

int compute() {
    tarjan(1);
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
