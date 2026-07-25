# class079 树型DP（下）— 树型DP和树上背包

> B站视频：[算法讲解079](https://www.bilibili.com/video/BV1Y54y1N7SR/)
> 前置知识：class078（树型DP上）、class073（01背包）

---

## 01 到达首都的最少油耗 — LeetCode 2477

**题面：** n个城市形成树，0是首都，每个城市有1个代表。每辆车seats个座位，相邻城市间行驶耗1升油。求所有人抵达首都的最少油耗。

**核心思路：** DFS后序遍历。`size[u]`=子树人数，`cost[u]`=子树内部总油耗。每个子节点v到u的边需要`ceil(size[v]/seats)`辆车，即`(size[v]+seats-1)/seats`趟。`cost[u] = Σ(cost[v] + 趟数)`。

**坑点：** 无向图用parent参数防回头；整除向上取整写法`(a+b-1)/b`。

**代码：**
```cpp
void dfs(int seats, int u, int p) {
    sz[u] = 1;
    for (int v : graph[u]) {
        if (v != p) {
            dfs(seats, v, u);
            sz[u] += sz[v];
            cost[u] += cost[v] + (sz[v] + seats - 1) / seats;
        }
    }
}
```

---

## 02 相邻字符不同的最长路径 — LeetCode 2246

**题面：** 树（0为根），每个节点有一个字符。找最长路径满足：路径上任意相邻节点字符不同。返回节点数。

**核心思路：** Info = `(maxPathFromHead, maxPath)`。对每个孩子v，若`s[u]!=s[v]`，用其`maxPathFromHead`更新max1/max2（最长链/次长链）。最终：`maxPathFromHead = max1+1`，`maxPath = max(孩子maxPath, max1+max2+1)`。

**坑点：** 只合并字符不同的孩子；叶子返回`(1, 1)`。

**代码：**
```cpp
struct Info { int maxPathFromHead, maxPath; };
Info f(string& s, int u) {
    if (graph[u].empty()) return Info(1, 1);
    int max1 = 0, max2 = 0, maxPath = 1;
    for (int v : graph[u]) {
        Info next = f(s, v);
        maxPath = max(maxPath, next.maxPath);
        if (s[u] != s[v]) {
            if (next.maxPathFromHead > max1) { max2 = max1; max1 = next.maxPathFromHead; }
            else if (next.maxPathFromHead > max2) max2 = next.maxPathFromHead;
        }
    }
    return Info(max1 + 1, max(maxPath, max1 + max2 + 1));
}
```

---

## 03 移除子树后的二叉树高度 — LeetCode 2458

**题面：** 二叉树，m个独立查询：每次移除以某值为根的子树（不修改原树），求树剩余部分的高度。

**核心思路：** DFN序。DFS时给每个节点分配序号`dfn`，记录深度`deep[dfn]`和子树大小`sz[dfn]`。子树在DFN序中是一段**连续区间**。预计算`maxl[i]`=DFN[0..i]的最大深度，`maxr[i]`=DFN[i..end]的最大深度。对于查询v：答案=`max(maxl[dfn[v]-1], maxr[dfn[v]+sz[dfn[v]]])`。

**坑点：** 查询不修改原树，O(1)回答；深度是边数。

**代码：**
```cpp
void dfs(TreeNode* x, int k) {
    int i = ++dfnCnt; dfn[x->val] = i; deep[i] = k; sz[i] = 1;
    if (x->left) { dfs(x->left, k+1); sz[i] += sz[dfn[x->left->val]]; }
    if (x->right) { dfs(x->right, k+1); sz[i] += sz[dfn[x->right->val]]; }
}
// 查询
int leftMax = maxl[dfn[q] - 1];
int rightMax = maxr[dfn[q] + sz[dfn[q]]];
ans = max(leftMax, rightMax);
```

---

## 04 从树中删除边的最小分数 — LeetCode 2322

**题面：** 树，每个节点有权值。删两条边形成三个连通分量，分数=最大异或值-最小异或值。求最小分数。

**核心思路：** DFN序+XOR。DFS求子树XOR值`xorVal[dfn]`。枚举所有边对(O(m²))，取较大DFN端点。两棵子树的关系：①pos在pre子树内→`sum1=xor[pos]`，`sum2=xor[pre]^xor[pos]`，`sum3=全部XOR^xor[pre]`；②独立→`sum1=xor[pos]`，`sum2=xor[pre]`，`sum3=全部XOR^sum1^sum2`。

**坑点：** 判断两个子树是否嵌套：`pos < pre + sz[pre]`。

**代码：**
```cpp
for (int i = 0; i < m; i++) {
    a = max(dfn[edges[i][0]], dfn[edges[i][1]]);
    for (int j = i+1; j < m; j++) {
        b = max(dfn[edges[j][0]], dfn[edges[j][1]]);
        pre = min(a,b); pos = max(a,b);
        sum1 = xorVal[pos];
        if (pos < pre + sz[pre]) {
            sum2 = xorVal[pre] ^ xorVal[pos];
            sum3 = xorVal[1] ^ xorVal[pre];
        } else {
            sum2 = xorVal[pre];
            sum3 = xorVal[1] ^ sum1 ^ sum2;
        }
        ans = min(ans, max({sum1,sum2,sum3}) - min({sum1,sum2,sum3}));
    }
}
```

---

## 05 选课（树上01背包） — 洛谷 P2014

**题面：** n门课，每门课可能有先修课。选m门课获得最大学分。先修关系构成树（0号虚拟节点为根）。

### 普通解法 O(n·avgChildren·m²)

三维DP。`f(i,j,k)`=节点i和它的前j棵子树，选k个节点（连通）的最大累加和。跳过第j棵子树→`f(i,j-1,k)`；从第j棵子树选s个→`f(i,j-1,k-s)+f(v, allChildren, s)`。

### 最优解 O(n·m) — DFN序+01背包

**核心洞察：** DFN序上，若跳过节点i，则必须跳过它的整棵子树（不能选后代不选祖先）。`dp[i][j]`=DFN从i到末尾，选j个节点形成"有效结构"（挂在假想根下连通无断）的最大和。

转移：①跳过i→`dp[i+sz[i]][j]`（跳过整个子树）；②选i→`val[i]+dp[i+1][j-1]`。

最终答案：`nums[0] + dp[2][m]`（0号虚拟节点在DFN=1，必然选）。

**坑点：** 这是树上01背包的最优解法，理解"有效结构"定义是关键。

**代码（最优解）：**
```cpp
int dfs(int u) {
    int i = ++dfnCnt; val[i] = nums[u]; sz[i] = 1;
    for (int ei = head[u]; ei > 0; ei = nxt[ei])
        sz[i] += dfs(to[ei]);
    return sz[i];
}
int compute() {
    dfs(0); // n+1个节点，DFN 1..n+1
    for (int i = n+1; i >= 2; i--)
        for (int j = 1; j <= m; j++)
            dp[i][j] = max(dp[i + sz[i]][j],           // 不要节点i（跳过整个子树）
                           val[i] + dp[i + 1][j - 1]);  // 要节点i
    return nums[0] + dp[2][m];
}
```

---

## 总结：树型DP笔记

| 题目 | 核心技巧 | 类型 |
|------|---------|------|
| 到达首都油耗 | 后序DFS + size/cost累积 | 树型DP |
| 相邻不同最长路径 | Info合并 + 最长/次长链 | 树型DP |
| 移除子树高度 | DFN序 + 前后缀max | DFN技巧 |
| 删边最小分数 | DFN序 + XOR + 嵌套判断 | DFN技巧 |
| 选课（最优解） | DFN序 + 01背包转换 O(nm) | 树上背包 |
