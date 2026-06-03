#include <iostream>
#include <vector>
#include <queue> // 引入优先队列的头文件

using namespace std;

// 习惯性多开几个空间防越界
const int MAXN = 100005;
const int MAXM = 100005;

// 建图相关，链式前向星
int head[MAXN];
int nxt[MAXM]; // 避开 std::next 关键字
int to[MAXM];
int cnt;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

// 清理之前的脏数据
void build(int n)
{
    cnt = 1;
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
void topoSort()
{
    // 声明一个小根堆（默认的 priority_queue 是大根堆，所以要加两个模板参数改为小根堆）
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            pq.push(i);
        }
    }

    int fill = 0;
    while (!pq.empty())
    {
        // 弹出堆顶的最小值
        int cur = pq.top();
        pq.pop();

        ans[fill++] = cur;

        // 用链式前向星的方式，遍历 cur 的相邻节点
        for (int ei = head[cur]; ei != 0; ei = nxt[ei])
        {
            if (--indegree[to[ei]] == 0)
            {
                pq.push(to[ei]);
            }
        }
    }
}

int main()
{
    // C++ 快读优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 处理多组测试数据
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

        topoSort();

        // 打印结果
        for (int i = 0; i < n - 1; i++)
        {
            cout << ans[i] << " ";
        }
        cout << ans[n - 1] << "\n"; // 注意使用 \n 而不是 endl
    }

    return 0;
}