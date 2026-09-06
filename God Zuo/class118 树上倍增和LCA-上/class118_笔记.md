# class118 树上问题专题1 - 树上倍增和LCA（上）

> 前置知识：并查集、链式前向星建图（讲解059）、树形DP（讲解078/079）、倍增基础（讲解117）。
> 本节讲求「最低公共祖先（LCA）」的两种方法：**树上倍增**（在线，每次 O(log n)）和 **Tarjan**（离线，O(n+m)）。

---

## 一、树节点的第K个祖先

### 题面

树上有 n 个节点，编号 0~n-1，用 parent 数组给出父节点，根节点是 0 号。实现 `TreeAncestor(n, parent)` 和 `getKthAncestor(i, k)`：返回节点 i 往上跳 k 步的节点，不存在返回 -1。

测试链接：https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/

### 核心思路

树上倍增最基础的应用：

1. 链式前向星建**有向图**（每个节点只有一个父节点，父→子建边即可）。
2. dfs 生成 `deep[i]`（节点在第几层）和 `stjump[i][p]`（i 往上跳 2^p 步到达的节点）。
   - 转移：`stjump[i][p] = stjump[stjump[i][p-1]][p-1]`（只依赖上方的节点，树形DP自顶向下填）。
3. 查询第 k 个祖先：
   - 若 `deep[i] <= k` 返回 -1（越过了根）。
   - 目标层数 `s = deep[i] - k`，从高位枚举 p，只要 `deep[stjump[i][p]] >= s` 就往上跳，最后 i 就是答案。

### 坑点

- `power = log2(n)` 决定 st 表列数（本题 MAXN=50001，LIMIT=16）。
- 根节点 0 的 `deep[0] = 1`（单独判断），`stjump[0][0] = 0`（指向不存在的节点）。

### 代码

```cpp
const int MAXN = 50001;
const int LIMIT = 16;
int power;
int head[MAXN], nxt[MAXN], to[MAXN], cnt;
int deep[MAXN];
int stjump[MAXN][LIMIT];

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) ans++;
    return ans;
}

void addEdge(int u, int v) {
    nxt[cnt] = head[u]; to[cnt] = v; head[u] = cnt++;
}

// 当前来到i节点，i节点父亲节点是f
void dfs(int i, int f) {
    deep[i] = (i == 0) ? 1 : deep[f] + 1;
    stjump[i][0] = f;
    for (int p = 1; p <= power; p++)
        stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
    for (int e = head[i]; e != 0; e = nxt[e])
        dfs(to[e], i);
}

class TreeAncestor {
public:
    TreeAncestor(int n, vector<int>& parent) {
        power = log2(n);
        cnt = 1;
        memset(head, 0, n * sizeof(int));
        for (int i = 1; i < (int)parent.size(); i++)
            addEdge(parent[i], i);
        dfs(0, 0);
    }

    int getKthAncestor(int i, int k) {
        if (deep[i] <= k) return -1;
        int s = deep[i] - k;  // s是想要去往的层数
        for (int p = power; p >= 0; p--)
            if (deep[stjump[i][p]] >= s) i = stjump[i][p];
        return i;
    }
};
```

---

## 二、最近公共祖先（树上倍增法）

### 题面

给定一棵树（n 个节点），m 次查询两个节点的最低公共祖先（LCA）。n 可达 5×10^5。

测试链接：https://www.luogu.com.cn/problem/P3379

### 核心思路

1. 建**无向图**（题目给定头节点 root，边是无向的），从 root 开始 dfs 生成 deep 数组和 stjump 表。
2. LCA 查询分两步：
   - **先对齐深度**：让较深的 a 往上跳到与 b 同层（用倍增，保证 `deep[stjump[a][p]] >= deep[b]`）。
   - **再一起往上跳**：从高位枚举 p，只要 `stjump[a][p] != stjump[b][p]` 就一起跳（保证不会跳过 LCA）；最后 `return stjump[a][0]`（再往上一步就是 LCA）。
   - 特判：对齐后若 `a == b`，说明 b 就是 LCA。

### 坑点

