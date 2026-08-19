// Dijkstra算法模版（洛谷）
// 静态空间实现 : 链式前向星 + 反向索引堆
// 测试链接 : https://www.luogu.com.cn/problem/P4779
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
const int MAXM = 200001;

// 链式前向星
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// 反向索引堆
int reverseHeap[MAXN];
// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = i(>=0)，表示v这个节点，在堆上的i位置
int where[MAXN];
int heapSize;

int distance_[MAXN];

int n, m, s;

// 反向索引堆相关函数的声明（C++ 需先声明后使用）
void addEdge(int u, int v, int w);
void addOrUpdateOrIgnore(int v, int w);
void heapInsert(int i);
int pop();
void heapify(int i);
bool isEmpty();
void swap_(int i, int j);

void build() {
    cnt = 1;
    heapSize = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        where[i] = -1;
        distance_[i] = INT_MAX;
    }
}

// 链式前向星建图
void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void addOrUpdateOrIgnore(int v, int w) {
    if (where[v] == -1) {
        reverseHeap[heapSize] = v;
        where[v] = heapSize++;
        distance_[v] = w;
        heapInsert(where[v]);
    } else if (where[v] >= 0) {
        distance_[v] = min(distance_[v], w);
        heapInsert(where[v]);
    }
}

void heapInsert(int i) {
    while (distance_[reverseHeap[i]] < distance_[reverseHeap[(i - 1) / 2]]) {
        swap_(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

int pop() {
    int ans = reverseHeap[0];
    swap_(0, --heapSize);
    heapify(0);
    where[ans] = -2;
    return ans;
}

void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && distance_[reverseHeap[l + 1]] < distance_[reverseHeap[l]] ? l + 1 : l;
        best = distance_[reverseHeap[best]] < distance_[reverseHeap[i]] ? best : i;
        if (best == i) {
            break;
        }
        swap_(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

bool isEmpty() {
    return heapSize == 0;
}

void swap_(int i, int j) {
    int tmp = reverseHeap[i];
    reverseHeap[i] = reverseHeap[j];
    reverseHeap[j] = tmp;
    where[reverseHeap[i]] = i;
    where[reverseHeap[j]] = j;
}

void dijkstra() {
    addOrUpdateOrIgnore(s, 0);
    while (!isEmpty()) {
        int v = pop();
        for (int ei = head[v]; ei > 0; ei = nxt[ei]) {
            addOrUpdateOrIgnore(to[ei], distance_[v] + weight[ei]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m >> s) {
        build();
        for (int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            addEdge(u, v, w);
        }
        dijkstra();
        cout << distance_[1];
        for (int i = 2; i <= n; i++) {
            cout << " " << distance_[i];
        }
        cout << '\n';
    }
    return 0;
}
