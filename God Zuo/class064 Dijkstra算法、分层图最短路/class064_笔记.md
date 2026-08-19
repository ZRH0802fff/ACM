# class064 Dijkstra算法、分层图最短路 笔记

> 视频：算法讲解064【必备】Dijkstra算法、分层图最短路

---

## 题目1：网络延迟时间 / 单源最短路径模板

### 题面
有 n 个网络节点（1~n），times[i] = (ui, vi, wi) 表示从 ui 到 vi 的有向边、传递时间 wi。从源点 s 发出信号，求所有节点都收到信号的最短时间，若无法到达所有节点返回 -1。

- LeetCode 743: https://leetcode.cn/problems/network-delay-time （n ≤ 100，m ≤ 6000）
- 洛谷 P4779: https://www.luogu.com.cn/problem/P4779 （n ≤ 1e5，m ≤ 2e5，单源最短路模板）

### 核心思路
**Dijkstra 算法**：每次从「未弹出过的点」中取出距离最小的点，用它的距离去松弛所有邻边。

- **方法一（动态建图 + 普通堆）**：邻接表 `vector<vector<pair<int,int>>>` + STL 小根堆（`priority_queue`），堆里存 (节点, 距离)，按距离排。弹出已访问的节点直接跳过。
- **方法二（链式前向星 + 反向索引堆）**：静态空间，`where[v]` 记录 v 在堆上的位置（-1=从没进堆，-2=已弹出，≥0=在堆上的下标），支持"原地改小距离再上浮"，避免堆里堆积重复节点。

### 坑点
- 链式前向星 `cnt` 从 1 开始，`head[i]=0` 表示空，遍历 `for (int ei = head[u]; ei > 0; ei = nxt[ei])`。
- 反向索引堆的 `where` 要随 `swap` 同步维护。
- 最后所有节点距离取 `max`；任一节点仍为 `INT_MAX` 说明不可达，返回 -1。
- 洛谷数据量大（n=1e5），必须用链式前向星 + 反向索引堆，不能用邻接表 + STL 堆。

### 代码（洛谷模板：链式前向星 + 反向索引堆）
```cpp
const int MAXN = 100001;
const int MAXM = 200001;

int head[MAXN], nxt[MAXM], to[MAXM], weight[MAXM], cnt;
int reverseHeap[MAXN];
int where[MAXN];   // -1 从没进堆，-2 已弹出，>=0 在堆上位置
int heapSize;
int distance_[MAXN];
int n, m, s;

void build() {
    cnt = 1;
    heapSize = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        where[i] = -1;
        distance_[i] = INT_MAX;
    }
}

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
        if (best == i) break;
        swap_(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

bool isEmpty() { return heapSize == 0; }

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
```

---

## 题目2：最小体力消耗路径

### 题面
rows×columns 地图 heights，从 (0,0) 走到 (rows-1, columns-1)，可上下左右移动。一条路径的体力值 = 相邻格子高度差绝对值的最大值，求最小体力消耗值。

- LeetCode 1631: https://leetcode.cn/problems/path-with-minimum-effort/ （rows, columns ≤ 100）

### 核心思路
**网格上的 Dijkstra**：源点 (0,0) 距离 0。每次弹出代价最小的格子 (x,y)，松弛四邻。到 (nx,ny) 的代价 = `max(当前代价 c, |heights[x][y] - heights[nx][ny]|)`。

### 坑点
- 代价取「路径上最大值」，所以松弛用 `max` 而不是加法。
- 发现右下角直接返回（剪枝），因为 Dijkstra 第一次弹出终点即为最优。
- n、m ≤ 100，distance/visited 用全局 `int distance_[101][101]`。

