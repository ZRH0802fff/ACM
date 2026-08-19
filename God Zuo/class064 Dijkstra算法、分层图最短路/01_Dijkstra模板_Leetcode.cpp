// Dijkstra算法模版（Leetcode）
// 网络延迟时间
// 有 n 个网络节点，标记为 1 到 n
// 给你一个列表 times，表示信号经过 有向 边的传递时间
// times[i] = (ui, vi, wi)，表示从ui到vi传递信号的时间是wi
// 现在，从某个节点 s 发出一个信号
// 需要多久才能使所有节点都收到信号
// 如果不能使所有节点收到信号，返回 -1
// 测试链接 : https://leetcode.cn/problems/network-delay-time

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int MAXM = 6001;

// 邻接表（动态建图 + 普通堆用）
// graph[i] = {{邻居, 边权}, ...}
vector<vector<pair<int, int>>> graph;
int distance_[MAXN];
bool visited[MAXN];

// 小根堆的记录（动态建图 + 普通堆用）
// 0 : 当前节点
// 1 : 源点到当前点距离
struct Record {
    int u;
    int c;
};
// 按距离组织小根堆
struct Cmp {
    bool operator()(const Record& a, const Record& b) const {
        return a.c > b.c;
    }
};
priority_queue<Record, vector<Record>, Cmp> heap;

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

// 反向索引堆相关函数的声明（C++ 需先声明后使用）
void addEdge(int u, int v, int w);
void addOrUpdateOrIgnore(int v, int c);
void heapInsert(int i);
int pop();
void heapify(int i);
bool isEmpty();
void swap_(int i, int j);

void build(int n) {
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

void addOrUpdateOrIgnore(int v, int c) {
    if (where[v] == -1) {
        reverseHeap[heapSize] = v;
        where[v] = heapSize++;
        distance_[v] = c;
        heapInsert(where[v]);
    } else if (where[v] >= 0) {
        distance_[v] = min(distance_[v], c);
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

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        return networkDelayTime2(times, n, k);
    }

    // 动态建图+普通堆的实现
    int networkDelayTime1(vector<vector<int>>& times, int n, int s) {
        graph.clear();
        graph.resize(n + 1);
        for (auto& edge : times) {
            graph[edge[0]].push_back({ edge[1], edge[2] });
        }
        for (int i = 1; i <= n; i++) {
            distance_[i] = INT_MAX;
        }
        distance_[s] = 0;
        for (int i = 1; i <= n; i++) {
            visited[i] = false;
        }
        heap = priority_queue<Record, vector<Record>, Cmp>();
        heap.push({ s, 0 });
        while (!heap.empty()) {
            Record rec = heap.top();
            heap.pop();
            int u = rec.u;
            if (visited[u]) {
                continue;
            }
            visited[u] = true;
            for (auto& edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                if (!visited[v] && distance_[u] + w < distance_[v]) {
                    distance_[v] = distance_[u] + w;
                    heap.push({ v, distance_[u] + w });
                }
            }
        }
        int ans = INT_MIN;
        for (int i = 1; i <= n; i++) {
            if (distance_[i] == INT_MAX) {
                return -1;
            }
            ans = max(ans, distance_[i]);
        }
        return ans;
    }

    // 链式前向星+反向索引堆的实现
    int networkDelayTime2(vector<vector<int>>& times, int n, int s) {
        build(n);
        for (auto& edge : times) {
            addEdge(edge[0], edge[1], edge[2]);
        }
        addOrUpdateOrIgnore(s, 0);
        while (!isEmpty()) {
            int u = pop();
            for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
                addOrUpdateOrIgnore(to[ei], distance_[u] + weight[ei]);
            }
        }
        int ans = INT_MIN;
        for (int i = 1; i <= n; i++) {
            if (distance_[i] == INT_MAX) {
                return -1;
            }
            ans = max(ans, distance_[i]);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> times1 = { { 2, 1, 1 }, { 2, 3, 1 }, { 3, 4, 1 } };
    cout << sol.networkDelayTime(times1, 4, 2) << " (expected: 2)" << endl;
    vector<vector<int>> times2 = { { 1, 2, 1 } };
    cout << sol.networkDelayTime(times2, 2, 1) << " (expected: 1)" << endl;
    vector<vector<int>> times3 = { { 1, 2, 1 } };
    cout << sol.networkDelayTime(times3, 2, 2) << " (expected: -1)" << endl;
    return 0;
}
