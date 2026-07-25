# class078 树型DP（上）

> B站视频：[算法讲解078](https://www.bilibili.com/video/BV1ae411f7SF/)
> 前置知识：class037（二叉树递归）、class067/068（二维DP）

---

## 01 最大BST子树 — LeetCode 333

**题面：** 二叉树，找节点数最多的二叉搜索子树，返回其大小。

**核心思路：** 树型DP套路——每节点返回Info（`maxVal, minVal, isBst, maxBstSize`）。整合：左子树+右子树都BST且左max<x.val<右min → 当前子树是BST。空节点返回`(LLONG_MIN, LLONG_MAX, true, 0)`。

**坑点：** 空节点的max/min值为"无限小/无限大"，让所有正常节点都满足BST条件。节点值可能等于INT_MIN/MAX，所以用`long long`。

**代码：**
```cpp
struct Info { long long maxVal, minVal; bool isBst; int maxBstSize; };
Info f(TreeNode* x) {
    if (!x) return Info(LLONG_MIN, LLONG_MAX, true, 0);
    Info l = f(x->left), r = f(x->right);
    long long mx = max((long long)x->val, max(l.maxVal, r.maxVal));
    long long mn = min((long long)x->val, min(l.minVal, r.minVal));
    bool bst = l.isBst && r.isBst && l.maxVal < x->val && x->val < r.minVal;
    int sz = bst ? l.maxBstSize + r.maxBstSize + 1
                 : max(l.maxBstSize, r.maxBstSize);
    return Info(mx, mn, bst, sz);
}
```

---

## 02 二叉搜索子树的最大键值和 — LeetCode 1373

**题面：** 同01，但返回最大键值和（sum）而非节点数。

**核心思路：** Info多加一个`sum`字段。整合时：若当前子树是BST，`maxBstSum = max(左max, 右max, 当前sum)`。

**坑点：** 节点值范围在`[-40000, 40000]`，INT_MIN/MAX够用，可以不用long long。

**代码：**
```cpp
struct Info { int maxVal, minVal, sum, maxBstSum; bool isBst; };
Info f(TreeNode* x) {
    if (!x) return Info(INT_MIN, INT_MAX, 0, 0, true);
    Info l = f(x->left), r = f(x->right);
    int mx = max(x->val, max(l.maxVal, r.maxVal));
    int mn = min(x->val, min(l.minVal, r.minVal));
    int sum = l.sum + r.sum + x->val;
    bool bst = l.isBst && r.isBst && l.maxVal < x->val && x->val < r.minVal;
    int mbs = max(l.maxBstSum, r.maxBstSum);
    if (bst) mbs = max(mbs, sum);
    return Info(mx, mn, sum, mbs, bst);
}
```

---

## 03 二叉树的直径 — LeetCode 543

**题面：** 二叉树上任意两节点间最长路径的边数。

**核心思路：** Info = `(diameter, height)`。`height = max(左高, 右高)+1`。`diameter = max(左直径, 右直径, 左高+右高)`。

**坑点：** 直径不一定过根节点。

**代码：**
```cpp
struct Info { int diameter, height; };
Info f(TreeNode* x) {
    if (!x) return Info(0, 0);
    Info l = f(x->left), r = f(x->right);
    int h = max(l.height, r.height) + 1;
    int d = max({l.diameter, r.diameter, l.height + r.height});
    return Info(d, h);
}
```

---

## 04 在二叉树中分配硬币 — LeetCode 979

**题面：** n个节点的树共有n枚硬币（分布在节点上）。一次移动将一枚硬币从节点移到相邻节点。求让每个节点恰好1枚硬币的最少移动次数。

**核心思路：** Info = `(cnt, sum, move)`。子树的节点数vs硬币数的差值 = 需要进出该子树的硬币数。`moves = 左move+右move + abs(左cnt-左sum) + abs(右cnt-右sum)`。

**坑点：** 核心洞察——每个子树"缺多少"或"多多少"硬币，都要通过父边运输，贡献=|cnt-sum|步。

**代码：**
```cpp
struct Info { int cnt, sum, move; };
Info f(TreeNode* x) {
    if (!x) return Info(0, 0, 0);
    Info l = f(x->left), r = f(x->right);
    int cnts = l.cnt + r.cnt + 1;
    int sums = l.sum + r.sum + x->val;
    int moves = l.move + r.move + abs(l.cnt-l.sum) + abs(r.cnt-r.sum);
    return Info(cnts, sums, moves);
}
```

---

## 05 没有上司的舞会 — 洛谷 P1352（LeetCode 337 打家劫舍 III）

**题面：** 树形组织结构，每个职员有快乐值。若上司参加，其直接下属就不参加。求最大总快乐值。

**核心思路：** `no[u]` = u不来时子树最大快乐值，`yes[u]` = u来时最大。递推：`no[u] = Σmax(no[v], yes[v])`，`yes[u] = happy[u] + Σno[v]`。最终答案=`max(no[root], yes[root])`。

**坑点：** 用链式前向星建图；先找根节点（`boss`标记）。

**代码：**
```cpp
void f(int u) {
    no[u] = 0; yes[u] = nums[u];
    for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
        int v = to[ei]; f(v);
        no[u] += max(no[v], yes[v]);
        yes[u] += no[v];
    }
}
```

---

## 06 监控二叉树 — LeetCode 968

**题面：** 节点上装摄像头可监视自身、父、子。求覆盖整棵树的最少摄像头数。

**核心思路：** 递归（假设x上方一定有父亲！）。返回值含义：
- `0`：x无覆盖，但下方都覆盖了
- `1`：x有覆盖（无摄像头），下方都覆盖
- `2`：x有覆盖（有摄像头），下方都覆盖

转移：①左或右=0 → 必须放摄像头，返回2；②左=1且右=1 → 指望父亲覆盖，返回0；③否则返回1。最后若根节点返回0，再+1。

**坑点：** 假设"x上方一定有父亲"让空节点返回1（被覆盖状态）；根节点无父亲，需最后补判。

**代码：**
```cpp
int f(TreeNode* x) {
    if (!x) return 1;
    int l = f(x->left), r = f(x->right);
    if (l == 0 || r == 0) { ans++; return 2; }
    if (l == 1 && r == 1) return 0;
    return 1;
}
int minCameraCover(TreeNode* root) {
    ans = 0;
    if (f(root) == 0) ans++;
    return ans;
}
```

---

## 07 路径总和 III — LeetCode 437

**题面：** 二叉树，求从任意节点向下（只能父到子）的路径中，和等于targetSum的路径数。

**核心思路：** "前缀和+HashMap"在树上的应用。DFS时维护"根到当前节点的前缀和"以及前缀和出现次数的哈希表。以当前节点作为路径结尾，`ans += presum[sum - target]`。回溯时恢复哈希表（`presum[sum]--`）。

**坑点：** 初始化`presum[0] = 1`（路径从根开始的情况）；回溯时撤销计数。

**代码：**
```cpp
void f(TreeNode* x, int target, long long sum) {
    if (!x) return;
    sum += x->val;
    ans += presum[sum - target];
    presum[sum]++;
    f(x->left, target, sum);
    f(x->right, target, sum);
    presum[sum]--; // 回溯
}
```
