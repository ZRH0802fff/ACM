# class067 从递归入手二维动态规划

> 前置：讲解066（一维DP入门）。本节承接「从递归到 DP」的主线，讲清楚**二维**动态规划怎么从递归改出来，以及**二维空间压缩**技巧，并说明**哪些递归不适合改成 DP**。
> 下节课（068）直接从 DP 定义入手见识更多二维 DP 题目。

## 核心方法论

1. **几维 DP 由「可变参数个数」决定**：尝试函数有 1 个可变参数能完全决定返回值 → 1 维 DP 表；2 个可变参数 → 2 维 DP 表。多维同理。
2. **DP 表大小 = 每个可变参数可能性数量的乘积**；**时间复杂度 = 表大小 × 每个格子的枚举代价**。
3. 改 DP 的标准四步（与一维完全一样）：写出尝试递归 → 记忆化搜索（顶到底）→ 严格位置依赖（底到顶）→ 空间/时间优化。
4. **二维 DP 依赖关系要画图**：把格子之间的依赖关系画出来，建立空间感，再从简单格子填到复杂格子。
5. **能改 DP 的递归，统一特征是「可变参数类型简单（不比 int 复杂）」**——因为这样才能用一张大小有限的表存下所有状态，且参数能完全代表之前决策对后续的影响。**带路径的递归**（可变参数复杂，如要记录「哪些格子用过了」）不适合/没必要改成 DP，题目 2 就是典型。
6. **递归尽量从「长度/范围」而非「下标」定义**：长度最短是 0，天然避免越界和边界讨论（题目 3、4 都这么做）。

---

## 题目1：最小路径和

- **测试链接**：https://leetcode.cn/problems/minimum-path-sum/
- **题面**：给定 `m×n` 非负整数网格，从左上角走到右下角，每次只能**向右或向下**，求路径数字和最小。`m, n ≤ 200`。
- **核心思路**：
  - 尝试：`f(i,j)` = 从 `(0,0)` 到 `(i,j)` 的最小路径和。它只可能从上面 `(i-1,j)` 或左边 `(i,j-1)` 走过来，所以 `f(i,j) = grid[i][j] + min(上, 左)`；`(0,0)` 是边界返回 `grid[0][0]`。
  - 严格位置依赖：`dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]`，先填第 0 行、第 0 列（只有一种走法），再按行填充。
  - **空间压缩**：二维 → 一维。`dp[j]` 滚动表示「当前这一行的 `dp[i][j]`」。因为 `dp[i][j]` 只依赖上一行的 `dp[i-1][j]`（即旧 `dp[j]`）和本行的 `dp[i][j-1]`（即新 `dp[j-1]`），所以一行一维数组即可滚动。
- **坑点**：
  - 第 0 行、第 0 列要先单独初始化（不能从上方/左方来，只有一种前缀和走法）。
  - 空间压缩时 `dp[0] += grid[i][0]` 要放在每行的列循环**之前**更新，因为它只依赖上一行的 `dp[0]`。
  - 上下两个方向不可达时用 `INT_MAX` 兜底（递归版）。
- **代码**（空间压缩版，即 Java 的 `minPathSum4`）：

```cpp
// dp 是一维数组，长度 m（m <= 200）
int minPathSum(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    int dp[MAXM];
    dp[0] = grid[0][0];
    for (int j = 1; j < m; j++) dp[j] = dp[j - 1] + grid[0][j];   // 第0行
    for (int i = 1; i < n; i++) {
        dp[0] += grid[i][0];                                       // 每行第0列
        for (int j = 1; j < m; j++) {
            dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
        }
    }
    return dp[m - 1];
}
```

---

## 题目2：单词搜索（无法改成动态规划）

