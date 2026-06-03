#include <iostream>
#include <vector>
#include <algorithm> // 用于 std::fill

using namespace std;

// 点的最大数量
const int MAXN = 11;

// 边的最大数量
// 只有链式前向星方式建图需要这个数量
// 注意如果无向图的最大数量是m条边，数量要准备m*2
const int MAXM = 21;

// 1. 邻接矩阵方式建图
int graph1[MAXN][MAXN];

// 2. 邻接表方式建图
// 在 C++ 中，对于带权重的邻接表，通常使用 pair<int, int> 来存 {邻居, 权重}
vector<vector<pair<int, int>>> graph2;

// 3. 链式前向星方式建图
int head[MAXN];
// 注意：C++ 标准库里有 std::next 函数，为避免冲突，通常将 next 数组改名为 nxt
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// 初始化/清空图
void build(int n)
{
    // 邻接矩阵清空
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            graph1[i][j] = 0;
        }
    }

    // 邻接表清空和准备
    // assign 会自动调整 vector 大小为 n+1，并将每个元素初始化为空的 vector
    graph2.assign(n + 1, vector<pair<int, int>>());

    // 链式前向星清空
    cnt = 1;
    // std::fill 用法：将 head 数组的 1~n 范围清零
    fill(head + 1, head + n + 1, 0);
}

// 链式前向星加边
void addEdge(int u, int v, int w)
{
    // u -> v , 边权重是w
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// 三种方式建立有向图带权图
void directGraph(const vector<vector<int>> &edges)
{
    // 邻接矩阵建图
    for (const auto &edge : edges)
    {
        graph1[edge[0]][edge[1]] = edge[2];
    }

    // 邻接表建图
    for (const auto &edge : edges)
    {
        // C++11 支持直接使用 {} 构造 pair 插入
        graph2[edge[0]].push_back({edge[1], edge[2]});
    }

    // 链式前向星建图
    for (const auto &edge : edges)
    {
        addEdge(edge[0], edge[1], edge[2]);
    }
}

// 三种方式建立无向图带权图
void undirectGraph(const vector<vector<int>> &edges)
{
    // 邻接矩阵建图
    for (const auto &edge : edges)
    {
        graph1[edge[0]][edge[1]] = edge[2];
        graph1[edge[1]][edge[0]] = edge[2];
    }

    // 邻接表建图
    for (const auto &edge : edges)
    {
        graph2[edge[0]].push_back({edge[1], edge[2]});
        graph2[edge[1]].push_back({edge[0], edge[2]});
    }

    // 链式前向星建图
    for (const auto &edge : edges)
    {
        addEdge(edge[0], edge[1], edge[2]);
        addEdge(edge[1], edge[0], edge[2]);
    }
}

// 遍历打印
void traversal(int n)
{
    cout << "邻接矩阵遍历 :" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << graph1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "邻接表遍历 :" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << "(邻居、边权) : ";
        for (const auto &edge : graph2[i])
        {
            // pair 通过 .first 和 .second 访问
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << endl;
    }

    cout << "链式前向星 :" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << "(邻居、边权) : ";
        // 链式前向星的方式遍历
        for (int ei = head[i]; ei > 0; ei = nxt[ei])
        {
            cout << "(" << to[ei] << "," << weight[ei] << ") ";
        }
        cout << endl;
    }
}

int main()
{
    // 例子1：有向带权图
    int n1 = 4;
    vector<vector<int>> edges1 = {
        {1, 3, 6}, {4, 3, 4}, {2, 4, 2}, {1, 2, 7}, {2, 3, 5}, {3, 1, 1}};
    build(n1);
    directGraph(edges1);
    traversal(n1);

    cout << "==============================" << endl;

    // 例子2：无向带权图
    int n2 = 5;
    vector<vector<int>> edges2 = {
        {3, 5, 4}, {4, 1, 1}, {3, 4, 2}, {5, 2, 4}, {2, 3, 7}, {1, 5, 5}, {4, 2, 6}};
    build(n2);
    undirectGraph(edges2);
    traversal(n2);

    return 0;
}