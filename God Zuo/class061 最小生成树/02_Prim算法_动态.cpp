// Prim算法模版（洛谷）
// 动态空间实现
// 测试链接 : https://www.luogu.com.cn/problem/P3366
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include <bits/stdc++.h>
using namespace std;

// 时间复杂度O(n + m) + O(m * log m)

const int MAXN = 5001;
const int MAXM = 400001;

// 链式前向星建图
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// 手写小根堆 (边: 到达节点, 花费)
int heap[MAXM][2];
int heapSize;

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void push(int v, int cost) {
    int i = heapSize++;
    heap[i][0] = v;
    heap[i][1] = cost;
    while (heap[i][1] < heap[(i - 1) / 2][1]) {
        swap(heap[i][0], heap[(i - 1) / 2][0]);
        swap(heap[i][1], heap[(i - 1) / 2][1]);
        i = (i - 1) / 2;
    }
}

void pop(int& v, int& cost) {
    v = heap[0][0];
    cost = heap[0][1];
    heap[0][0] = heap[--heapSize][0];
    heap[0][1] = heap[heapSize][1];
    int i = 0;
    int l = 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
        best = heap[best][1] < heap[i][1] ? best : i;
        if (best == i) break;
        swap(heap[best][0], heap[i][0]);
        swap(heap[best][1], heap[i][1]);
        i = best;
        l = i * 2 + 1;
    }
}

bool heapEmpty() {
    return heapSize == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        cnt = 1;
        for (int i = 0; i <= n; i++) {
            head[i] = 0;
        }
        for (int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        heapSize = 0;
        // 哪些节点已经发现过了
        bool set[MAXN] = {false};
        int nodeCnt = 1;
        set[1] = true;
        for (int ei = head[1]; ei > 0; ei = nxt[ei]) {
            push(to[ei], weight[ei]);
        }
        int ans = 0;
        while (!heapEmpty()) {
            int next, cost;
            pop(next, cost);
            if (!set[next]) {
                nodeCnt++;
                set[next] = true;
                ans += cost;
                for (int ei = head[next]; ei > 0; ei = nxt[ei]) {
                    push(to[ei], weight[ei]);
                }
            }
        }
        if (nodeCnt == n) {
            cout << ans << '\n';
        } else {
            cout << "orz" << '\n';
        }
    }
    return 0;
}
