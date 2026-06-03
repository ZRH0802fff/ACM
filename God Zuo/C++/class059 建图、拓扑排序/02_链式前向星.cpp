#include <iostream>

using namespace std;

// 数组大小习惯性多开几个，防止越界
const int MAXN = 200005;
const int MAXM = 200005;

// 建图相关，链式前向星
int head[MAXN];
// ⚠️ 注意：C++中为了避免和标准库的 std::next 冲突，这里一定要改名叫 nxt
int nxt[MAXM];
int to[MAXM];
int cnt;

// 拓扑排序，用数组模拟队列
// ⚠️ 注意：避免和 std::queue 冲突，这里简写为 q
int q[MAXN];
int l, r;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

// 初始化函数
void build(int n)
{
    cnt = 1;
    // 每次针对当前测试用例的大小进行清空即可，不要清空整个 200005 的数组，否则多组测试用例时会超时
    for (int i = 0; i <= n; i++)
    {
        head[i] = 0;
        indegree[i] = 0;
    }
}

// 用链式前向星建图
void addEdge(int f, int t)
{
    nxt[cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt++;
}

// 拓扑排序核心逻辑
bool topoSort()
{
    l = r = 0;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q[r++] = i;
        }
    }
    int fill = 0;
    while (l < r)
    {
        int cur = q[l++];
        ans[fill++] = cur;
        // 用链式前向星的方式，遍历 cur 的相邻节点
        for (int ei = head[cur]; ei != 0; ei = nxt[ei])
        {
            if (--indegree[to[ei]] == 0)
            {
                q[r++] = to[ei];
            }
        }
    }
    // 如果收集到的节点数等于总节点数，说明图无环，拓扑排序成功
    return fill == n;
}

int main()
{
    // ⚠️ C++ 最核心的快读优化，等价于 Java 的 StreamTokenizer
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // C++ 中处理多组输入 (EOF) 最优雅的写法
    while (cin >> n >> m)
    {
        build(n);
        for (int i = 0; i < m; i++)
        {
            int f, t;
            cin >> f >> t;
            addEdge(f, t);
            indegree[t]++;
        }

        if (!topoSort())
        {
            cout << -1 << "\n";
        }
        else
        {
            for (int i = 0; i < n - 1; i++)
            {
                cout << ans[i] << " ";
            }
            cout << ans[n - 1] << "\n";
        }
    }

    return 0;
}