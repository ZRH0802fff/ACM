// 拓扑排序模版（牛客）
// 邻接表建图（动态方式 vector<vector<int>>）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

// 拓扑排序，用到队列
int queue_[MAXN];
int l, r;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

// 邻接表建图（动态方式）
// graph[i] 存 i 指向的所有节点
vector<vector<int>> graph;

int n, m;

void build(int n) {
    graph.clear();
    graph.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        indegree[i] = 0;
    }
}

// 有拓扑排序返回true
// 没有拓扑排序返回false
bool topoSort() {
    l = r = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue_[r++] = i;
        }
    }
    int fill = 0;
    while (l < r) {
        int cur = queue_[l++];
        ans[fill++] = cur;
        // 邻接表方式遍历 cur 的相邻节点
        for (int next : graph[cur]) {
            if (--indegree[next] == 0) {
                queue_[r++] = next;
            }
        }
    }
    return fill == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        build(n);
        for (int i = 0, from, to; i < m; i++) {
            cin >> from >> to;
            graph[from].push_back(to);
            indegree[to]++;
        }
        if (!topoSort()) {
            cout << -1 << '\n';
        } else {
            for (int i = 0; i < n - 1; i++) {
                cout << ans[i] << ' ';
            }
            cout << ans[n - 1] << '\n';
        }
    }
    return 0;
}
