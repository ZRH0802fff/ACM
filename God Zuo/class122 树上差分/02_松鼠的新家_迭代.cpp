// 松鼠的新家(迭代版)
// 有n个节点形成一棵树
// 给定一个由点编号组成的数组，表示松鼠依次要去往的地点
// 松鼠每走到一个节点都必须拿一个糖果，否则松鼠就停止前进
// 松鼠来到最后一个地点时不需要吃糖果
// 打印每个节点上至少准备多少糖果才能让松鼠依次走完数组里的节点
// 测试链接 : https://www.luogu.com.cn/problem/P3258
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

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
int ufe[MAXN][3];

int stackSize, u, f, e;

void push(int u, int f, int e) {
    ufe[stackSize][0] = u;
    ufe[stackSize][1] = f;
    ufe[stackSize][2] = e;
    stackSize++;
}

void pop() {
    --stackSize;
    u = ufe[stackSize][0];
    f = ufe[stackSize][1];
    e = ufe[stackSize][2];
}

void tarjan(int root) {
    stackSize = 0;
    push(root, 0, -1);
    while (stackSize > 0) {
        pop();
        if (e == -1) {
            visited[u] = true;
            e = headEdge[u];
        } else {
            e = edgeNext[e];
        }
        if (e != 0) {
            push(u, f, e);
            if (edgeTo[e] != f) {
                push(edgeTo[e], u, -1);
            }
        } else {
            for (int q = headQuery[u], v; q != 0; q = queryNext[q]) {
                v = queryTo[q];
                if (visited[v]) {
                    ans[queryIndex[q]] = find(v);
                }
            }
            unionfind[u] = f;
            father[u] = f;
        }
    }
}

// dfs方法的递归版改迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
void dfs(int root) {
    stackSize = 0;
    push(root, 0, -1);
    while (stackSize > 0) {
        pop();
        if (e == -1) {
            e = headEdge[u];
        } else {
            e = edgeNext[e];
        }
        if (e != 0) {
            push(u, f, e);
            if (edgeTo[e] != f) {
                push(edgeTo[e], u, -1);
            }
        } else {
            for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
                v = edgeTo[e];
                if (v != f) {
                    num[u] += num[v];
                }
            }
        }
    }
}

void compute(int n) {
    tarjan(1);
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
    dfs(1);
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