### 代码
```cpp
int move_[] = { -1, 0, 1, 0, -1 };
int distance_[MAXN][MAXM];
bool visited[MAXN][MAXM];

struct Record { int x, y, c; };
struct Cmp { bool operator()(const Record& a, const Record& b) const { return a.c > b.c; } };
priority_queue<Record, vector<Record>, Cmp> heap;

int minimumEffortPath(vector<vector<int>>& heights) {
    int n = heights.size(), m = heights[0].size();
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        distance_[i][j] = INT_MAX; visited[i][j] = false;
    }
    distance_[0][0] = 0;
    heap = priority_queue<Record, vector<Record>, Cmp>();
    heap.push({ 0, 0, 0 });
    while (!heap.empty()) {
        Record rec = heap.top(); heap.pop();
        int x = rec.x, y = rec.y, c = rec.c;
        if (visited[x][y]) continue;
        if (x == n - 1 && y == m - 1) return c;   // 发现终点直接返回
        visited[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + move_[i], ny = y + move_[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                int nc = max(c, abs(heights[x][y] - heights[nx][ny]));
                if (nc < distance_[nx][ny]) {
                    distance_[nx][ny] = nc;
                    heap.push({ nx, ny, nc });
                }
            }
        }
    }
    return -1;
}
```

---

## 题目3：水位上升的泳池中游泳

### 题面
n×n 矩阵 grid，grid[i][j] 是平台高度，t 时刻水位为 t。可从一平台游到相邻平台，前提是水位同时淹没两者。求从 (0,0) 到 (n-1,n-1) 的最少时间。

- LeetCode 778: https://leetcode.cn/problems/swim-in-rising-water/ （n ≤ 50）

### 核心思路
与题目 2 同款网格 Dijkstra，只是起点代价为 `grid[0][0]`，松弛到邻居的代价 = `max(c, grid[nx][ny])`。

### 坑点
- 初始距离 `distance_[0][0] = grid[0][0]`（不能从 0 出发，得先淹没起点平台）。
- 其余同题目 2，`max` 而非加法。

### 代码
```cpp
int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        distance_[i][j] = INT_MAX; visited[i][j] = false;
    }
    distance_[0][0] = grid[0][0];
    heap = priority_queue<Record, vector<Record>, Cmp>();
    heap.push({ 0, 0, grid[0][0] });
    while (!heap.empty()) {
        Record rec = heap.top(); heap.pop();
        int x = rec.x, y = rec.y, c = rec.c;
        if (visited[x][y]) continue;
        visited[x][y] = true;
        if (x == n - 1 && y == m - 1) return c;   // 发现终点直接返回
        for (int i = 0; i < 4; i++) {
            int nx = x + move_[i], ny = y + move_[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                int nc = max(c, grid[nx][ny]);
                if (nc < distance_[nx][ny]) {
                    distance_[nx][ny] = nc;
                    heap.push({ nx, ny, nc });
                }
            }
        }
    }
    return -1;
}
```

---

## 题目4：获取所有钥匙的最短路径

### 题面
二维网格：`.` 空房间、`#` 墙、`@` 起点、小写字母钥匙、大写字母锁。每个锁需对应钥匙才能通过。钥匙数 k ≤ 6。求拿到所有钥匙的最少移动次数，无法则 -1。

- LeetCode 864: https://leetcode.cn/problems/shortest-path-to-get-all-keys （30×30，k ≤ 6）

### 核心思路
**BFS + 状态压缩（分层图思想）**：图上的点 = (行, 列, 已收集钥匙的状态 bitmask)。钥匙 ≤ 6，状态用 `1 << k` 枚举。
- 先扫一遍网格，找到起点 `@`（状态 0），并求出所有钥匙的掩码 `key`。
- BFS 逐层扩散：越界/墙跳过；遇到锁但无对应钥匙跳过；遇到钥匙就 `ns |= 1 << (ch - 'a')`。
- `ns == key` 时直接返回当前层数（剪枝）。

### 坑点
- `visited` 是三维 `[n][m][1<<6]`，状态维度必须包含钥匙状态，否则会漏掉"拿不同钥匙组合"的路径。
- 清空 visited 时 `s` 循环到 `key` 即可（不是到 `1<<6`）。

