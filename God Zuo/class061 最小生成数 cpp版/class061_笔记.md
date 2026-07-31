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

```cpp
sort(edges, edges + m, [](const Edge& a, const Edge& b) { return a.w < b.w; });
for (int i = 0; i < m; i++) {
    if (unionSet(edges[i].u, edges[i].v)) {
        ans += edges[i].w;
        if (++edgeCnt == n - 1) break;
    }
}
```

### 坑点
- 边用 struct 存储（`int edges[MAXM][3]` 无法用 sort）
- 并查集路径压缩：`if (i != father[i]) father[i] = find(father[i]);`

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