- **测试链接**：https://leetcode.cn/problems/word-search/
- **题面**：给定 `m×n` 字符网格和单词 `word`，判断 `word` 能否通过相邻（上下左右）单元格、不重复使用同一格地走出来。`m, n ≤ 6`，`word.length ≤ 15`。
- **核心思路**：经典回溯。`f(i, j, k)` 表示从 `(i,j)` 出发、当前匹配到 `word[k]`，能否走出 `word[k..]`。四个方向 DFS，用「改格子字符」标记已访问，回溯时恢复。
- **坑点**：
  - 这是**带路径的递归**：可变参数要包含「哪些格子用过了」（一条路径信息），类型复杂，**改不成、也没必要改成 DP**。这是本节课讲「不适合改 DP」的例题。
  - 标记已访问的方式是「就地改写 + 恢复」，比额外 `visited` 数组省空间。
  - 边界判断（越界 + 字符不匹配）要在递归入口统一处理，逻辑更清晰。
- **代码**：

```cpp
bool exist(vector<vector<char>>& board, string word) {
    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[0].size(); j++)
            if (f(board, i, j, word, 0)) return true;
    return false;
}

// 从(i,j)出发，来到word[k]，请问后续能不能把word[k...]走出来
bool f(vector<vector<char>>& b, int i, int j, string& w, int k) {
    if (k == w.length()) return true;
    if (i < 0 || i == b.size() || j < 0 || j == b[0].size() || b[i][j] != w[k]) return false;
    char tmp = b[i][j];
    b[i][j] = 0;   // 标记已用
    bool ans = f(b, i - 1, j, w, k + 1) || f(b, i + 1, j, w, k + 1)
            || f(b, i, j - 1, w, k + 1) || f(b, i, j + 1, w, k + 1);
    b[i][j] = tmp; // 恢复
    return ans;
}
```

---

## 题目3：最长公共子序列

- **测试链接**：https://leetcode.cn/problems/longest-common-subsequence/
- **题面**：给定两个字符串 `text1`、`text2`，求最长公共子序列长度。`text1/text2 长度 ≤ 1000`。
- **核心思路**：
  - 用**长度**定义尝试：`f2(len1, len2)` = `s1[前 len1]` 与 `s2[前 len2]` 的 LCS 长度，`len1/len2 == 0` 时返回 0（自然边界，无下标越界烦恼）。
  - 转移：看**最后一个字符** `s1[len1-1]` 与 `s2[len2-1]`：
    - 相等 → `f2(len1-1, len2-1) + 1`（两个都删掉，配对）。
    - 不等 → `max(f2(len1-1, len2), f2(len1, len2-1))`（至少删掉一个）。
  - 严格位置依赖：`dp[len1][len2]`，按 len1、len2 双循环递增填充。
  - **空间压缩**：`dp[len2]` 一维数组，用 `leftUp` 保存左上角 `dp[len1-1][len2-1]`（斜对角），`backup` 在覆盖前暂存 `dp[len2]`（上一行的值）。
- **坑点**：
  - 转移只依赖「左、上、左上」三个方向，空间压缩时必须额外用一个变量 `leftUp` 记斜对角（单靠一维 `dp` 会丢失它）。
  - 为了让一维数组更短，先让 `s1` 取较长串、`s2` 取较短串，压缩到较短串的长度上。
- **代码**（空间压缩版，即 Java 的 `longestCommonSubsequence5`）：

```cpp
// 让 s1 是较长串、s2 是较短串；dp 是长度 m+1 的一维数组
int longestCommonSubsequence(string str1, string str2) {
    string& s1 = str1, &s2 = str2;
    if (str1.length() < str2.length()) { s1 = str2; s2 = str1; }
    int n = s1.length(), m = s2.length();
    int dp[MAXM];
    memset(dp, 0, sizeof(dp));
    for (int len1 = 1; len1 <= n; len1++) {
        int leftUp = 0, backup;
        for (int len2 = 1; len2 <= m; len2++) {
            backup = dp[len2];
            if (s1[len1 - 1] == s2[len2 - 1]) dp[len2] = 1 + leftUp;
            else dp[len2] = max(dp[len2], dp[len2 - 1]);
            leftUp = backup;
        }
    }
    return dp[m];
}
```

