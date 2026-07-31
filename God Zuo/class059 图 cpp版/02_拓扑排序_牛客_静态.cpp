// 拓扑排序模版（牛客）
// 链式前向星建图（静态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;
const int MAXM = 200001;

// 建图相关，链式前向星
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt;

// 拓扑排序，用到队列
int queue_[MAXN];
int l, r;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

void build(int n) {
    cnt = 1;
    for (int i = 0; i <= n; i++) {
        head[i] = 0;
        indegree[i] = 0;
    }
}

// 用链式前向星建图
void addEdge(int f, int t) {
    nxt[cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt++;
}

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
        // 用链式前向星的方式，遍历cur的相邻节点
        for (int ei = head[cur]; ei != 0; ei = nxt[ei]) {
            if (--indegree[to[ei]] == 0) {
                queue_[r++] = to[ei];
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
            addEdge(from, to);
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
