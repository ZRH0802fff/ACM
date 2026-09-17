// 松鼠的新家(递归版)
// 有n个节点形成一棵树
// 给定一个由点编号组成的数组，表示松鼠依次要去往的地点
// 松鼠每走到一个节点都必须拿一个糖果，否则松鼠就停止前进
// 松鼠来到最后一个地点时不需要吃糖果
// 打印每个节点上至少准备多少糖果才能让松鼠依次走完数组里的节点
// 测试链接 : https://www.luogu.com.cn/problem/P3258
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code02_SquirrelHome2文件

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300001;

// 依次去往节点的顺序
int travel[MAXN];

// 每个节点需要分配多少糖果
int num[MAXN];

// 链式前向星建图
int headEdge[MAXN];

int edgeNext[MAXN << 1];

int edgeTo[MAXN << 1];

int tcnt;

// 以下结构都是tarjan算法所需要的
int headQuery[MAXN];

int queryNext[MAXN << 1];

int queryTo[MAXN << 1];

int queryIndex[MAXN << 1];

int qcnt;

bool visited[MAXN];

// unionfind数组是tarjan算法专用的并查集结构
int unionfind[MAXN];

// father数组不用作并查集，就是记录每个节点的父亲节点
int father[MAXN];

// ans数组是tarjan算法的输出结果，记录每次旅行两端点的最低公共祖先
int ans[MAXN];

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

void compute(int n) {
    tarjan(1, 0);
    for (int i = 1, u, v, lca, lcafather; i < n; i++) {
        u = travel[i];
        v = travel[i + 1];
        lca = ans[i];
        lcafather = father[lca];
        num[u]++;
        num[v]++;
        num[lca]--;
        num[lcafather]--;
    }
    dfs(1, 0);
    for (int i = 2; i <= n; i++) {
        num[travel[i]]--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    build(n);
    for (int i = 1; i <= n; i++) {
        cin >> travel[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i < n; i++) {
        addQuery(travel[i], travel[i + 1], i);
        addQuery(travel[i + 1], travel[i], i);
    }
    compute(n);
    for (int i = 1; i <= n; i++) {
        cout << num[i] << "\n";
    }
    return 0;
}
