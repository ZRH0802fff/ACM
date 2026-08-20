# class065 A星、Floyd、Bellman-Ford与SPFA 笔记

> 视频：算法讲解065【必备】A星、Floyd、Bellman-Ford与SPFA
> 前置知识：class059 建图/链式前向星、class062 宽度优先遍历、class064 Dijkstra算法
> 本课四个算法理解门槛都不高：A星是 Dijkstra 的"引导"版，Floyd 三层循环，Bellman-Ford 是"松弛轮数"的直白框架，SPFA 是它的队列优化。

---

## 题目1：A*算法模版（对数器验证）

### 题面
n×n 网格，`grid[i][j]==0` 代表障碍、`1` 代表道路，只能走上、下、左、右（不含斜线）。返回从 (startX,startY) 到 (targetX,targetY) 的最短距离（不可达返回 -1）。无测试链接，用对数器对比 Dijkstra 与 A* 验证。

### 核心思路
**Dijkstra 只求"原点到所有点"，A* 专求"原点→指定目标点"**：Dijkstra 要铺满整张图，A* 只想最快走到终点，所以给堆里的排序加一层"引导"。

- 堆排序依据：Dijkstra 是「原点到当前点的真实距离」，A* 变成「原点到当前点真实距离 + 当前点到终点的**预估距离**」。
- 其余一切与 Dijkstra 完全一致：`visited` 去重、`distance_` 只记真实最短距离（和预估无关）、发现终点即返回 `distance_[x][y]`。
- **可以把 Dijkstra 看作 A* 的特例**：预估函数恒返回 0 时，A* 就退化成 Dijkstra。把"恒 0"升级成一个有吸引力的估计，就是 A*。

**预估函数的唯一要求：预估距离 ≤ 当前点到终点的真实最短距离。**
- 满足这一点，算法正确（证明略）；预估越接近真实距离，跑得越快。预估是"吸引力"——合适的吸引力加速搜索，吸引力过强（预估 > 真实）就会出错（可能提前"路过"终点却不是最短路）。
- 性能对比：同样 4000×4000 网格，Dijkstra 约 1.7s，A* 约 300ms（常数级优化，最坏复杂度仍同 Dijkstra）。
- 为什么只能在二维网格这类有"空间感"的问题上用 A*？因为普通有向图你**估计不出**"当前点到终点还有多远"。

**三种常见预估距离**（根据题目"能不能走斜线"选）：
| 距离 | 公式 | 适用 |
|---|---|---|
| 曼哈顿距离 | `|Δ行| + |Δ列|` | 只能上下左右 |
| 对角线距离 | `max(|Δ行|, |Δ列|)` | 上下左右 + 斜线 |
| 欧式距离 | `sqrt(Δ行² + Δ列²)` | 勾股定理直线距离 |

**关键坑**：若格子能走斜线，用曼哈顿距离就会"预估 > 真实"（曼哈顿可能估出 6 步，真实斜线只需 4 步），导致错误——此时必须换成对角线距离。若只能上下左右，则曼哈顿、对角线都正确，但曼哈顿吸引力更强、更快。

### 坑点
- 预估距离 ≤ 真实距离才保证正确；A* 返回的是 `distance_[x][y]`（真实距离），不是堆里的"真实+预估"。
- 起点/终点是障碍直接返回 -1。
- 本文件是自测对数器，`grid/distance_/visited` 用全局数组，`MAXN=4001` 为性能测试（4000×4000）预留。

### 代码
```cpp
const int MAXN = 4001;
int move_[] = { -1, 0, 1, 0, -1 };
int grid[MAXN][MAXN];
int distance_[MAXN][MAXN];
bool visited[MAXN][MAXN];

struct Record { int x, y, c; };
struct Cmp { bool operator()(const Record& a, const Record& b) const { return a.c > b.c; } };
priority_queue<Record, vector<Record>, Cmp> heap;

// 曼哈顿距离（预估函数）
int f1(int x, int y, int targetX, int targetY) {
    return abs(targetX - x) + abs(targetY - y);
}
// 对角线距离
int f2(int x, int y, int targetX, int targetY) {
    return max(abs(targetX - x), abs(targetY - y));
}
// 欧式距离
double f3(int x, int y, int targetX, int targetY) {
    return sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
}

// Dijkstra 版（预估函数恒为 0 的 A*）
int minDistance1(int n, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) return -1;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        distance_[i][j] = INT_MAX; visited[i][j] = false;
    }
    distance_[startX][startY] = 1;
    heap = priority_queue<Record, vector<Record>, Cmp>();
    heap.push({ startX, startY, 1 });              // 排序依据 = 真实距离
    while (!heap.empty()) {
        Record cur = heap.top(); heap.pop();
        int x = cur.x, y = cur.y;
        if (visited[x][y]) continue;
        visited[x][y] = true;
        if (x == targetX && y == targetY) return distance_[x][y];
        for (int i = 0, nx, ny; i < 4; i++) {
            nx = x + move_[i]; ny = y + move_[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1 && !visited[nx][ny]
                && distance_[x][y] + 1 < distance_[nx][ny]) {
                distance_[nx][ny] = distance_[x][y] + 1;
                heap.push({ nx, ny, distance_[x][y] + 1 });
            }
        }
    }
    return -1;
}

// A* 版：唯一区别——入堆的 c 多加一个预估距离 f1
int minDistance2(int n, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) return -1;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        distance_[i][j] = INT_MAX; visited[i][j] = false;
    }
    distance_[startX][startY] = 1;
    heap = priority_queue<Record, vector<Record>, Cmp>();
    heap.push({ startX, startY, 1 + f1(startX, startY, targetX, targetY) });
    while (!heap.empty()) {
        Record cur = heap.top(); heap.pop();
        int x = cur.x, y = cur.y;
        if (visited[x][y]) continue;
        visited[x][y] = true;
        if (x == targetX && y == targetY) return distance_[x][y];
        for (int i = 0, nx, ny; i < 4; i++) {
            nx = x + move_[i]; ny = y + move_[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1 && !visited[nx][ny]
                && distance_[x][y] + 1 < distance_[nx][ny]) {
                distance_[nx][ny] = distance_[x][y] + 1;
                heap.push({ nx, ny, distance_[x][y] + 1 + f1(nx, ny, targetX, targetY) });
            }
        }
    }
    return -1;
}
```

