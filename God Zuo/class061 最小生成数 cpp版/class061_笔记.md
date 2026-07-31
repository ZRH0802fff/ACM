# class061 最小生成树 笔记

> 视频：算法讲解061【必备】最小生成树

---

## 题目1：Kruskal算法

### 题面
给定 n 个点 m 条边的无向带权连通图，求最小生成树的边权和。若不连通输出 "orz"。

- 洛谷 P3366: https://www.luogu.com.cn/problem/P3366

### 核心思路
**Kruskal（贪心+并查集）**，复杂度 O(m log m)：

1. 所有边按权重升序排序
2. 依次枚举每条边，用并查集判断两端是否已连通
3. 若不连通则合并，累加权重
4. 选够 n-1 条边即完成

### 坑点
- 边用 struct 存储（`int edges[MAXM][3]` 无法用 sort）
- 并查集路径压缩：`if (i != father[i]) father[i] = find(father[i]);`

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

// 时间复杂度O(m * log m) + O(n + m)

const int MAXN = 5001;
const int MAXM = 200001;

int father[MAXN];

// u, v, w
struct Edge {
    int u, v, w;
} edges[MAXM];

int n, m;

void build() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 如果x和y本来就是一个集合，返回false
// 如果x和y不是一个集合，合并之后返回true
bool unionSet(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        return true;
    } else {
        return false;
    }
}

// 核心算法（通常在main中调用）:
// sort(edges, edges + m, [](const Edge& a, const Edge& b) { return a.w < b.w; });
// int ans = 0, edgeCnt = 0;
// for (int i = 0; i < m; i++) {
//     if (unionSet(edges[i].u, edges[i].v)) {
//         edgeCnt++;
//         ans += edges[i].w;
//     }
//     if (edgeCnt == n - 1) break;
// }
// if (edgeCnt == n - 1) cout << ans; else cout << "orz";
```

---

## 题目2-3：Prim算法（动态版/静态版）

### 题面
同上，求最小生成树。

### 核心思路
**Prim（贪心+堆）**，复杂度 O((n+m) log n)：

1. 从节点 1 出发，将其所有边加入小根堆
2. 每次弹出权重最小的边，若目标节点未访问则加入 MST
3. 将新节点的所有边加入堆

**动态版**：每次 push 边到堆，可能有重复边（通过 set 去重）。

**静态版（优化）**：堆中每个节点只保留一条最小边。
- `where[v]` 三态：-1=未入堆，-2=已弹出，≥0=堆中位置
- `addOrUpdateOrIgnore(ei)`：若节点未入堆则插入，已在堆则更新最小值

### 坑点
- 静态版中 `swap` 时要同步更新 `where` 数组
- `pop()` 后 `where[u] = -2` 标记已弹出

### 代码（动态版）
```cpp
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

