# class057 并查集（下）

> B站视频：[算法讲解057](https://www.bilibili.com/video/BV1Gy4y1T7TB/)
> 前置知识：class056（并查集上）

## 核心知识：并查集的扩展应用

本节课通过4道典型题展示并查集的**小扩展**：

- **维护集合数量**（`sets`）：初始化 `sets = n`，每次成功 union 时 `sets--`。最终是连通分量数。
- **维护集合大小**（`size`）：小挂大优化顺带得到，可用于统计某分量节点数。
- **给集合打标签**（`infect`、`secret` 等）：根节点携带额外信息，union 时信息随根合并。
- **选择性建图**（如只连非病毒节点）：并查集不一定要连所有节点，可以根据条件跳过某些节点。

**更高级的扩展**（进阶课程）：带权并查集、可持久化并查集、可撤销并查集。

---

## 01 移除最多的同行或同列石头 — LeetCode 947

**题面：** 二维平面上 n 块石头，同行或同列的石头属于同一连通分量。每个分量可移除到只剩 1 块。求最多能移除多少块。

**核心思路：** 并查集 + 公式 `答案 = n - 连通分量数`。用两个哈希表记录每行/列第一次遇到的石头编号，后续同行的都跟第一个 union。

**坑点：** 不是 n² 配对比！用哈希表降到 O(n)。

**代码：**
```cpp
unordered_map<int, int> rowFirst, colFirst;
for (int i = 0; i < n; i++) {
    int r = stones[i][0], c = stones[i][1];
    if (rowFirst.count(r)) unionSet(i, rowFirst[r]);
    else rowFirst[r] = i;
    if (colFirst.count(c)) unionSet(i, colFirst[c]);
    else colFirst[c] = i;
}
return n - sets;
```

---

## 02 找出知晓秘密的所有专家 — LeetCode 2092

**题面：** n 个专家，0 号已知秘密。按时间开会议，同一时间可能有多场。求最终所有知道秘密的专家。

**核心思路：** 按时间排序后分组处理。同一时间的会议全部 union 一遍（同步传播 secret），然后**回查**：如果某组人开完会后仍然不知道秘密，就把他们的 father 重置回自己（撤销——他们聊了也白聊）。关键：会议时间相同的先全连，再根据 secret 选择性保留。

**坑点：** 不是"不知道秘密就不连"——必须先全连让秘密传播，再逐个重修。`secret[fy] |= secret[fx]` 在 union 时自动传播。

**代码：**
```cpp
for (int l = 0; l < m;) {
    int r = l;
    while (r + 1 < m && meetings[l][2] == meetings[r + 1][2]) r++;
    // 先全连
    for (int i = l; i <= r; i++) unionSet(meetings[i][0], meetings[i][1]);
    // 不知道秘密的撤销
    for (int i = l; i <= r; i++) {
        int a = meetings[i][0], b = meetings[i][1];
        if (!secret[find(a)]) father[a] = a, father[b] = b;
    }
    l = r + 1;
}
```

---

## 03 好路径的数目 — LeetCode 2421

**题面：** 树，每个节点有权值 vals。一条"好路径"的起点和终点权值相同，且路径上所有节点的权值都 ≤ 起点权值。求好路径总数。

**核心思路：** 按边两端 max(vals[u], vals[v]) 从小到大排序处理边。维护并查集，根的选取规则：**权值更大的当根**。额外维护 `maxcnt[root]` = 该分量中"最大权值节点"的个数。当两边权值相等时：`ans += maxcnt[fx] * maxcnt[fy]`（边两端所有最大权值节点两两配对形成好路径），然后合并。

**坑点：** 按 max 值排序边是关键——保证处理到这条边时，分量内最大权值不超过当前边的 max。路径减半防爆栈。

**代码：**
```cpp
sort(edges.begin(), edges.end(),
     [&](auto& a, auto& b) { return max(vals[a[0]], vals[a[1]])
                                  < max(vals[b[0]], vals[b[1]]); });
int ans = n;
for (auto& e : edges) {
    int fx = find(e[0]), fy = find(e[1]);
    if (vals[fx] > vals[fy]) father[fy] = fx;
    else if (vals[fx] < vals[fy]) father[fx] = fy;
    else {
        ans += maxcnt[fx] * maxcnt[fy];
        father[fy] = fx; maxcnt[fx] += maxcnt[fy];
    }
}
```

---

## 04 尽量减少恶意软件的传播 — LeetCode 924

**题面：** 无向图，initial 是初始感染节点集。移除一个节点后，求最终感染节点数最少的方案（并列取编号最小）。

**核心思路：** **只在非病毒节点之间建并查集**。统计每个连通分量被哪些病毒"独家"接触：
- -1：无病毒接触（安全）
- `≥0`：只有一个病毒接触，记下病毒编号
- -2：被多个病毒接触（没救了，移除谁都救不了这个分量）

`cnts[i]` = 如果移除病毒 i，能救多少个节点。取 cnts 最大且编号最小的。

**坑点：** 初始化节点不算病毒节点，只在 clean 节点间 union；病毒只负责"接触"但不参与连通。

**代码：**
```cpp
// 只在非病毒节点间建边
for (int i = 0; i < n; i++) {
    if (virusSet.count(i)) continue;
    for (int j = i + 1; j < n; j++)
        if (!virusSet.count(j) && graph[i][j] == 1) unionSet(i, j);
}
// 病毒接触干净组件
for (int sick : initial)
    for (int nb = 0; nb < n; nb++)
        if (!virusSet.count(nb) && graph[sick][nb] == 1) {
            int fn = find(nb);
            if (infect[fn] == -1) infect[fn] = sick;
            else if (infect[fn] != sick) infect[fn] = -2;
        }
// 统计治愈效果
for (int i = 0; i < n; i++)
    if (i == father[i] && infect[i] >= 0)
        cnts[infect[i]] += sz[i];
```