---

## 题目4：最长回文子序列

- **测试链接**：https://leetcode.cn/problems/longest-palindromic-subsequence/
- **题面**：给定字符串 `s`，求最长回文子序列长度。`s.length ≤ 1000`。
- **核心思路**：区间 DP 思路（后续 076/077 会专门讲区间 DP）。
  - 尝试：`f(l, r)` = `s[l..r]` 的最长回文子序列长度（`l <= r`）。
    - `l == r` → 1；`l + 1 == r` → `s[l]==s[r] ? 2 : 1`。
    - `s[l] == s[r]` → `2 + f(l+1, r-1)`（两头配对）。
    - 否则 → `max(f(l+1, r), f(l, r-1))`（至少放弃一头）。
  - 严格位置依赖：`dp[l][r]` 依赖 `dp[l+1][r-1]`（左下）、`dp[l+1][r]`（下）、`dp[l][r-1]`（左），所以 `l` 从大到小、`r` 从小到大填充。
  - **空间压缩**：一维 `dp[r]`，`l` 倒序扫描，用 `leftDown` 记左下角 `dp[l+1][r-1]`。
- **坑点**：
  - 依赖方向是「下、左、左下」，和 LCS 的「上、左、左上」不同，空间压缩的斜对角变量命名和更新顺序要对上（这里是 `leftDown`）。
  - `l+1 == r` 的相邻两个字符要单独初始化，不能走 `l+1 > r-1` 的空区间。
  - 本题也可转化为「s 与 reverse(s) 的 LCS」，但这里用区间 DP 讲述。
- **代码**（空间压缩版，即 Java 的 `longestPalindromeSubseq4`）：

```cpp
// dp 是长度 n 的一维数组
int longestPalindromeSubseq(string s) {
    int n = s.length();
    int dp[MAXN];
    for (int l = n - 1, leftDown = 0, backup; l >= 0; l--) {
        dp[l] = 1;
        if (l + 1 < n) {
            leftDown = dp[l + 1];
            dp[l + 1] = (s[l] == s[l + 1] ? 2 : 1);
        }
        for (int r = l + 2; r < n; r++) {
            backup = dp[r];
            if (s[l] == s[r]) dp[r] = 2 + leftDown;
            else dp[r] = max(dp[r], dp[r - 1]);
            leftDown = backup;
        }
    }
    return dp[n - 1];
}
```

---

## 题目5：节点数为 n 高度不大于 m 的二叉树个数

- **测试链接**：https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea（牛客）
- **题面**：给定 `n` 个节点，求「节点数为 `n`、高度不超过 `m`」的不同结构二叉树个数，答案对 `10^9+7` 取模。`n, m ≤ 50`。
- **核心思路**：以**根节点**划分子问题。
  - `f(n, m)` = 节点数为 `n`、高度 ≤ `m` 的结构数。边界：`n == 0`（空树）返回 1；`m == 0`（高度上限为 0，但还有节点）返回 0。
  - 根占 1 个节点，枚举左子树节点数 `k`（`0..n-1`），右子树就是 `n-k-1` 个；两棵子树高度都 ≤ `m-1`，所以 `f(n,m) = Σ_k f(k, m-1) * f(n-k-1, m-1)`。
  - 严格位置依赖：`dp[i][j]`，先初始化 `dp[0][j] = 1`（空树），再按 i、j 递增填充，内部枚举 k。
  - **空间压缩**：压缩 i 维到一维 `dp[i]`。关键依赖在「前一列（高度 j-1）」，所以**外层枚举 j（高度）**，内层 `i` 要**从大到小**枚举，保证读到的 `dp[k]、dp[i-k-1]`（都 < i）还是上一个高度 j-1 的值。
