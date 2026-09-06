# class119 树上问题专题2 - 树上倍增和LCA（下）

> 前置知识：讲解118（树上倍增与LCA）、讲解061（最小生成树 Kruskal）、讲解105（字符串哈希）。
> 本节用树上倍增 + LCA 解决 5 道综合题。核心结论：**树上两点距离 `dist(a,b) = deep[a] + deep[b] - 2*deep[lca]`**。

---

## 一、紧急集合

### 题面

树上有 n 个节点，每条边权为 1。每次查询 (a,b,c)：三个人分别站在 a、b、c，选一个点集合，求三人走过的总边数最少是多少，输出集合点和最小花费。n、m ≤ 5×10^5。

测试链接：https://www.luogu.com.cn/problem/P4281

### 核心思路

对三点两两求 LCA，得到 h1=lca(a,b)、h2=lca(a,c)、h3=lca(b,c)。关键结论：**这三个 LCA 只有 1 个或 2 个不同的点**。

- 取 `high` = 较浅（层数小）的那个 LCA，`low` = 较深（层数大）的那个（或唯一的那个）。
- 汇聚点 = `low`（三人往较低的那个祖先汇聚最省）。
- 花费 = `deep[a] + deep[b] + deep[c] - 2*deep[high] - deep[low]`（两条边权为 1，所以距离 = 层数差）。

推导：三人先各到 low（此时 a、b 已汇合在 high 以下），c 额外走到 low，因此总距离 = (deep[a]-deep[high]) + (deep[b]-deep[high]) + (deep[c]-deep[low])，展开即上式。

### 坑点

- 用 `long long` 存 cost（虽然本题数值不溢出，但题目 n 大，谨慎）。
- 洛谷对 Java 空间卡得严，只有 C++ 能全过（逻辑两个语言完全一样）。

### 代码

```cpp
void compute(int a, int b, int c) {
    // 来自对结构关系的深入分析
    int h1 = lca(a, b), h2 = lca(a, c), h3 = lca(b, c);
    int high = h1 != h2 ? (deep[h1] < deep[h2] ? h1 : h2) : h1;
    int low  = h1 != h2 ? (deep[h1] > deep[h2] ? h1 : h2) : h3;
    togather = low;
    cost = (long long)deep[a] + deep[b] + deep[c] - (long long)deep[high] * 2 - deep[low];
}
```

---

## 二、货车运输

### 题面

n 座城市，m 条双向道路 (u,v,w) 限重 w。汽车载重不能超过路径上任意一条边的限重。每次查询 (a,b)：从 a 到 b 的最大载重是多少（即路径上最小边权的最大值）；不连通返回 -1。n≤10^4, m≤5×10^4, q≤3×10^4。

测试链接：https://www.luogu.com.cn/problem/P1967

### 核心思路

1. **最大生成树**：先收集所有边，Kruskal 按权值从大到小排序（贪心：能走大边就不走小边），用并查集选边，选中的边建一棵树（图可能不连通 → 森林）。
2. **倍增 + 路径最小值**：除 `stjump[u][p]` 外再维护 `stmin[u][p]`（u 往上跳 2^p 步的路径中最小的边权）。
   - 转移：`stmin[u][p] = min(stmin[u][p-1], stmin[stjump[u][p-1]][p-1])`。
3. **查询**：先 `find(a) != find(b)` 判断是否连通（-1）。然后像求 LCA 一样对齐深度、一起往上跳，过程中用 `ans = min(ans, stmin[...])` 维护路径最小边权。注意这里是求**最小边权**而非 LCA 节点，所以函数名叫 lca 但返回的是 min。

### 坑点

- 边需要 `struct Edge { u, v, w; }` 并排序（C 风格 `int[m][3]` 不能 sort）。
- 可能是森林，要 `for i in 1..n: if(!visited[i]) dfs(i,0,0)`，每个连通块各自 dfs。
- 每个树的根（f==0）：`stjump[u][0]=u`，`stmin[u][0]=INT_MAX`（根上面没有边）。

### 代码