### 代码
```cpp
const int MAXN = 31, MAXM = 31, MAXK = 6;
int move_[] = { -1, 0, 1, 0, -1 };
char grid_[MAXN][MAXM];
bool visited[MAXN][MAXM][1 << MAXK];
int queue_[MAXN * MAXM * (1 << MAXK)][3];
int l, r, n, m, key;

void build(vector<string>& g) {
    l = r = key = 0;
    n = g.size(); m = g[0].size();
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) grid_[i][j] = g[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (grid_[i][j] == '@') { queue_[r][0] = i; queue_[r][1] = j; queue_[r++][2] = 0; }
        if (grid_[i][j] >= 'a' && grid_[i][j] <= 'f') key |= 1 << (grid_[i][j] - 'a');
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        for (int s = 0; s <= key; s++) visited[i][j][s] = false;
}

int shortestPathAllKeys(vector<string>& grid) {
    build(grid);
    int level = 1;
    while (l < r) {
        for (int k = 0, size = r - l, x, y, s; k < size; k++) {
            x = queue_[l][0]; y = queue_[l][1]; s = queue_[l++][2];
            for (int i = 0, nx, ny, ns; i < 4; i++) {
                nx = x + move_[i]; ny = y + move_[i + 1]; ns = s;
                if (nx < 0 || nx == n || ny < 0 || ny == m || grid_[nx][ny] == '#') continue;
                if (grid_[nx][ny] >= 'A' && grid_[nx][ny] <= 'F' && (ns & (1 << (grid_[nx][ny] - 'A'))) == 0) continue;
                if (grid_[nx][ny] >= 'a' && grid_[nx][ny] <= 'f') ns |= 1 << (grid_[nx][ny] - 'a');
                if (ns == key) return level;
                if (!visited[nx][ny][ns]) {
                    visited[nx][ny][ns] = true;
                    queue_[r][0] = nx; queue_[r][1] = ny; queue_[r++][2] = ns;
                }
            }
        }
        level++;
    }
    return -1;
}
```

---

## 题目5：电动车游城市

### 题面
电动车满电可行驶 cnt，行驶 1 单位距离耗 1 单位电并花 1 单位时间。N 个城市（0~N-1），paths 表示双向通路。初始电量 0，城市 i 充电桩每充 1 单位电耗时 charge[i]。求从 start 到 end 的最少时间。

- LeetCode LCP 35: https://leetcode.cn/problems/DFPeFJ/ （n ≤ 100，cnt ≤ 100）

### 核心思路
**分层图最短路（扩点/拆点）**：图上的点 = (城市, 到达该城市的剩余电量)，共 n × (cnt+1) 个点。
- 每个状态两种转移：
  1. **充一格电**：`(cur, power)` → `(cur, power+1)`，代价 `+charge[cur]`（需 `power < cnt`）。
  2. **不充电去别的城市**：`(cur, power)` → `(nextCity, power - 距离)`，代价 `+距离`（需 `power ≥ 距离`）。
- 用 STL 小根堆按花费时间排序跑 Dijkstra，遇到 end 直接返回。

### 坑点
- 状态是「城市 + 电量」两个维度，不能只按城市编号去重。
- 初始电量 0，必须先充电才能走（如果邻居距离 > 0）。
- n、cnt 各 ≤ 100，状态数 ≤ 10100，全局 `distance_[101][101]` 够用。

### 代码
```cpp
vector<vector<pair<int, int>>> graph;   // graph[i] = {{邻居, 距离}, ...}
int distance_[MAXN][MAXC];
bool visited[MAXN][MAXC];

struct Record { int cur, power, cost; };
struct Cmp { bool operator()(const Record& a, const Record& b) const { return a.cost > b.cost; } };
priority_queue<Record, vector<Record>, Cmp> heap;

int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
    int n = charge.size();
    graph.clear(); graph.resize(n);
    for (auto& path : paths) {
        graph[path[0]].push_back({ path[1], path[2] });
        graph[path[1]].push_back({ path[0], path[2] });
    }
    for (int i = 0; i < n; i++) for (int j = 0; j <= cnt; j++) {
        distance_[i][j] = INT_MAX; visited[i][j] = false;
    }
    distance_[start][0] = 0;
    heap = priority_queue<Record, vector<Record>, Cmp>();
    heap.push({ start, 0, 0 });
    while (!heap.empty()) {
        Record rec = heap.top(); heap.pop();
        int cur = rec.cur, power = rec.power, cost = rec.cost;
        if (visited[cur][power]) continue;
        if (cur == end) return cost;   // 发现终点直接返回
        visited[cur][power] = true;
        if (power < cnt) {   // 充一格电
            if (!visited[cur][power + 1] && cost + charge[cur] < distance_[cur][power + 1]) {
                distance_[cur][power + 1] = cost + charge[cur];
                heap.push({ cur, power + 1, cost + charge[cur] });
            }
        }
        for (auto& edge : graph[cur]) {   // 不充电去别的城市
            int nextCity = edge.first;
            int restPower = power - edge.second;
            int nextCost = cost + edge.second;
            if (restPower >= 0 && !visited[nextCity][restPower] && nextCost < distance_[nextCity][restPower]) {
                distance_[nextCity][restPower] = nextCost;
                heap.push({ nextCity, restPower, nextCost });
            }
        }
    }
    return -1;
}
```