- **坑点**：
  - `n==0` 空树算 1 种（这是递归/DP 的种子），`m==0` 且 `n>0` 算 0 种。
  - 乘法会溢出，`long long` + 每步 `% MOD`。
  - 空间压缩必须「先枚举高度 j，再逆序枚举 i」，顺序错了会读到当前列已更新的值导致错误。
- **代码**（空间压缩版，即 Java 的 `compute3`）：

```cpp
// 严格位置依赖的动态规划
long long dp2[MAXN][MAXN];

int compute2(int n, int m) {
	for (int j = 0; j <= m; j++) {
		dp2[0][j] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp2[i][j] = 0;
			for (int k = 0; k < i; k++) {
				// 一共i个节点，头节点已经占用了1个名额
				// 如果左树占用k个，那么右树就占用i-k-1个
				dp2[i][j] = (dp2[i][j] + dp2[k][j - 1] * dp2[i - k - 1][j - 1] % MOD) % MOD;
			}
		}
	}
	return (int) dp2[n][m];
}
```

---

## 题目6：矩阵中的最长递增路径

- **测试链接**：https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/
- **题面**：给定 `m×n` 整数矩阵，求最长严格递增路径长度，可上下左右移动，不能越界。`m, n ≤ 200`。
- **核心思路**：记忆化 DFS（每个格子是图上的点，边从小的指向大的，形成 DAG，无环）。
  - `f(i, j)` = 从 `(i,j)` 出发的最长递增路径长度。四个方向里，凡是 `grid[i][j] < grid[邻]` 的都可以走，取最大值 `+1`。
  - 因为严格递增，递归不会回头，天然无环，记忆化 `dp[i][j]` 缓存即可（`dp[i][j] != 0` 表示已算过，因为答案至少为 1）。
  - 每个格子作为起点取最大值。
- **坑点**：
  - 只有 `grid[i][j] < 邻居` 才递归（严格递增，等于不成立），这是剪枝和无环的保证。
  - 用 `0` 作为「未计算」标记是安全的，因为路径长度至少为 1。
  - 本题没有严格位置依赖的「按行列填表」版本，因为依赖方向由值的大小决定（非固定方向），直接用记忆化搜索最自然。
- **代码**（记忆化搜索版）：

```cpp
// dp 是 n x m 的全局二维数组，0 表示未计算
int longestIncreasingPath(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans = max(ans, f(grid, i, j));
    return ans;
}

int f(vector<vector<int>>& grid, int i, int j) {
    if (dp[i][j] != 0) return dp[i][j];
    int next = 0;
    if (i > 0 && grid[i][j] < grid[i-1][j]) next = max(next, f(grid, i-1, j));
    if (i+1 < grid.size() && grid[i][j] < grid[i+1][j]) next = max(next, f(grid, i+1, j));
    if (j > 0 && grid[i][j] < grid[i][j-1]) next = max(next, f(grid, i, j-1));
    if (j+1 < grid[0].size() && grid[i][j] < grid[i][j+1]) next = max(next, f(grid, i, j+1));
    return dp[i][j] = next + 1;
}
```

---

## 本节小结

1. **二维 DP 的本质**：尝试函数有 2 个可变参数。表大小 = 两参数可能性乘积，复杂度 = 表大小 × 每格枚举代价。
2. **依赖关系靠画图**：填表顺序（谁先谁后、依赖上/左/左上还是下/左/左下）一定要画格子图确认，空间压缩时才不会搞错斜对角变量。
3. **空间压缩的套路**：二维压缩到一维，额外用一个变量保存「斜对角」值（LCS 的 `leftUp`、回文子序列的 `leftDown`），覆盖前用 `backup` 暂存。
4. **不是所有递归都该改 DP**：带路径的递归（可变参数类型复杂）改不动也没必要，单词搜索就是典型例子。
5. **从长度/范围定义尝试**：避免下标越界的边界讨论（LCS、回文子序列都受益）。