```cpp
void kruskal(int n, int m) {
    sort(edges + 1, edges + m + 1, [](const Edge& a, const Edge& b) { return a.w > b.w; });
    for (int i = 1, a, b, fa, fb; i <= m; i++) {
        a = edges[i].u; b = edges[i].v;
        fa = find(a); fb = find(b);
        if (fa != fb) { father[fa] = fb; addEdge(a, b, edges[i].w); addEdge(b, a, edges[i].w); }
    }
}

void dfs(int u, int w, int f) {
    visited[u] = true;
    if (f == 0) { deep[u] = 1; stjump[u][0] = u; stmin[u][0] = INT_MAX; }
    else { deep[u] = deep[f] + 1; stjump[u][0] = f; stmin[u][0] = w; }
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        stmin[u][p] = min(stmin[u][p - 1], stmin[stjump[u][p - 1]][p - 1]);
    }
    for (int e = head[u]; e != 0; e = nxt[e])
        if (!visited[to[e]]) dfs(to[e], weight[e], u);
}
```

---

## 三、边权相等的最小修改次数

### 题面

一棵树（0~n-1），每条边有权重 w（1≤w≤26）。每次查询 (a,b)：把 a→b 路径上所有边变成同一种值，至少需要修改几条边。

测试链接：https://leetcode.cn/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/

### 核心思路

利用「权值只有 1~26 种」这个关键约束：

1. **dfs 统计前缀词频**：`weightCnt[u][w]` = 从根到 u 的路径上，权值为 w 的边有几条。转移：先复制父亲的值，再把当前边权 `weightCnt[u][w]++`。
2. **tarjan 离线求所有查询的 LCA**，存到 lca 数组。
3. **查询**：对 w=1..26 枚举，`wcnt = weightCnt[a][w] + weightCnt[b][w] - 2*weightCnt[lca][w]`（路径上权值为 w 的边数）。累加得 `allCnt`（总边数），取最大 `maxCnt`，答案 = `allCnt - maxCnt`。

### 坑点

- `weightCnt` 是二维数组 `[MAXN][MAXW+1]`（下标 0~26，0 恒为 0）。
- tarjan 里 `father[u] = f` 放在遍历完子树之后（等义写法）。
- 权值种类少（26），所以单次查询 O(26)，整体线性。

### 代码

```cpp
void dfs(int u, int w, int f) {
    if (u == 0) memset(weightCnt[u], 0, sizeof(weightCnt[u]));
    else {
        for (int i = 1; i <= MAXW; i++) weightCnt[u][i] = weightCnt[f][i];
        weightCnt[u][w]++;
    }
    for (int e = headEdge[u]; e != 0; e = edgeNext[e])
        if (edgeTo[e] != f) dfs(edgeTo[e], edgeValue[e], u);
}

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = headEdge[u]; e != 0; e = edgeNext[e])
        if (edgeTo[e] != f) tarjan(edgeTo[e], u);
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) lca[queryIndex[e]] = find(v);
    }
    father[u] = f;
}
```

---

## 四、在传球游戏中最大化函数值

### 题面

n 名玩家（0~n-1），`receiver[i]` 表示 i 传球的下一人。从 x 出发传球恰好 k 次，f(x) = 沿途所有触球玩家编号之和（可重复累加）。求 max f(x)。k 可达 long 量级。

测试链接：https://leetcode.cn/problems/maximize-value-of-function-in-a-ball-passing-game/

### 核心思路

倍增 + 前缀和（本质是基环树，但倍增法最好想）：

1. `stjump[i][p]`：i 跳 2^p 步到达的玩家；`stsum[i][p]`：i 跳 2^p 步沿途编号之和。
   - 转移：`stjump[i][p] = stjump[stjump[i][p-1]][p-1]`，`stsum[i][p] = stsum[i][p-1] + stsum[stjump[i][p-1]][p-1]`。
2. 把 k 二进制分解（`kbits` 存 k 的哪些位是 1），对每个起点 i，`sum = i`，按 kbits 逐块累加并跳转，取最大值。

### 坑点

- k 是 long，用 `1LL << power` 防溢出，`stsum` 用 `long long`。
- `LIMIT = 34`（k 最多约 2^34）。
- 最优解是基环树 DP（O(n)），倍增法 O(n log n) 也能过但常数较大。

### 代码

```cpp
void build(long long k) {
    power = 0;
    while ((1LL << power) <= (k >> 1)) power++;
    m = 0;
    for (int p = power; p >= 0; p--)
        if ((1LL << p) <= k) { kbits[m++] = p; k -= 1LL << p; }
}

long long getMaxFunctionValue(vector<int>& receiver, long long k) {
    build(k);
    int n = receiver.size();
    for (int i = 0; i < n; i++) { stjump[i][0] = receiver[i]; stsum[i][0] = receiver[i]; }
    for (int p = 1; p <= power; p++)
        for (int i = 0; i < n; i++) {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
            stsum[i][p] = stsum[i][p - 1] + stsum[stjump[i][p - 1]][p - 1];
        }
    long long sum, ans = 0;
    for (int i = 0, cur; i < n; i++) {
        cur = i; sum = i;
        for (int j = 0; j < m; j++) { sum += stsum[cur][kbits[j]]; cur = stjump[cur][kbits[j]]; }
        ans = max(ans, sum);
    }
    return ans;
}
```