---

## 题目2：Floyd算法模版

### 题面
求图中**任意两点之间**的最短距离。本题（洛谷 P2910）给定 n 个岛、m 个按顺序访问的岛（点数 100 以内），及 n×n 邻接矩阵（危险系数），求按顺序走完这 m 个岛的最小总危险系数。

- 洛谷 P2910: https://www.luogu.com.cn/problem/P2910 （n ≤ 100，m ≤ 1e4）

### 核心思路
**Floyd**：`distance[i][j] = min(distance[i][j], distance[i][bridge] + distance[bridge][j])`。

- 适用：有向/无向图都行，边权正负都行，但**不能有负环**（有负环则最短路本身不存在——可以无限绕圈把距离刷到负无穷）。
- 复杂度：时间 O(n³)、空间 O(n²)。因为信息本身是 n² 的（任意两点），所以 O(n²) 空间是下限。
- **数据量判断**：节点数约 100 时，n³ ≈ 10⁶，轻松过。所以 Floyd 基本只用于小图。
- **跳板必须最先枚举**（三层循环最外层是 bridge），这是 Floyd 唯一的硬性顺序要求；至于先枚举哪个 bridge（A/B/C/D 顺序）无所谓。

### 坑点
- 一般情况下 `build()` 要先 `distance[i][j] = INT_MAX`；本题因给的是完整邻接矩阵，初始化显得"不必要"，但通用模板必须做。
- 松弛前先判 `distance[i][bridge] != INT_MAX && distance[bridge][j] != INT_MAX`，否则 `+` 溢出。
- 本题岛编号 0 开始，读入 path 时 `-1`。

### 代码
```cpp
const int MAXN = 101;
const int MAXM = 10001;
int path[MAXM];
int distance_[MAXN][MAXN];
int n, m, ans;

void build() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            distance_[i][j] = INT_MAX;
}

void floyd() {
    // O(N^3)的过程，枚举每个跳板，注意跳板要最先枚举！
    for (int bridge = 0; bridge < n; bridge++) { // 跳板
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distance_[i][bridge] != INT_MAX && distance_[bridge][j] != INT_MAX
                    && distance_[i][j] > distance_[i][bridge] + distance_[bridge][j]) {
                    distance_[i][j] = distance_[i][bridge] + distance_[bridge][j];
                }
            }
        }
    }
}
```

---

## 题目3：k站中转内最便宜的航班（Bellman-Ford应用）

### 题面
n 个城市，flights[i] = [from, to, price]。求从 start 到 target、**最多经过 k 站中转**的最便宜价格，无则 -1。

- LeetCode 787: https://leetcode.cn/problems/cheapest-flights-within-k-stops/ （n ≤ 100）

### 核心思路
先讲裸 Bellman-Ford：反复"一轮轮考察所有边做松弛"，直到某轮不再有松弛。**松弛** = 若 `distance[u] + w < distance[v]` 就更新 `distance[v]`。因为最短路最多 n-1 条边，所以最多松弛 n-1 轮 → 总复杂度 O(m·n)。

**本题是"阉割版"Bellman-Ford，不是标准模板**，原因：裸 Bellman-Ford 的"一轮"可能联动出多次中转（边顺序合适时，一轮内 A→B→C 就全刷出来了），和题目"中转 k 次"对不上。

解法：**用老表 cur 取距离、写到新表 next**，每轮先从 cur 拷贝到 next，再遍历所有边时**只从 cur（老表）读、只向 next（新表）写**。这样一轮最多走一条边，中转次数与轮数严格对应。
- `cur[v]` = 经过 ≤ i 条边到达 v 的最短距离；共做 k+1 轮（k 次中转 = 最多 k+1 条边）。

### 坑点
- `next` 必须是 `cur` 的拷贝；松弛时 `cur[edge[0]]` 从老表读（不能就地读 next），否则一条边可能被同一轮多次利用（中转次数虚报）。
- `cur[edge[0]] != INT_MAX` 才松弛，否则 `+ price` 溢出。
- 结果 `cur[target] == INT_MAX ? -1 : cur[target]`。

