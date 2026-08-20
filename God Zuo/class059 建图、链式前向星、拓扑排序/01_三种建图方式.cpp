// 三种方式建图：邻接矩阵、邻接表(vector)、链式前向星
// 同时演示有向图和无向图的建立

#include <bits/stdc++.h>
using namespace std;

// 点的最大数量
const int MAXN = 11;

// 边的最大数量
// 只有链式前向星方式建图需要这个数量
// 注意如果无向图的最大数量是m条边，数量要准备m*2
// 因为一条无向边要加两条有向边
const int MAXM = 21;

// 边的数据结构：每条边 = (u, v, w)，表示 u -> v、边权 w
// edges 数组一律用 struct，不用 int edges[m][3]
struct Edge {
    int u, v, w;
};

// 邻接矩阵方式建图
int graph1[MAXN][MAXN];

// 邻接表方式建图
// graph2[i] = {{邻居, 边权}, ...}
vector<vector<pair<int, int>>> graph2;

// 链式前向星方式建图
int head[MAXN];
int nxt[MAXM];
int to[MAXM];

// 如果边有权重，那么需要这个数组
int weight[MAXM];

int cnt;

void build(int n) {
    // 邻接矩阵清空
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph1[i][j] = 0;
        }
    }
    // 邻接表清空和准备
    // 下标需要支持1~n，所以加入n+1个列表，0下标准备但不用
    graph2.clear();
    graph2.resize(n + 1);
    // 链式前向星清空
    cnt = 1;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
}

// 链式前向星加边
void addEdge(int u, int v, int w) {
    // u -> v , 边权重是w
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// 三种方式建立有向图带权图
void directGraph(int n, Edge edges[], int m) {
    // 邻接矩阵建图
    for (int i = 0; i < m; i++) {
        graph1[edges[i].u][edges[i].v] = edges[i].w;
    }
    // 邻接表建图
    for (int i = 0; i < m; i++) {
        graph2[edges[i].u].push_back({edges[i].v, edges[i].w});
    }
    // 链式前向星建图
    for (int i = 0; i < m; i++) {
        addEdge(edges[i].u, edges[i].v, edges[i].w);
    }
}

// 三种方式建立无向图带权图
void undirectGraph(int n, Edge edges[], int m) {
    // 邻接矩阵建图
    for (int i = 0; i < m; i++) {
        graph1[edges[i].u][edges[i].v] = edges[i].w;
        graph1[edges[i].v][edges[i].u] = edges[i].w;
    }
    // 邻接表建图
    for (int i = 0; i < m; i++) {
        graph2[edges[i].u].push_back({edges[i].v, edges[i].w});
        graph2[edges[i].v].push_back({edges[i].u, edges[i].w});
    }
    // 链式前向星建图
    for (int i = 0; i < m; i++) {
        addEdge(edges[i].u, edges[i].v, edges[i].w);
        addEdge(edges[i].v, edges[i].u, edges[i].w);
    }
}

void traversal(int n) {
    cout << "邻接矩阵遍历 :" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << graph1[i][j] << " ";
        }
        cout << endl;
    }
    cout << "邻接表遍历 :" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << "(邻居、边权) : ";
        for (auto& edge : graph2[i]) {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << endl;
    }
    cout << "链式前向星 :" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << "(邻居、边权) : ";
        // 注意这个for循环，链式前向星的方式遍历
        for (int ei = head[i]; ei > 0; ei = nxt[ei]) {
            cout << "(" << to[ei] << "," << weight[ei] << ") ";
        }
        cout << endl;
    }
}

int main() {
    // 理解了带权图的建立过程，也就理解了不带权图
    // 点的编号为1...n
    // 例子1自己画一下图，有向带权图，然后打印结果
    int n1 = 4;
    Edge edges1[] = { { 1, 3, 6 }, { 4, 3, 4 }, { 2, 4, 2 }, { 1, 2, 7 }, { 2, 3, 5 }, { 3, 1, 1 } };
    build(n1);
    directGraph(n1, edges1, 6);
    traversal(n1);
    cout << "==============================" << endl;
    // 例子2自己画一下图，无向带权图，然后打印结果
    int n2 = 5;
    Edge edges2[] = { { 3, 5, 4 }, { 4, 1, 1 }, { 3, 4, 2 }, { 5, 2, 4 }, { 2, 3, 7 }, { 1, 5, 5 }, { 4, 2, 6 } };
    build(n2);
    undirectGraph(n2, edges2, 7);
    traversal(n2);
    return 0;
}
