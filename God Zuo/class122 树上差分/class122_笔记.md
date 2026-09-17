# class122 树上差分 笔记

> 树上问题专题五。前置：树上倍增与LCA（118）、链式前向星建图（059）、树形DP（078/079）、递归改迭代（118）、二分答案法（051）。

## 树上差分：点差分与边差分

树上差分解决的核心问题：给很多「路径修改」操作（比如把 a 到 b 路径上的点权/边权都加 v），能不能用**单次操作 O(1)** 的代价完成，最后**一遍 DFS** 统一加工出所有点的正确值。

一切的前提是能快速求出路径两端点的**最低公共祖先 LCA**（倍增或 tarjan，见讲解118）。

### 点差分（改点权）

路径 x→y 上所有点权加 v，只需要做 **4 条操作**：

```
num[x] += v
num[y] += v
num[lca] -= v
num[father(lca)] -= v
```

最后一遍 DFS 汇总：`num[u] += 所有子节点的 num`。

**道理**：x 加 v 会沿路径一路向上传递到 lca，y 加 v 也会传递到 lca，lca 处累计了两份 v，所以要减掉一份 v；但整棵子树还「盈余」了一个 v 往外冒，所以在 lca 的父亲处再减一个 v 把影响彻底抵消。根节点上方设一个虚拟 0 号节点（点权恒 0）承接这个减操作。

### 边差分（改边权）

路径 x→y 上所有边权加 v，只需要做 **3 条操作**：

```
num[x] += v
num[y] += v
num[lca] -= 2 * v
```

最后一遍 DFS 汇总：`num[u] += 所有子节点的 num`；此时 `num[u]` 的含义就是「u 到父节点这条边」被修改的增量（原始边权 + num[u] 就是新边权）。

**道理**：点差分里 lca 处要减 v、lca 父亲处也要减 v，而边差分里 lca 到父节点这条边**本来就不该被修改**，所以把这两个减操作合并成 lca 处一次 `-2*v`，把影响在 lca 处就彻底消掉，不让它冒到 lca 的父边上去。

---

## 题目一：树上点差分模版（P3128）

**题面**
n 个节点形成一棵树，初始所有点权都是 0；给定 m 个操作 (a,b)，表示从 a 到 b 路径上所有点的点权 +1。所有操作完成后，返回树上的最大点权。

**核心思路**
裸的点差分模板，用倍增法求 LCA：
1. `dfs1` 建 ST 表（`deep` 深度 + `stjump` 倍增跳表）；
2. 每条操作做 4 条点差分（两端点 +1，lca -1，lca 的父亲 -1），lca 的父亲直接用 `stjump[lca][0]` 拿到；
3. `dfs2` 一遍 DFS 汇总点权，最后取 `num[1..n]` 的最大值。

**坑点**
- java 递归版会爆栈（C++ 能过），迭代版见「写法 2」，逻辑完全一样。
- 根的父节点是虚拟 0 号点：`stjump[根][0] = 0`，`num[0]` 随便减不影响最终结果。
- 复杂度：倍增建表 O(n log n) + O(m)，tarjan 则是 O(n) + O(m)。

### 写法 1：递归版

```cpp
const int MAXN = 50001, LIMIT = 16;
int power, cnt;
int num[MAXN], head[MAXN], nxt[MAXN << 1], to[MAXN << 1];
int deep[MAXN], stjump[MAXN][LIMIT];

int log2(int n) { int ans = 0; while ((1 << ans) <= (n >> 1)) ans++; return ans; }

void dfs1(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++)
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    for (int e = head[u]; e != 0; e = nxt[e])
        if (to[e] != f) dfs1(to[e], u);
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) swap(a, b);
    for (int p = power; p >= 0; p--)
        if (deep[stjump[a][p]] >= deep[b]) a = stjump[a][p];
    if (a == b) return a;
    for (int p = power; p >= 0; p--)
        if (stjump[a][p] != stjump[b][p]) { a = stjump[a][p]; b = stjump[b][p]; }
    return stjump[a][0];
}

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = nxt[e]) { v = to[e]; if (v != f) dfs2(v, u); }
    for (int e = head[u], v; e != 0; e = nxt[e]) { v = to[e]; if (v != f) num[u] += num[v]; }
}
// 每条操作：num[u]++, num[v]++, num[lca(u,v)]--, num[stjump[lca][0]]--
```

### 写法 2：迭代版

`dfs1`、`dfs2` 递归改迭代（栈里存 `(u, f, e)` 三元组，`e == -1` 表示第一次来到 u），其余完全一样。改法见讲解118。

---

## 题目二：松鼠的新家（P3258）

**题面**
n 个节点形成一棵树，给定一个点编号数组 `travel` 表示松鼠依次要去往的地点。松鼠每走到一个节点必须拿一个糖果，否则停止前进；到达最后一个地点时不需要吃糖果。打印每个节点上至少准备多少糖果才能让松鼠走完。

