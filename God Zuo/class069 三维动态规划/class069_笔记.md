# class069 从递归入手三维动态规划 笔记

> 视频：算法讲解069【必备】从递归入手三维动态规划

---

## 题目1：一和零（多维费用背包）

### 题面
给定二进制字符串数组 strs 和两个整数 m、n。选出最大的子集，使得子集中**最多**有 m 个 0 和 n 个 1。每个字符串由 '0' 和 '1' 组成。

- LeetCode 474: https://leetcode.cn/problems/ones-and-zeroes/

### 核心思路
**三维 DP / 多维费用 0-1 背包**，每个字符串要或不要：
- `dp[i][z][o]`：从 i 开始往后自由选择，零不超过 z、一不超过 o，最多选几个字符串
- 不要当前：`dp[i+1][z][o]`
- 要当前（需 zeros ≤ z 且 ones ≤ o）：`1 + dp[i+1][z-zeros][o-ones]`
- **三维表中每层只依赖上一层**，层之间无依赖 → 从上往下填
- 空间压缩：二维数组 `dp[z][o]`，z 和 o 都**从大到小**更新（因为依赖上一层的 z-zeros, o-ones）

### 坑点
- 空间压缩时 z 和 o 都要从大到小遍历，否则会读到本层刚更新的值
- 每个字符串的 zeros/ones 通过 `zerosAndOnes()` 统计到全局变量

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int zeros, ones;

    // 统计一个字符串中0和1的数量
    void zerosAndOnes(const string& str) {
        zeros = 0;
        ones = 0;
        for (char c : str) {
            if (c == '0') {
                zeros++;
            } else {
                ones++;
            }
        }
    }

    // 递归尝试
    int f1(vector<string>& strs, int i, int z, int o) {
        if (i == (int)strs.size()) {
            return 0;
        }
        int p1 = f1(strs, i + 1, z, o);
        int p2 = 0;
        zerosAndOnes(strs[i]);
        if (zeros <= z && ones <= o) {
            p2 = 1 + f1(strs, i + 1, z - zeros, o - ones);
        }
        return max(p1, p2);
    }

    // 记忆化搜索
    int findMaxForm2(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        return f2(strs, 0, m, n, dp);
    }

    int f2(vector<string>& strs, int i, int z, int o, vector<vector<vector<int>>>& dp) {
        if (i == (int)strs.size()) {
            return 0;
        }
        if (dp[i][z][o] != -1) {
            return dp[i][z][o];
        }
        int p1 = f2(strs, i + 1, z, o, dp);
        int p2 = 0;
        zerosAndOnes(strs[i]);
        if (zeros <= z && ones <= o) {
            p2 = 1 + f2(strs, i + 1, z - zeros, o - ones, dp);
        }
        int ans = max(p1, p2);
        dp[i][z][o] = ans;
        return ans;
    }

    // 三维动态规划
    int findMaxForm3(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        for (int i = len - 1; i >= 0; i--) {
            zerosAndOnes(strs[i]);
            for (int z = 0; z <= m; z++) {
                for (int o = 0; o <= n; o++) {
                    int p1 = dp[i + 1][z][o];
                    int p2 = 0;
                    if (zeros <= z && ones <= o) {
                        p2 = 1 + dp[i + 1][z - zeros][o - ones];
                    }
                    dp[i][z][o] = max(p1, p2);
                }
            }
        }
        return dp[0][m][n];
    }

    // 空间压缩（LeetCode 提交用）
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (const string& s : strs) {
            zerosAndOnes(s);
            for (int z = m; z >= zeros; z--) {
                for (int o = n; o >= ones; o--) {
                    dp[z][o] = max(dp[z][o], 1 + dp[z - zeros][o - ones]);
                }
            }
        }
        return dp[m][n];
    }
};
```

---

## 题目2：盈利计划（多维费用背包）

### 题面
n 名员工，第 i 项工作消耗 group[i] 人、产生 profit[i] 利润。员工不能同时参与多项工作。求选出一些工作使得**员工总数 ≤ n** 且**利润 ≥ minProfit** 的方案数。答案取模 1000000007。

- LeetCode 879: https://leetcode.cn/problems/profitable-schemes/

### 核心思路
**三维 DP / 多维费用 0-1 背包**，利润维度做特殊处理：
- `dp[i][r][s]`：从第 i 号工作开始，员工额度 r、还需利润 s 达标，有多少种方案
- base case：
  - r ≤ 0 且 s ≤ 0 → 1（已达标）
  - i 越界且 s ≤ 0 → 1
  - 否则 → 0
- 转移：不要当前 + 要当前（人够的前提下），和题目 1 一样
- **关键优化**：利润要求到了负数等同于 0（`max(0, s-profit[i])`），防止 DP 表下标越界
- 空间压缩：二维 dp[r][s]，r 从大到小、s 从大到小更新

### 坑点
- `max(0, s - profit[i])` 是灵魂操作：利润达标后多出来的利润没区别，统一压到 0
- 初始 `dp[r][0] = 1`：利润已达标的时候方案数为 1

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int MOD = 1000000007;

    // 递归尝试
    int f1(vector<int>& g, vector<int>& p, int i, int r, int s) {
        if (r <= 0) {
            return s <= 0 ? 1 : 0;
        }
        if (i == (int)g.size()) {
            return s <= 0 ? 1 : 0;
        }
        int p1 = f1(g, p, i + 1, r, s);
        int p2 = 0;
        if (g[i] <= r) {
            p2 = f1(g, p, i + 1, r - g[i], s - p[i]);
        }
        return p1 + p2;
    }

    // 记忆化搜索
    int profitableSchemes2(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n + 1, vector<int>(minProfit + 1, -1)));
        return f2(group, profit, 0, n, minProfit, dp);
    }

    int f2(vector<int>& g, vector<int>& p, int i, int r, int s, vector<vector<vector<int>>>& dp) {
        if (r <= 0) {
            return s == 0 ? 1 : 0;
        }
        if (i == (int)g.size()) {
            return s == 0 ? 1 : 0;
        }
        if (dp[i][r][s] != -1) {
            return dp[i][r][s];
        }
        int p1 = f2(g, p, i + 1, r, s, dp);
        int p2 = 0;
        if (g[i] <= r) {
            p2 = f2(g, p, i + 1, r - g[i], max(0, s - p[i]), dp);
        }
        int ans = (p1 + p2) % MOD;
        dp[i][r][s] = ans;
        return ans;
    }

    // 空间压缩版动态规划（LeetCode 提交用）
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
        for (int r = 0; r <= n; r++) {
            dp[r][0] = 1;
        }
        int m = group.size();
        for (int i = m - 1; i >= 0; i--) {
            for (int r = n; r >= 0; r--) {
                for (int s = minProfit; s >= 0; s--) {
                    int p1 = dp[r][s];
                    int p2 = group[i] <= r ? dp[r - group[i]][max(0, s - profit[i])] : 0;
                    dp[r][s] = (p1 + p2) % MOD;
                }
            }
        }
        return dp[n][minProfit];
    }
};
```