### 代码
```cpp
const int MAXN = 101;
int cur[MAXN];
int next_[MAXN];

int findCheapestPrice(int n, vector<vector<int>>& flights, int start, int target, int k) {
    for (int i = 0; i < n; i++) cur[i] = INT_MAX;
    cur[start] = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < n; j++) next_[j] = cur[j];   // 老表拷贝
        for (auto& edge : flights) {   // a -> b , w
            if (cur[edge[0]] != INT_MAX) {                // 只从老表读
                next_[edge[1]] = min(next_[edge[1]], cur[edge[0]] + edge[2]);  // 只写新表
            }
        }
        for (int j = 0; j < n; j++) cur[j] = next_[j];
    }
    return cur[target] == INT_MAX ? -1 : cur[target];
}
```

---

## 题目4：负环检测（Bellman-Ford + SPFA优化）

### 题面
n 个点的有向图，判断图中是否存在**从顶点 1 出发能到达的负环**（边权和为负的回路）。多组测试。

- 洛谷 P3385: https://www.luogu.com.cn/problem/P3385 （n ≤ 2000，m ≤ 3000）

### 核心思路
**SPFA = Bellman-Ford 的队列优化（只优化常数，最坏仍 O(n·m)）**：
- 裸 Bellman-Ford 每轮扫所有边很蠢——只有"上一轮距离变小的点"连出的边才可能引发下一轮松弛。所以用队列维护"哪些点距离变小了"。
- `enter[]` 标记点是否已在队列，避免重复入队；已在队列的点距离再被改小也不用重复入队（它迟早会弹出去松弛别人）。
- **负环判据**：若最短路存在（无负环），每个点被松弛次数 ≤ n-1；一旦 `updateCnt[v]` 达到 n 次（即 `++updateCnt[v] > n-1`），说明绕进了负环，返回 true。这个 updateCnt 结构是**为负环定制的**，纯 SPFA 求最短路不需要它。
- 注意源点 1 初始 `distance_[1] = 0` 也算"被松弛了一次"，所以 `updateCnt[1]++`。

**扩展：判断整张图（不指定原点）是否有负环** → 设一个**虚拟原点**，连向所有点、边权全 0，从它出发跑 SPFA 即可（保证每个点都可达）。

### 坑点
- 无负权边时用 Dijkstra，别用 SPFA（SPFA 最坏 O(n·m) 可被卡）。
- 建图按题目约定：`w >= 0` 的边双向各建一条；`w < 0` 只建一条有向边。
- 用 `enter[]` 避免重复入队；`queue_` 用数组模拟，`l/r` 头尾指针。

### 代码
```cpp
const int MAXN = 2001, MAXM = 6001, MAXQ = 4000001;
int head[MAXN], nxt[MAXM], to[MAXM], weight[MAXM], cnt;
int distance_[MAXN];   // 源点出发到每个节点的距离表
int updateCnt[MAXN];   // 节点被松弛的次数
int queue_[MAXQ];      // 哪些节点被松弛了放入队列
int l, r;
bool enter[MAXN];      // 节点是否已经在队列中

void build(int n) {
    cnt = 1; l = r = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0; enter[i] = false;
        distance_[i] = INT_MAX; updateCnt[i] = 0;
    }
}

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u]; to[cnt] = v; weight[cnt] = w; head[u] = cnt++;
}

bool spfa(int n) {
    distance_[1] = 0;
    updateCnt[1]++;          // 源点到自己也算松弛一次
    queue_[r++] = 1;
    enter[1] = true;
    while (l < r) {
        int u = queue_[l++];
        enter[u] = false;
        for (int ei = head[u], v, w; ei > 0; ei = nxt[ei]) {
            v = to[ei]; w = weight[ei];
            if (distance_[u] + w < distance_[v]) {
                distance_[v] = distance_[u] + w;
                if (!enter[v]) {
                    if (++updateCnt[v] > n - 1) return true;   // 松弛次数达到 n 就有负环
                    queue_[r++] = v;
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}
```

---

## 本课总结

| 算法 | 解决 | 复杂度 | 注意 |
|---|---|---|---|
| A* | 指定源点→目标点最短路 | 最坏同 Dijkstra，仅优化常数 | 预估 ≤ 真实距离；走斜线用对角线距离 |
| Floyd | 任意两点最短路 | O(n³) / O(n²) | 跳板最先枚举；不能有负环 |
| Bellman-Ford | 有负权边（无负环）单源最短路 | O(m·n) | 松弛轮数 ≤ n-1；第 n 轮仍松弛⇒有负环 |
| SPFA | Bellman-Ford 的队列优化 | 平均快，最坏 O(m·n) | 小图用；负环判 updateCnt 达 n |

**Bellman-Ford 的用途小结**：①小图（n·m ≤ 10⁷~10⁸）有负权边的单源最短路；②判断从某点出发能否到达负环；③设虚拟原点可判断整张图有无负环；④并行计算时优势大（每轮各点松弛相互独立，可多线程）。