// 核心Prim逻辑：
// bool set[MAXN] = {false};
// int nodeCnt = 1;
// set[1] = true;
// for (int ei = head[1]; ei > 0; ei = nxt[ei]) push(to[ei], weight[ei]);
// int ans = 0;
// while (!heapEmpty()) {
//     int next, cost;
//     pop(next, cost);
//     if (!set[next]) {
//         nodeCnt++;
//         set[next] = true;
//         ans += cost;
//         for (int ei = head[next]; ei > 0; ei = nxt[ei]) push(to[ei], weight[ei]);
//     }
// }
// if (nodeCnt == n) 输出ans; else 输出"orz";
```

### 代码（静态版）
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5001;
const int MAXM = 400001;

int n, m;

// 链式前向星建图
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// 改写的堆结构
int heap[MAXN][2];

// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = i(>=0)，表示v这个节点，在堆上的i位置
int where[MAXN];

// 堆的大小
int heapSize;

// 找到的节点个数
int nodeCnt;

void build() {
    cnt = 1;
    heapSize = 0;
    nodeCnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        where[i] = -1;
    }
}

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void heapInsert(int i) {
    while (heap[i][1] < heap[(i - 1) / 2][1]) {
        swap(heap[i], heap[(i - 1) / 2]);
        int a = heap[i][0];
        int b = heap[(i - 1) / 2][0];
        where[a] = i;
        where[b] = (i - 1) / 2;
        i = (i - 1) / 2;
    }
}

// 当前处理的是编号为ei的边！
void addOrUpdateOrIgnore(int ei) {
    int v = to[ei];
    int w = weight[ei];
    // 去往v点，权重w
    if (where[v] == -1) {
        // v这个点，从来没有进入过堆！
        heap[heapSize][0] = v;
        heap[heapSize][1] = w;
        where[v] = heapSize++;
        heapInsert(where[v]);
    } else if (where[v] >= 0) {
        // v这个点的记录，在堆上的位置是where[v]
        heap[where[v]][1] = min(heap[where[v]][1], w);
        heapInsert(where[v]);
    }
}

int u, w;

// 堆顶的记录：节点 -> u、到节点的花费 -> w
void pop() {
    u = heap[0][0];
    w = heap[0][1];
    swap(heap[0], heap[--heapSize]);
    if (heapSize > 0) {
        where[heap[0][0]] = 0;
    }
    where[u] = -2;
    nodeCnt++;
    // heapify
    int i = 0;
    int l = 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
        best = heap[best][1] < heap[i][1] ? best : i;
        if (best == i) break;
        swap(heap[best], heap[i]);
        int a = heap[best][0];
        int b = heap[i][0];
        where[a] = best;
        where[b] = i;
        i = best;
        l = i * 2 + 1;
    }
}

bool isEmpty() {
    return heapSize == 0;
}

int prim() {
    // 1节点出发
    nodeCnt = 1;
    where[1] = -2;
    for (int ei = head[1]; ei > 0; ei = nxt[ei]) {
        addOrUpdateOrIgnore(ei);
    }
    int ans = 0;
    while (!isEmpty()) {
        pop();
        ans += w;
        for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
            addOrUpdateOrIgnore(ei);
        }
    }
    return ans;
}
```

---

## 题目4：水资源分配优化

### 题面
n 栋房子，可在房子内建水井（成本 wells[i]），或铺设管道连接两房（成本 pipes[j]）。求为所有房子供水的最低总成本。

- LeetCode 1168: https://leetcode.cn/problems/optimize-water-distribution-in-a-village/

### 核心思路
**虚拟节点 0 + Kruskal**：

关键 trick：建立一个虚拟节点 0 代表"水源"，在房子 i 建水井等价于连接 (0, i, wells[i])。问题转化为求包含节点 0~n 的 MST。

1. 将所有 wells[i] 转为边 (0, i+1, wells[i])
2. 将所有 pipes 加入边集
3. Kruskal 求 MST

### 坑点
- 虚拟节点 0 的技巧是关键
- 房子编号从 1 开始，wells 索引从 0 开始

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;

struct Edge {
    int u, v, w;
} edges[MAXN << 1];

int edgeCnt;

int father[MAXN];