---

## 题目3：骑士在棋盘上的概率

### 题面
n×n 棋盘，骑士从 (row, col) 出发走 k 步，每步等概率走 8 个"马走日"方向之一。一旦出棋盘就死亡。求 k 步后仍在棋盘上的概率。

- LeetCode 688: https://leetcode.cn/problems/knight-probability-in-chessboard/

### 核心思路
**三维 DP（记忆化搜索即可，返回 double 类型）**：
- `dp[i][j][k]`：从 (i,j) 出发还剩 k 步，最后在棋盘上的概率
- 越界 → 0
- k=0 → 1（不用走且还在棋盘内）
- 8 个方向等概率各 1/8 → 返回 8 个方向的概率之和除以 8
- K 依赖 K-1 层，三维表按层从低到高填

### 坑点
- 返回 double，DP 表用 double 或 -1 标记未计算
- 空间压缩可以用两张二维表交替（K 层只用 K-1 层），但记忆化搜索已足够快

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 记忆化搜索
    // 从(i,j)出发还有k步要走，返回最后在棋盘上的概率
    double f(int n, int i, int j, int k, vector<vector<vector<double>>>& dp) {
        if (i < 0 || i >= n || j < 0 || j >= n) {
            return 0;
        }
        if (dp[i][j][k] != -1) {
            return dp[i][j][k];
        }
        double ans = 0;
        if (k == 0) {
            ans = 1;
        } else {
            ans += (f(n, i - 2, j + 1, k - 1, dp) / 8);
            ans += (f(n, i - 1, j + 2, k - 1, dp) / 8);
            ans += (f(n, i + 1, j + 2, k - 1, dp) / 8);
            ans += (f(n, i + 2, j + 1, k - 1, dp) / 8);
            ans += (f(n, i + 2, j - 1, k - 1, dp) / 8);
            ans += (f(n, i + 1, j - 2, k - 1, dp) / 8);
            ans += (f(n, i - 1, j - 2, k - 1, dp) / 8);
            ans += (f(n, i - 2, j - 1, k - 1, dp) / 8);
        }
        dp[i][j][k] = ans;
        return ans;
    }

    double knightProbability(int n, int k, int row, int column) {
        vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(k + 1, -1)));
        return f(n, row, column, k, dp);
    }
};
```

---

## 题目4：矩阵中和能被 K 整除的路径

### 题面
n×m 矩阵，从 (0,0) 出发只能向右或向下走到 (n-1,m-1)。求路径和能被 k 整除的路径数，结果取模 1000000007。

- LeetCode 2435: https://leetcode.cn/problems/paths-in-matrix-whose-sum-is-divisible-by-k/

### 核心思路
**三维 DP，余数做第三维**：
- `dp[i][j][r]`：从 (i,j) 出发到右下角，路径和模 k 余 r 的路径数
- 当前格值模 k = `cur = grid[i][j] % k`
- 后续需要凑的余数：`need = (k + r - cur) % k`（核心公式）
- base case：右下角 `dp[n-1][m-1][grid[n-1][m-1]%k] = 1`
- 转移：`dp[i][j][r] = dp[i+1][j][need] + dp[i][j+1][need]`
- 从右下往左上填：先填最后一行/列，再填中间

### 坑点
- `need = (k + r - cur) % k` 这个公式是关键，保证非负
- 三维 DP 规模是 n×m×k，每个格子 O(1) 转移（没有枚举）

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int MOD = 1000000007;

    // 记忆化搜索
    int numberOfPaths2(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, -1)));
        return f2(grid, n, m, k, 0, 0, 0, dp);
    }

    int f2(vector<vector<int>>& grid, int n, int m, int k, int i, int j, int r, vector<vector<vector<int>>>& dp) {
        if (i == n - 1 && j == m - 1) {
            return grid[i][j] % k == r ? 1 : 0;
        }
        if (dp[i][j][r] != -1) {
            return dp[i][j][r];
        }
        int need = (k + r - grid[i][j] % k) % k;
        int ans = 0;
        if (i + 1 < n) {
            ans = f2(grid, n, m, k, i + 1, j, need, dp);
        }
        if (j + 1 < m) {
            ans = (ans + f2(grid, n, m, k, i, j + 1, need, dp)) % MOD;
        }
        dp[i][j][r] = ans;
        return ans;
    }

    // 动态规划（LeetCode 提交用）
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, 0)));
        dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;
        // 最后一列
        for (int i = n - 2; i >= 0; i--) {
            for (int r = 0; r < k; r++) {
                dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
            }
        }
        // 最后一行
        for (int j = m - 2; j >= 0; j--) {
            for (int r = 0; r < k; r++) {
                dp[n - 1][j][r] = dp[n - 1][j + 1][(k + r - grid[n - 1][j] % k) % k];
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            for (int j = m - 2; j >= 0; j--) {
                for (int r = 0; r < k; r++) {
                    int need = (k + r - grid[i][j] % k) % k;
                    dp[i][j][r] = dp[i + 1][j][need];
                    dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % MOD;
                }
            }
        }
        return dp[0][0][0];
    }
};
```

