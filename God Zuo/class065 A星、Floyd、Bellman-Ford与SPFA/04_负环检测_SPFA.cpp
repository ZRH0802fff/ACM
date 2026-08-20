// Bellman-Ford + SPFA优化模版（洛谷）
// 给定n个点的有向图，请求出图中是否存在从顶点1出发能到达的负环
// 负环的定义是：一条边权之和为负数的回路
// 测试链接 : https://www.luogu.com.cn/problem/P3385
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2001;
const int MAXM = 6001;

// 链式前向星建图需要
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// SPFA需要
const int MAXQ = 4000001;

// 源点出发到每个节点的距离表
int distance_[MAXN];

// 节点被松弛的次数
int updateCnt[MAXN];

// 哪些节点被松弛了放入队列
int queue_[MAXQ];

int l, r;

// 节点是否已经在队列中
bool enter[MAXN];

void build(int n) {
    cnt = 1;
    l = r = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        enter[i] = false;
        distance_[i] = INT_MAX;
        updateCnt[i] = 0;
    }
}

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// Bellman-Ford + SPFA优化的模版
bool spfa(int n) {
    distance_[1] = 0;
    updateCnt[1]++;
    queue_[r++] = 1;
    enter[1] = true;
    while (l < r) {
        int u = queue_[l++];
        enter[u] = false;
        for (int ei = head[u], v, w; ei > 0; ei = nxt[ei]) {
            v = to[ei];
            w = weight[ei];
            if (distance_[u] + w < distance_[v]) {
                distance_[v] = distance_[u] + w;
                if (!enter[v]) {
                    // 松弛次数超过n-1就有负环
                    if (++updateCnt[v] > n - 1) {
                        return true;
                    }
                    queue_[r++] = v;
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int cases;
    cin >> cases;
    for (int i = 0, n, m; i < cases; i++) {
        cin >> n >> m;
        build(n);
        for (int j = 0, u, v, w; j < m; j++) {
            cin >> u >> v >> w;
            if (w >= 0) {
                addEdge(u, v, w);
                addEdge(v, u, w);
            } else {
                addEdge(u, v, w);
            }
        }
        cout << (spfa(n) ? "YES" : "NO") << '\n';
    }
    return 0;
}