**核心思路**
点差分 + **tarjan 批量求 LCA**：
1. 相邻地点 `(travel[i], travel[i+1])` 看成一条路径，全部做点差分（两端点 +1，lca -1，lca 父亲 -1）；
2. tarjan 一次性求出所有相邻点对的 LCA（存进 `ans`），并用 `father` 数组单独记录每个节点的真实父亲（不是并查集的父亲）；
3. 一遍 DFS 汇总点权后，**除了第一个地点**，其余 `travel[2..n]` 的糖果数都 -1：中间节点是因为「作为上一条路的终点、又作为下一条路的起点」被重复算了一次；最后一个节点是因为题目要求不需要糖果。

**坑点**
- 这里 LCA 用 **tarjan**（讲解118），注意 `father` 数组记录的是真实树上的父节点，`unionfind` 才是 tarjan 的并查集，两者要分开。
- 最后 -1 从 `travel[2]` 到 `travel[n]`，第一个地点 `travel[1]` 不减。
- java 递归版会爆栈，需改迭代版；tarjan、find、dfs 都要改（find 的路径压缩也用栈模拟）。

```cpp
const int MAXN = 300001;
int travel[MAXN], num[MAXN];
int headEdge[MAXN], edgeNext[MAXN << 1], edgeTo[MAXN << 1], tcnt;
int headQuery[MAXN], queryNext[MAXN << 1], queryTo[MAXN << 1], queryIndex[MAXN << 1], qcnt;
bool visited[MAXN];
int unionfind[MAXN], father[MAXN], ans[MAXN];

int find(int i) { return i != unionfind[i] ? unionfind[i] = find(unionfind[i]) : unionfind[i]; }

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) { v = edgeTo[e]; if (v != f) tarjan(v, u); }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) ans[queryIndex[e]] = find(v);
    }
    unionfind[u] = f;
    father[u] = f;
}

void dfs(int u, int f) {
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) { v = edgeTo[e]; if (v != f) dfs(v, u); }
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) { v = edgeTo[e]; if (v != f) num[u] += num[v]; }
}

void compute(int n) {
    tarjan(1, 0);
    for (int i = 1; i < n; i++) {
        int u = travel[i], v = travel[i + 1], lca = ans[i], lcafather = father[lca];
        num[u]++; num[v]++; num[lca]--; num[lcafather]--;
    }
    dfs(1, 0);
    for (int i = 2; i <= n; i++) num[travel[i]]--;
}
```

---

## 题目三：最小化旅行的价格总和（LeetCode 2646）

**题面**
n 个节点形成一棵树，每个节点有点权，给定很多路径（每条路径有开始点、结束点，代价 = 沿途点权和，所有路径代价之和就是旅行总价）。你可以选择把**某些点**的点权减半，但**选择的点不能相邻**。返回旅行价格总和最少能是多少。

**核心思路**
点差分（统计次数） + **树形 DP**（讲解078/079）：
1. 用一个**次数数组** `num` 做点差分，统计每个点被多少条路径经过（注意：差分的是「经过次数」，不是原有点权 `price`）。
2. 树形 DP 两状态：`no` = u 一定不减半时以 u 为头的子树最小花费，`yes` = u 一定减半时以 u 为头的子树最小花费：
   ```
   n = price[u] * num[u];           // u 不减半，自己贡献全价 * 经过次数
   y = (price[u] / 2) * num[u];     // u 减半，自己贡献半价 * 经过次数
   对每个孩子 v：n += min(no_v, yes_v);  y += no_v;   // 减半则孩子都不能减半
   ```
3. 最终答案 `min(no_根, yes_根)`。

**坑点**
- LeetCode 编号从 0 开始，代码里统一 +1 调整成从 1 开始。
- 差分的是 `num`（次数）数组，不是 `price`（原有点权）数组，别改错。
- LCA 有两种写法：倍增（`dfs1` 建表）和 tarjan，功能一样。

```cpp
const int MAXN = 51, LIMIT = 6;
int power, cnt;
int price[MAXN], num[MAXN], head[MAXN], nxt[MAXN << 1], to[MAXN << 1];
int deep[MAXN], stjump[MAXN][LIMIT];
int no, yes;

void dp(int u, int f) {
    int n = price[u] * num[u];
    int y = (price[u] / 2) * num[u];
    for (int e = head[u], v; e != 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dp(v, u);
            n += min(no, yes);
            y += no;
        }
    }
    no = n;
    yes = y;
}
// 先点差分求出 num[1..n]（每条路径：num[u]++, num[v]++, num[lca]--, num[stjump[lca][0]]--）
// 再 dp(1, 0)，答案 min(no, yes)
```

---

## 题目四：使图不连通的方法数（POJ 3417，边差分实战）

**题面**
n 个节点、n-1 条「老边」连成一棵树，再额外加 m 条「新边」。你可以切断两条边让图不连通，且**必须切一条老边 + 一条新边**。返回方法数。