---

## 题目5：扰乱字符串

### 题面
给定等长字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。扰乱规则：可将字符串任意分割成两个非空子串，每层可选择交换或不交换左右两部分，递归进行。

- LeetCode 87: https://leetcode.cn/problems/scramble-string/

### 核心思路
**三维 DP + 区间 DP 思想**，O(n⁴)（n³ 格子 × n 枚举）：
- `dp[l1][l2][len]`：s1 从 l1 开始、s2 从 l2 开始，长度均为 len，是否互为扰乱串
- 初始：`len=1` 时 `dp[l1][l2][1] = s1[l1]==s2[l2]`
- 转移——枚举分割点 k（1 ≤ k < len）：
  - **不交错**：`dp[l1][l2][k] && dp[l1+k][l2+k][len-k]`
  - **交错**：`dp[l1][l2+len-k][k] && dp[l1+k][l2][len-k]`
  - 任一种成立即 true
- 枚举 k 有 O(n) 开销，无法优化
- 从 len=2 往上递推，注意边界：l1 ≤ n-len, l2 ≤ n-len

### 坑点
- 字符种类和数量都相同 ≠ 一定是扰乱串（反例：abcd vs cadb）
- len 从 2 到 n 递增，l1/l2 不能越界（`l1 <= n-len`）
- 记忆化搜索用 int 三态（0=未算, -1=false, 1=true），因为 bool 无法区分"没算过"

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 记忆化搜索
    // dp[l1][l2][len] : 0 -> 没展开过, -1 -> false, 1 -> true
    bool isScramble3(string s1, string s2) {
        int n = s1.length();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n + 1, 0)));
        return f3(s1, s2, 0, 0, n, dp);
    }

    bool f3(const string& s1, const string& s2, int l1, int l2, int len, vector<vector<vector<int>>>& dp) {
        if (len == 1) {
            return s1[l1] == s2[l2];
        }
        if (dp[l1][l2][len] != 0) {
            return dp[l1][l2][len] == 1;
        }
        bool ans = false;
        // 不交错
        for (int k = 1; k < len; k++) {
            if (f3(s1, s2, l1, l2, k, dp) && f3(s1, s2, l1 + k, l2 + k, len - k, dp)) {
                ans = true;
                break;
            }
        }
        // 交错
        if (!ans) {
            for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++) {
                if (f3(s1, s2, l1, j, k, dp) && f3(s1, s2, i, l2, len - k, dp)) {
                    ans = true;
                    break;
                }
            }
        }
        dp[l1][l2][len] = ans ? 1 : -1;
        return ans;
    }

    // 严格位置依赖的动态规划（LeetCode 提交用）
    bool isScramble(string s1, string s2) {
        int n = s1.length();
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));
        // len = 1
        for (int l1 = 0; l1 < n; l1++) {
            for (int l2 = 0; l2 < n; l2++) {
                dp[l1][l2][1] = s1[l1] == s2[l2];
            }
        }
        for (int len = 2; len <= n; len++) {
            for (int l1 = 0; l1 <= n - len; l1++) {
                for (int l2 = 0; l2 <= n - len; l2++) {
                    for (int k = 1; k < len; k++) {
                        if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k]) {
                            dp[l1][l2][len] = true;
                            break;
                        }
                    }
                    if (!dp[l1][l2][len]) {
                        for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++) {
                            if (dp[l1][j][k] && dp[i][l2][len - k]) {
                                dp[l1][l2][len] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};
```
