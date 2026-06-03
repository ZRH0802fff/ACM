#include <iostream>
#include <algorithm> // 包含 sort 函数

using namespace std;

// 习惯性多开几个空间防止数组越界
const int MAXN = 5005;
const int MAXM = 200005;

// 在 C++ 中，使用结构体存边比使用二维数组更加清晰和高效
struct Edge
{
    int u, v, w;
} edges[MAXM];

int father[MAXN];
int n, m;

// 并查集初始化
void build()
{
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }
}

// 并查集查找（带路径压缩）
int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 如果 x 和 y 本来就是一个集合，返回 false
// 如果 x 和 y 不是一个集合，合并之后返回 true
// 注意：C++ 中 union 是保留关键字，所以通常改名叫 unite 或者 merge
bool unite(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
        father[fx] = fy;
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // 解除 C++ 和 C 的输入输出绑定，极大地提升读写效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 处理多组输入，直到 EOF
    while (cin >> n >> m)
    {
        build();
        for (int i = 0; i < m; i++)
        {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        // 核心：按照边的权重(w)从小到大排序
        // 这里使用了 C++11 的 Lambda 表达式，非常简洁
        sort(edges, edges + m, [](const Edge &a, const Edge &b)
             { return a.w < b.w; });

        int ans = 0;
        int edgeCnt = 0;

        // 遍历所有边，执行 Kruskal 逻辑
        for (int i = 0; i < m; i++)
        {
            if (unite(edges[i].u, edges[i].v))
            {
                edgeCnt++;
                ans += edges[i].w;
            }
        }

        // 如果成功连上了 n - 1 条边，说明最小生成树构建成功
        if (edgeCnt == n - 1)
        {
            cout << ans << "\n"; // 使用 \n 代替 endl 以保证性能
        }
        else
        {
            cout << "orz\n"; // 图不连通的情况
        }
    }

    return 0;
}