---

## 题目6：飞行路线（免费 k 次）

### 题面
n 个城市（0~n-1），m 条航线（双向，价格 c），可免费在最多 k 条航线上搭乘。求从 s 到 t 的最少花费。

- 洛谷 P4568: https://www.luogu.com.cn/problem/P4568 （n ≤ 1e4，m ≤ 1e5，k ≤ 10）

### 核心思路
**分层图最短路（扩点）**：图上的点 = (城市, 已使用的免费次数)。状态转移：
- **使用免费**：`(u, use)` → `(v, use+1)`，代价不变（需 `use < k`）。
- **不用免费**：`(u, use)` → `(v, use)`，代价 `+w`。

两个版本：文件一用语言提供的堆（STL，动态，能过但慢 ~100ms）；文件二手写普通堆（静态，推荐，~80ms）。

### 坑点
- 城市编号从 0 开始（区别于一般题目的 1 开始）。
- 无向图，每条边要 `addEdge(a,b,c)` + `addEdge(b,a,c)`。
- 这里两个参数的组合才是一个点，所以**不用反向索引堆**（二维点变一维下标较绕），手写普通堆即可。

### 代码（自己手撸的堆版本）
```cpp
const int MAXN = 10001, MAXM = 100001, MAXK = 11;
int head[MAXN], nxt[MAXM], to[MAXM], weight[MAXM], cnt;
int distance_[MAXN][MAXK];
bool visited[MAXN][MAXK];

struct Node { int u, use, cost; };
Node heap[MAXM * MAXK];
int heapSize;
int n, m, k, s, t;

void push(int u, int t, int c) {
    heap[heapSize] = { u, t, c };
    int i = heapSize++;
    while (heap[i].cost < heap[(i - 1) / 2].cost) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int u, use, cost;
void pop() {
    u = heap[0].u; use = heap[0].use; cost = heap[0].cost;
    swap(heap[0], heap[--heapSize]);
    heapify(0);
}
void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1].cost < heap[l].cost ? l + 1 : l;
        best = heap[best].cost < heap[i].cost ? best : i;
        if (best == i) break;
        swap(heap[best], heap[i]);
        i = best; l = i * 2 + 1;
    }
}

int dijkstra() {
    distance_[s][0] = 0;
    push(s, 0, 0);
    while (heapSize > 0) {
        pop();
        if (visited[u][use]) continue;
        visited[u][use] = true;
        if (u == t) return cost;   // 发现终点直接返回
        for (int ei = head[u], v, w; ei > 0; ei = nxt[ei]) {
            v = to[ei]; w = weight[ei];
            if (use < k && distance_[v][use + 1] > distance_[u][use]) {   // 使用免费
                distance_[v][use + 1] = distance_[u][use];
                push(v, use + 1, distance_[v][use + 1]);
            }
            if (distance_[v][use] > distance_[u][use] + w) {   // 不用免费
                distance_[v][use] = distance_[u][use] + w;
                push(v, use, distance_[v][use]);
            }
        }
    }
    return -1;
}
```

---

## 本课总结

**Dijkstra 核心**：每次从堆中取「距离最小且未弹出」的点，用它的距离松弛邻边，直到堆空或弹出终点。

**分层图最短路（扩点）通用套路**：
1. 图上的点不止是「节点编号」，而是「节点编号 + 额外状态」的组合。
2. 题目 4（钥匙 bitmask）、题目 5（剩余电量）、题目 6（已免单次数）本质都是加一个状态维把问题变成普通最短路/BFS。
3. **核心在于「如何扩点、如何到达、如何算距离」**——每个题这三个问题的答案不同，但结构完全一致。
