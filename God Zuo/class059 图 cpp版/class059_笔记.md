# class059 建图、链式前向星、拓扑排序 笔记

> 视频：算法讲解059【必备】建图、链式前向星、拓扑排序

---

## 题目1：三种建图方式

### 题面
演示三种图的存储方式：邻接矩阵、邻接表、链式前向星。分别用于有向图和无向图带权图的建立和遍历。

### 核心思路

**邻接矩阵**：`graph[u][v] = w`。O(1)查询边，O(V²)空间。适合稠密图。

**邻接表**：每个节点维护一个邻居列表。动态灵活，但遍历缓存不友好。

**链式前向星（重点）**：静态数组模拟链表，竞赛首选。
```cpp
int head[MAXN], nxt[MAXM], to[MAXM], weight[MAXM], cnt;
void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}
// 遍历u的所有邻居:
for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
    int v = to[ei], w = weight[ei];
}
```
- 无向图加两次边，MAXM 需设为边数×2
- cnt 从 1 开始（0 作为空的标记）

### 坑点
- 无向图时 MAXM 要准备 m*2
- 链式前向星 cnt 初始化为 1，head 初始化为 0

---

## 题目2：课程表II（拓扑排序模版）

### 题面
numCourses 门课，prerequisites[i]=[ai,bi] 表示修 ai 前必须先修 bi。返回一个合法的学习顺序，若不可能则返回空。

- LeetCode 210: https://leetcode.cn/problems/course-schedule-ii/

### 核心思路
**Kahn算法（BFS拓扑排序）**：
1. 建图 + 入度表：b→a（先修课指向后修课），`indegree[a]++`
2. 入度为 0 的点入队
3. 每次出队一个点，将其邻居入度-1，减到 0 则入队
4. 出队顺序即拓扑序。若出队数 ≠ n，说明有环

### 坑点
- 边的方向：bi→ai（bi 是 ai 的先修课）
- 队列用数组模拟（不用 STL queue）

### 代码
```cpp
int l = 0, r = 0;
for (int i = 0; i < n; i++)
    if (indegree[i] == 0) queue[r++] = i;
while (l < r) {
    int cur = queue[l++];
    for (int next : graph[cur])
        if (--indegree[next] == 0) queue[r++] = next;
}
return (cnt == n) ? queue : empty;
```

---

## 题目3-4：拓扑排序（牛客）

### 题面
给 n 个点 m 条边的有向图，输出拓扑排序结果。若无合法拓扑序输出 -1。

- 牛客：https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c

### 核心思路
同题目2的 Kahn 算法。提供两个版本：
- **动态版**：每次建图用邻接表
- **静态版**：用链式前向星建图，全局数组复用，更快

### 坑点
- 点多边多（n,m≤200000），必须用链式前向星防卡空间
- 入度表、队列等全部用全局静态数组

---

## 题目5：字典序最小的拓扑排序（洛谷）

### 题面
在合法的拓扑排序中输出字典序最小的那个。

### 核心思路
将队列换成**小根堆**：每次从入度为 0 的点中取编号最小的。其他同 Kahn 算法。

- 手写堆：`heapInsert` + `heapify`
- `push(x)`, `pop()`, `isEmpty()`

### 坑点
- 不能用优先队列（STL），手写小根堆保持静态风格
- 堆操作注意维护 heapSize

---

## 题目6：火星词典

### 题面
给定已按外星语言字典序排好的单词列表，推导字母顺序。若矛盾返回 ""。

- LeetCode 269: https://leetcode.cn/problems/alien-dictionary/

### 核心思路
1. 出现过的字符 indegree 初始为 0，未出现为 -1
2. 比较相邻单词：找到第一个不同字符 `cur[j] != next[j]`，建立 cur[j]→next[j] 的边
3. **特殊情况**：若 `cur` 是 `next` 的前缀且更长（如 "abc" "ab"），矛盾返回 ""
4. 拓扑排序，看是否所有出现过的字符都被输出

### 坑点
- indegree 初始化为 -1 标记未出现，出现过的字符才设为 0
- 前缀矛盾检查：`j < cur.length() && j == next.length()`

---

## 题目7：戳印序列

### 题面
给定印章 stamp 和目标 target，初始 ???。每次盖章必须完全盖在序列内（可覆盖已盖章部分）。返回盖章的最左索引顺序，使得最终得到 target。使用次数 ≤ 10*n。

- LeetCode 936: https://leetcode.cn/problems/stamping-the-sequence/

### 核心思路
**反向拓扑排序**：从最终状态反推。

1. 枚举每个可能的盖章位置 i（0 ≤ i ≤ n-m），indegree[i]=m 表示还需匹配 m 个字符
2. 比较 target[i+j] 和 stamp[j]：匹配则 indegree[i]--；不匹配则建立"错误位置→i"的依赖边
3. indegree[i]=0 的位置入队（表示可直接盖章）
4. 队列弹出过程：每次盖章消除一些"错误"，解除依赖，最终得到盖章顺序
5. 结果逆序（因为是反向推导）

### 坑点
- 依赖方向：错误位置 j → 依赖它的盖章起始位置 i
- 最终结果需要逆序
- visited 数组防重复统计同位置错误