void build(int n) {
    edgeCnt = 0;
    for (int i = 0; i <= n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 如果x和y，原本是一个集合，返回false
// 如果x和y，不是一个集合，合并之后后返回true
bool unionSet(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        return true;
    } else {
        return false;
    }
}

class Solution {
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        build(n);
        for (int i = 0; i < n; i++, edgeCnt++) {
            // wells : 100   30
            //         0(1)  1(2)
            edges[edgeCnt].u = 0;
            edges[edgeCnt].v = i + 1;
            edges[edgeCnt].w = wells[i];
        }
        for (int i = 0; i < (int)pipes.size(); i++, edgeCnt++) {
            edges[edgeCnt].u = pipes[i][0];
            edges[edgeCnt].v = pipes[i][1];
            edges[edgeCnt].w = pipes[i][2];
        }
        sort(edges, edges + edgeCnt, [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });
        int ans = 0;
        for (int i = 0; i < edgeCnt; i++) {
            if (unionSet(edges[i].u, edges[i].v)) {
                ans += edges[i].w;
            }
        }
        return ans;
    }
};
```

---

## 题目5：检查边长度限制的路径是否存在

### 题面
无向图，多次询问：是否存在 pj 到 qj 的路径，路径上每条边权都 < limitj。

- LeetCode 1697: https://leetcode.cn/problems/checking-existence-of-edge-length-limited-paths/

### 核心思路
**离线查询 + Kruskal 思想**：

1. 边按权重排序，询问按 limit 排序
2. 双指针：对于每个询问，将所有 `w < limit` 的边加入并查集
3. 检查 p 和 q 是否连通（`isSameSet`）

### 坑点
- 询问需要记录原始索引，排序后丢失顺序
- 使用 struct Question {u, v, limit, idx} 保留原始位置

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
const int MAXM = 100001;

struct Edge {
    int u, v, w;
};

struct Question {
    int u, v, limit, idx;
};

Edge edges_global[MAXM];
Question questions[MAXN];
int father[MAXN];

void build(int n) {
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

bool isSameSet(int x, int y) {
    return find(x) == find(y);
}

void unionSet(int x, int y) {
    father[find(x)] = find(y);
}

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int m = edgeList.size();
        int k = queries.size();
        // 将edges转为struct数组以便排序
        for (int i = 0; i < m; i++) {
            edges_global[i].u = edgeList[i][0];
            edges_global[i].v = edgeList[i][1];
            edges_global[i].w = edgeList[i][2];
        }
        sort(edges_global, edges_global + m, [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });
        for (int i = 0; i < k; i++) {
            questions[i].u = queries[i][0];
            questions[i].v = queries[i][1];
            questions[i].limit = queries[i][2];
            questions[i].idx = i;
        }
        sort(questions, questions + k, [](const Question& a, const Question& b) {
            return a.limit < b.limit;
        });
        build(n);
        vector<bool> ans(k);
        for (int i = 0, j = 0; i < k; i++) {
            // i : 问题编号
            // j : 边的编号
            for (; j < m && edges_global[j].w < questions[i].limit; j++) {
                unionSet(edges_global[j].u, edges_global[j].v);
            }
            ans[questions[i].idx] = isSameSet(questions[i].u, questions[i].v);
        }
        return ans;
    }
};
```

---

## 题目6：繁忙的都市（洛谷 P2330）

### 题面
n 个路口 m 条双向路，每条路有分值。要求：
1. 改造的路连通所有路口
2. 改造路尽量少
3. 在上述条件下，分值最大的路分值尽量小
输出：改造了几条路 和 最大分值

### 核心思路
Kruskal 天然满足：按分值排序后，前 n-1 条能连通所有路口的边即为答案。最后加入的那条边的分值就是最大分值。

### 坑点
- 分值更新用 `ans = max(ans, edges[i].w)` 而非累加
- 输出 `n-1` 和 `ans`（n-1 条边 + 最后加入边的分值）

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 301;
const int MAXM = 8001;

int father[MAXN];

struct Edge {
    int u, v, w;
} edges[MAXM];

int n, m;

void build() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 如果x和y本来就是一个集合，返回false
// 如果x和y不是一个集合，合并之后返回true
bool unionSet(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        return true;
    } else {
        return false;
    }
}

// 核心算法：
// sort(edges, edges + m, [](const Edge& a, const Edge& b) { return a.w < b.w; });
// int ans = 0, edgeCnt = 0;
// for (int i = 0; i < m; i++) {
//     if (unionSet(edges[i].u, edges[i].v)) {
//         edgeCnt++;
//         ans = max(ans, edges[i].w);
//     }
//     if (edgeCnt == n - 1) break;
// }
// cout << n - 1 << ' ' << ans;
```
