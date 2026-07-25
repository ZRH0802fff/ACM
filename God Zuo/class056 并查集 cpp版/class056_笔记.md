# class056 并查集（上）

> B站视频：[算法讲解056](https://www.bilibili.com/video/BV1Vy4y1T7Xx/)
> 前置知识：无

## 核心知识：并查集

### 是什么 / 什么时候用

**并查集**用来解决：**集合的合并与查询**——初始每个元素各成一个集合，支持 `find`（找代表）、`union`（合并两个集合）、`isSameSet`（判断是否同集合）。

**识别特征：** 题目要求"连通分量数量"、"动态合并集合"、"同组/同类的合并"、"图的连通性"、"最少交换次数"等 → 并查集。

**时间复杂度：** 均摊 O(1)，实际是 α(n)（阿克曼函数的反函数）。n 大到 10^80 才可能达到 6，所以可以视为 O(1)。该结论由 Galler 和 Fischer 在 1964 年提出，1989 年完整证明。

**三个核心操作：**
1. `find(i)`：找 i 的代表节点（根），含**路径压缩**
2. `union(a, b)`：a 和 b 所在集合合并为一个，含**小挂大**优化
3. `isSameSet(a, b)`：`find(a) == find(b)`

**扩展用法：** 可额外维护集合数量（`sets`）、每个集合的元素个数（`size`）、以及给集合打标签（如"感染源"）。带权并查集、可持久化并查集在高级课程中讲解。

### 三个核心操作

1. **find(i)：** 找 i 的代表节点（根）。含**路径压缩**——沿途所有节点直接挂到根上。
2. **union(x, y)：** 合并两个集合。含**小挂大**优化——节点数少的集合挂到多的下面，防止链退化。
3. **isSameSet(x, y)：** `find(x) == find(y)`。

### 路径压缩图示推演

假设初始每个节点各成一个集合：`1→1, 2→2, 3→3, 4→4, 5→5`

经过一系列 union 后，链变成 `4→3→2→1`（1 是根）：

```
find(4) 调用前：  4 → 3 → 2 → 1
find(4) 调用后：  4 → 1, 3 → 1, 2 → 1  （沿途节点全部直挂根）
```

**递归版：** `father[i] = find(father[i])` —— 递归返回根，每层都把当前节点的 father 直接设成根。

**迭代版（防爆栈）：** 先用 path 数组收集 4→3→2，找到根 1，然后 `father[4]=father[3]=father[2]=1`。

**路径减半（Path Halving）：** 不爆栈、常数最小。
```cpp
while (i != father[i]) {
    father[i] = father[father[i]]; // 跳到爷爷
    i = father[i];
}
```
`4→3→2→1` 经过一次 find(4)：`father[4]=father[father[4]]=father[3]=2`，变成 `4→2→1`，再跳 `father[4]=father[father[4]]=father[2]=1`，最终 `4→1`。每次跳两层，效果等同压缩。

### 小挂大图示

```
fx(大小3)    fy(大小1)
  1            5
 / \
2   3

合并 fx→fy（错误）:    合并 fy→fx（正确小挂大）:
    1                   1
   / \                 /|\
  2   3               2 3 5
  |
  5                   ↑ 挂到大小大的下面
  ↑ 链变长
```
小挂大保证：每次合并后树高最多增加 1（当两个集合 size 相同时），否则不增加。配合路径压缩，均摊 O(α(n)) ≈ O(1)。

---

## 01 并查集模板 — 洛谷 P3367

**题面：** n 个元素，m 个操作：`1 x y` 查询是否同集合，`2 x y` 合并。

**代码：**
```cpp
int find(int i) {
    int path[MAXN], cnt = 0;
    while (i != father[i]) { path[cnt++] = i; i = father[i]; }
    for (int k = 0; k < cnt; k++) father[path[k]] = i;
    return i;
}
void unionSet(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        if (sz[fx] >= sz[fy]) { sz[fx] += sz[fy]; father[fy] = fx; }
        else { sz[fy] += sz[fx]; father[fx] = fy; }
    }
}
```

---

## 02 亲戚问题 — 洛谷 P1551

**题面：** 简化版并查集——纯路径压缩，无小挂大。

**坑点：** 递归路径压缩可能爆栈（洛谷需 `sys.setrecursionlimit`），C++ 一般没问题。

**代码：**
```cpp
int find(int i) {
    if (i != father[i]) father[i] = find(father[i]);
    return father[i];
}
```

---

## 03 情侣牵手 — LeetCode 765

**题面：** 2n 个人坐一排，每对情侣编号 pairId = row[i]/2。求最少交换次数使每对相邻。

**核心思路：** 每对相邻座位（`row[2k]` 和 `row[2k+1]`）如果不是一对情侣，就把两个 pairId 连通。最后连通分量数为 `sets`，答案 = `couples - sets`（每个分量内需 `size-1` 次交换）。

**坑点：** 转化是关键——把"位置交换"变成"情侣组连通"的图论问题。

**代码：**
```cpp
int sets = couples;
for (int i = 0; i < n; i += 2) {
    int fx = find(row[i] / 2), fy = find(row[i + 1] / 2);
    if (fx != fy) { father[fx] = fy; sets--; }
}
return couples - sets;
```

---

## 04 相似字符串组 — LeetCode 839

**题面：** 两个字符串"相似"：完全相同，或恰有 2 个位置字符不同（一次交换等价）。求相似组个数。

**核心思路：** O(n²) 暴力比较所有对，diff==0 或 2 即 union。剪枝：`find(i) == find(j)` 时跳过比对。

**坑点：** `diff > 2` 时提前 break，减少无谓比较。

**代码：**
```cpp
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
        if (find(i) != find(j)) { // 剪枝
            int diff = 0;
            for (int k = 0; k < m && diff <= 2; k++)
                if (strs[i][k] != strs[j][k]) diff++;
            if (diff == 0 || diff == 2) unionSet(i, j);
        }
```

---

## 05 岛屿数量 — LeetCode 200

**题面：** 01 网格，连通的 1 组成一个岛屿，求岛屿数量。

**核心思路：** 二维转一维：`index = i*m + j`。只需检查左邻和上邻（足够覆盖 4 方向连通）。路径减半防爆栈。

**坑点：** 只查左和上就可以不漏——因为遍历顺序保证了右和下的边会在后续被处理。

**代码：**
```cpp
int find(int i) {
    while (i != father[i]) {
        father[i] = father[father[i]];
        i = father[i];
    }
    return i;
}
// 遍历时只连左和上
if (j > 0 && grid[i][j-1] == '1') unionSet(i, j, i, j-1);
if (i > 0 && grid[i-1][j] == '1') unionSet(i, j, i-1, j);
```