- n=5×10^5，LIMIT=20（2^19 够用）。树可能退化成一条链，递归 dfs 在 Java 会爆栈，**C++ 能通过**。
- 单次查询 O(log n)，m 次 O(m log n)。倍增是**在线**算法。

### 代码（递归版）

```cpp
const int MAXN = 500001;
const int LIMIT = 20;
int power;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], cnt;
int deep[MAXN];
int stjump[MAXN][LIMIT];

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++)
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    for (int e = head[u]; e != 0; e = nxt[e])
        if (to[e] != f) dfs(to[e], u);
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) { int tmp = a; a = b; b = tmp; }
    for (int p = power; p >= 0; p--)
        if (deep[stjump[a][p]] >= deep[b]) a = stjump[a][p];
    if (a == b) return a;
    for (int p = power; p >= 0; p--)
        if (stjump[a][p] != stjump[b][p]) { a = stjump[a][p]; b = stjump[b][p]; }
    return stjump[a][0];
}
```

---

## 三、最近公共祖先（Tarjan 算法）

### 题面

同题二，但换用 Tarjan 离线算法。

### 核心思路

Tarjan 是**离线**批量算法：把 m 个查询先挂到每个节点的「问题列表」上（链式前向星存储），然后 **dfs 遍历整棵树一遍**，用并查集维护集合，就得到所有答案，总复杂度 **O(n+m)**。

过程（递归版）：

1. 来到节点 u，标记 `visited[u] = true`。
2. 遍历每个孩子 v（v != f），递归 `tarjan(v, u)`，返回后把 v 的集合合并到 u（`father[v] = u`）。
3. 处理 u 的问题列表：对每个 `(u, v)`，若 `visited[v]` 为 true，则 `ans[查询编号] = find(v)`（v 所在集合的代表节点就是 LCA）。

关键：每遍历完一棵子树，就把整棵子树合并到当前节点，并把当前节点设为代表节点。当查询的两个点中后出现的那个点被访问时，先出现的点所在集合的代表节点恰好就是它们的 LCA。

### 坑点

- 需要**两套链式前向星**：一套存树的边（headEdge/edgeNext/edgeTo），一套存每个节点的问题列表（headQuery/queryNext/queryTo/queryIndex）。
- 每条查询要**双向**挂到两个节点上（addQuery(u,v,i) 和 addQuery(v,u,i)）。
- 递归版在 Java 会爆栈（find 递归 + tarjan 递归），C++ 能过。
- 迭代版：并查集 find 改成非递归（用栈记录路径再扁平化），tarjan 改成显式栈（u/f/e 三元组）。为便于改迭代，先把递归版改成「等义」写法：把 `father[v]=u` 挪到遍历完所有子树之后统一执行 `father[u]=f`。

### 代码（递归版）

```cpp
const int MAXN = 500001;
int headEdge[MAXN], edgeNext[MAXN << 1], edgeTo[MAXN << 1], tcnt;
int headQuery[MAXN], queryNext[MAXN << 1], queryTo[MAXN << 1], queryIndex[MAXN << 1], qcnt;
bool visited[MAXN];
int father[MAXN];
int ans[MAXN];

int find(int i) {
    if (i != father[i]) father[i] = find(father[i]);
    return father[i];
}

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) { tarjan(v, u); father[v] = u; }
    }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) ans[queryIndex[e]] = find(v);
    }
}
```

---

## 总结

| 方法 | 复杂度 | 在线/离线 | 适用 |
|---|---|---|---|
| 树上倍增 | 预处理 O(n log n)，单次 O(log n) | 在线 | 高频单点查询 |
| Tarjan | 一次遍历 O(n+m) | 离线（批量） | 一次性给出一批查询 |

**递归改迭代（显式栈）通用套路**：栈里存 `(u, f, e)` 三元组——u 当前节点、f 父节点、e 处理到几号边。`e == -1` 表示第一次到达（做"进入节点"的工作），`e == 0` 表示所有边处理完（做"离开节点"的工作）；压栈时先把自己 `(u, f, 下一条边)` 压回，再压孩子 `(child, u, -1)`。当数据量很大、递归可能爆栈时，必须掌握。