**核心思路**
边差分 + 结构分析。把每条新边 (u,v) 看成一次边差分（`num[u]++`, `num[v]++`, `num[lca]-=2`），DFS 汇总后，每条老边的「边权」= 它被几条新边形成的环覆盖（`w = num[子节点]`）：
- `w == 0`：这条老边不在任何新环上，切断它图就断开，再任选一条新边都行 → 贡献 **m** 种；
- `w == 1`：这条老边被唯一一条新边覆盖，切断它后必须再切「那条新边」才能断 → 贡献 **1** 种；
- `w > 1`：被多条新边覆盖，只切一条新边不够断 → 贡献 **0** 种。

所有老边贡献相加就是答案。

**坑点**
- 老边原始边权都是 0（`w = 0 + num[v]`），边权 = 点权 `num[v]` 汇总值。
- 本题递归不改迭代也能过（POJ 数据不大）。
- 用倍增求 LCA，复杂度 O(n log n + m + n)。

```cpp
const int MAXN = 100001, LIMIT = 17;
int n, m, power, cnt, ans;
int num[MAXN], head[MAXN], nxt[MAXN << 1], to[MAXN << 1];
int deep[MAXN], stjump[MAXN][LIMIT];

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = nxt[e]) { v = to[e]; if (v != f) dfs2(v, u); }
    for (int e = head[u], v, w; e != 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            w = 0 + num[v];
            if (w == 0) ans += m;
            else if (w == 1) ans += 1;
            num[u] += num[v];
        }
    }
}
// 每条新边：num[u]++, num[v]++, num[lca(u,v)] -= 2
```

---

## 题目五：运输计划（P2680）

**题面**
n 个节点、n-1 条边（每条边有正数边权）连成一棵树，给定很多运输计划 (a,b)（代价 = 沿途边权和，计划之间互不干扰）。你只能选**一条边**把边权变成 0，目标是让所有运输计划代价的**最大值尽量小**，返回这个最小化的最大值。

**核心思路**
**二分答案法**（讲解051） + 边差分：
1. 先用 tarjan 一遍求出每个计划的两端点 LCA、代价 `cost[i]`（`dist[u]+dist[v]-2*dist[lca]`），以及 `maxCost`（最大代价）。
2. 答案落在 `[0, maxCost]`，二分 `limit`，用 `f(limit)` 判断「能否让所有计划代价 ≤ limit」：
   - `atLeast = maxCost - limit`：某条边至少要能减掉这么多边权；
   - 对所有 `cost[i] > limit` 的**超标**计划做边差分（`num[u]++`, `num[v]++`, `num[lca]-=2`），`beyond` = 超标计划数；
   - 若 `beyond == 0` 直接 true；否则找一条边同时满足：**被所有超标计划经过**（`num[该边]==beyond`）且 **边权 ≥ atLeast**。存在则 true。
3. 二分收窄得到最小可行 `limit`。

**坑点**
- 边差分时「边被经过的次数」体现在子节点上：`num[u]` 汇总后代表 u 到父节点这条边被超标计划经过的次数。
- 需要两个数组：`dist`（根到每个点的距离，tarjan 过程中顺手更新）、`father`（真实父节点）。`distance` 数组名会和 `std::distance` 冲突，C++ 里改名 `dist`。
- 递归版（tarjan + dfs）在 java 会爆栈，需改迭代版；逻辑完全一样。
- 复杂度：tarjan O(n+m)，二分 O(log maxCost) 次，每次 O(n)。

```cpp
const int MAXN = 300001, MAXM = 300001;
int n, m, maxCost, atLeast, beyond;
int num[MAXN];
int headEdge[MAXN], edgeNext[MAXN << 1], edgeTo[MAXN << 1], edgeWeight[MAXN << 1], tcnt;
int headQuery[MAXN], queryNext[MAXM << 1], queryTo[MAXM << 1], queryIndex[MAXM << 1], qcnt;
bool visited[MAXN];
int unionfind[MAXN], quesu[MAXM], quesv[MAXM];
int dist[MAXN], lca[MAXM], cost[MAXM];

void tarjan(int u, int f, int w) {
    visited[u] = true;
    dist[u] = dist[f] + w;
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) { v = edgeTo[e]; if (v != f) tarjan(v, u, edgeWeight[e]); }
    for (int e = headQuery[u], v, i; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            i = queryIndex[e];
            lca[i] = find(v);
            cost[i] = dist[u] + dist[v] - 2 * dist[lca[i]];
            maxCost = max(maxCost, cost[i]);
        }
    }
    unionfind[u] = f;
}

bool dfs(int u, int f, int w) {
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) if (dfs(v, u, edgeWeight[e])) return true;
    }
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) { v = edgeTo[e]; if (v != f) num[u] += num[v]; }
    return num[u] == beyond && w >= atLeast;
}

bool f(int limit) {
    atLeast = maxCost - limit;
    memset(num + 1, 0, n * sizeof(int));
    beyond = 0;
    for (int i = 1; i <= m; i++)
        if (cost[i] > limit) { num[quesu[i]]++; num[quesv[i]]++; num[lca[i]] -= 2; beyond++; }
    return beyond == 0 || dfs(1, 0, 0);
}
// 二分：l=0, r=maxCost; f(mid) 为真则记答案并 r=mid-1，否则 l=mid+1
```