---

## 五、检查树上两节点间的路径是否是回文

### 题面

一棵树（1~n，根为 1），每个节点有一个小写字母。每次查询 (a,b)：判断 a→b 路径上节点字符组成的字符串是否回文。n、m ≤ 10^5。

测试链接：https://ac.nowcoder.com/acm/contest/78807/G

### 核心思路

用**字符串哈希**把路径字符串变成数值，倍增快速求哈希值。

1. 字符转数字：a→1, …, z→26。取进制 K=499，预处理 `kpow[i] = K^i`。
2. 建两张哈希表：
   - `stup[u][p]`：u 往上走 2^p 步的路径哈希（**不含 u 本身**，即从父节点往上）。`stup[u][0] = s[f]`。
   - `stdown[u][p]`：从某祖先往下走 2^p 步到达 u 的路径哈希（不含 u 本身）。`stdown[u][0] = s[f]`。
   - 转移（设 v = jump[u][p-1]，步长 len = 2^(p-1)）：
     `stup[u][p] = stup[u][p-1] * kpow[len] + stup[v][p-1]`
     `stdown[u][p] = stdown[v][p-1] * kpow[len] + stdown[u][p-1]`
3. `hash(from, anc, to)`：上坡（from→anc，用 stup，up 初值 = s[from]）+ 下坡（anc 下一节点→to，用 stdown，down 初值 = s[to]），拼成 `up * kpow[height] + down`。
4. 判断回文：`hash(a, lca, b) == hash(b, lca, a)`（正序哈希 == 逆序哈希）。

### 坑点

- 哈希是「自然溢出」——Java 的 long 与 C++ 的 `long long` 都靠溢出截断，比较的是相等性，两个方向按同样规则溢出即可。
- 上坡跳的判定是 `deep[jump[from][p]] >= deep[lca]`（能到 lca），下坡是 `deep[jump[to][p]] > deep[lca]`（**严格大于**，不能到 lca）。
- 函数名 `hash` 与 `std::hash` 冲突，需改名（如 `calcHash`）；局部变量名 `lca` 与函数 `lca` 冲突，需改名（如 `anc`）。

### 代码

```cpp
void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    jump[u][0] = f;
    stup[u][0] = stdown[u][0] = s[f];
    for (int p = 1, v; p <= power; p++) {
        v = jump[u][p - 1];
        jump[u][p] = jump[v][p - 1];
        stup[u][p] = stup[u][p - 1] * kpow[1 << (p - 1)] + stup[v][p - 1];
        stdown[u][p] = stdown[v][p - 1] * kpow[1 << (p - 1)] + stdown[u][p - 1];
    }
    for (int e = head[u], v; e != 0; e = nxt[e]) {
        v = to[e];
        if (v != f) dfs(v, u);
    }
}

long long calcHash(int from, int anc, int to) {
    long long up = s[from];
    for (int p = power; p >= 0; p--)
        if (deep[jump[from][p]] >= deep[anc]) { up = up * kpow[1 << p] + stup[from][p]; from = jump[from][p]; }
    if (to == anc) return up;
    long long down = s[to];
    int height = 1;
    for (int p = power; p >= 0; p--)
        if (deep[jump[to][p]] > deep[anc]) { down = stdown[to][p] * kpow[height] + down; height += 1 << p; to = jump[to][p]; }
    return up * kpow[height] + down;
}

bool isPalindrome(int a, int b) {
    int anc = lca(a, b);
    return calcHash(a, anc, b) == calcHash(b, anc, a);
}
```

---

## 总结

本节 5 道题都是「树上倍增/LCA 模板 + 特定改写」：

| 题目 | 结合的知识点 | 关键改写 |
|---|---|---|
| 紧急集合 | 距离公式 | 三点 LCA 的 high/low 分析 |
| 货车运输 | 最大生成树 | stmin 维护路径最小边权 |
| 边权修改 | tarjan + 前缀词频 | 权值只有 26 种，枚举 |
| 传球游戏 | 倍增 | stsum 维护编号和，二进制分解 k |
| 路径回文 | 字符串哈希 | stup/stdown 正逆序哈希 |

难点不在倍增/LCA 本身，而在把不同知识点与树结构结合起来的分析。
