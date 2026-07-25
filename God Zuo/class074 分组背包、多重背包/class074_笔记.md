# class074 背包DP — 分组背包、完全背包

> B站视频：[算法讲解074](https://www.bilibili.com/video/BV1UM411f7YL/)
> 前置知识：class067、class068、class073

---

## 01 分组背包模板

**题面：** 物品分若干组，每组最多选一件。每个物品有体积和价值，背包容量t，求最大价值。

**核心思路：** `dp[i][j]`=1~i组容量不超过j的最大价值。转移：①不选i组→`dp[i-1][j]`；②选i组内某件k→`dp[i-1][j-cost[k]]+val[k]`。预处理：按组号排序物品。空间压缩：一维数组**从右往左**更新。

**坑点：** `dp[j]`需先继承上一行（天然继承不用写），然后组内每件物品都尝试，注意取max而非直接赋值。

**代码：**
```cpp
// 空间压缩版
for (int s = 1, e = 2; s <= n;) {
    while (e <= n && arr[e][2] == arr[s][2]) e++;
    // 当前组物品从 s 到 e-1
    for (int j = t; j >= 0; j--) {
        for (int k = s; k < e; k++) {
            if (j >= arr[k][0])
                dp[j] = max(dp[j], dp[j - arr[k][0]] + arr[k][1]);
        }
    }
    s = e; e++;
}
return dp[t];
```

---

## 02 栈中取K个硬币的最大价值 — LeetCode 2218

**题面：** 桌上n叠硬币（每叠是一个栈，只能从顶拿），每次操作取一个栈顶硬币。必须恰好k次操作，求最大总价值。

**核心思路：** 转化为分组背包：每叠是一组，组内**方案**=取前i个硬币(i=0,1,2,...)，消耗=i次操作，收益=前缀和。每组只能选一个方案（一种物品）。`dp[i][j]`=1~i组恰好j次操作的最大价值。背包容量=k。

**坑点：** 前缀和只需算到`min(栈高度, k)`；`dp`的第二维是恰好j次而非不超过j次。

**代码：**
```cpp
int maxValueOfCoins(vector<vector<int>>& piles, int m) {
    int n = piles.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        auto& pile = piles[i - 1];
        int t = min((int)pile.size(), m);
        vector<int> presum(t + 1);
        for (int j = 1; j <= t; j++)
            presum[j] = presum[j - 1] + pile[j - 1];
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j]; // 不选这组
            for (int k = 1; k <= min(j, t); k++)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + presum[k]);
        }
    }
    return dp[n][m];
}
```

---

## 03 完全背包模板 — 洛谷 P1616

**题面：** 背包容量t，n种物品各有体积和价值，每种可以选无限次，求最大价值。

**核心思路：** 与01背包的唯一区别：`dp[i][j]=max(dp[i-1][j], dp[i][j-w]+v)`（停留在第i行而非i-1行）。空间压缩：一维数组**从左往右**更新。

**坑点：** 此题t可达10⁷，必须空间压缩，开二维表会爆内存。循环从`j=cost[i]`开始而非`j=t`。

**代码：**
```cpp
vector<long long> dp(t + 1);
for (int i = 1; i <= n; i++)
    for (int j = cost[i]; j <= t; j++)  // 从左往右
        dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
return dp[t];
```

---

## 04 正则表达式匹配 — LeetCode 10

**题面：** 给字符串s和模式p。`.`匹配任意单字符，`*`让前一个字符出现任意次（含0次）。判断p能否完全匹配s。

**核心思路：** 递归→DP。`f(i,j)`: s[i..]能否被p[j..]匹配。分类：①`j+1`不是`*`→s[i]和p[j]对上且`f(i+1,j+1)`；②`j+1`是`*`→要么用0次（跳过`x*`，`f(i,j+2)`），要么s[i]和p[j]对上且用1次（`f(i+1,j)`，完全背包思想停在j）。DP: `dp[i][j]`依赖右下+同行跳两格→从下往上、从右往左填。

**坑点：** s为空时p可能配得上（如`a*b*c*`全消为0个），base case要处理。

**代码：**
```cpp
class Solution {
public:
    // 暴力递归
    // s[i....]能不能被p[j....]完全匹配出来
    // p[j]这个字符，一定不是'*'
    bool f1(const string& s, const string& p, int i, int j) {
        if (i == (int)s.length()) {
            // s没了
            if (j == (int)p.length()) {
                // 如果p也没了，返回true
                return true;
            } else {
                // p还剩下一些后缀
                // 如果p[j+1]是*，那么p[j..j+1]可以消掉，然后看看p[j+2....]是不是都能消掉
                return j + 1 < (int)p.length() && p[j + 1] == '*' && f1(s, p, i, j + 2);
            }
        } else if (j == (int)p.length()) {
            // s有后缀, p没后缀了
            return false;
        } else {
            // s有后缀, p有后缀
            if (j + 1 == (int)p.length() || p[j + 1] != '*') {
                // 如果p[j+1]不是*，那么当前的字符必须能匹配
                // 同时，后续也必须匹配上
                return (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j + 1);
            } else {
                // 如果p[j+1]是* —— 完全背包思想！
                // 选择1: 当前p[j..j+1]是x*，不让它搞定s[i]，继续 f(i, j+2)
                bool p1 = f1(s, p, i, j + 2);
                // 选择2: 当前p[j..j+1]是x*，如果可以搞定s[i]，继续 f(i+1, j)
                // 如果可以搞定s[i] : (s[i] == p[j] || p[j] == '.')
                bool p2 = (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j);
                return p1 || p2;
            }
        }
    }

    bool isMatch1(string s, string p) {
        return f1(s, p, 0, 0);
    }

    // 记忆化搜索
    // dp[i][j] == 0 没算过, 1 算过true, 2 算过false
    bool isMatch2(string s, string p) {
        int n = s.length(), m = p.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        return f2(s, p, 0, 0, dp);
    }

    bool f2(const string& s, const string& p, int i, int j, vector<vector<int>>& dp) {
        if (dp[i][j] != 0) return dp[i][j] == 1;
        bool ans;
        if (i == (int)s.length()) {
            if (j == (int)p.length()) {
                ans = true;
            } else {
                ans = j + 1 < (int)p.length() && p[j + 1] == '*' && f2(s, p, i, j + 2, dp);
            }
        } else if (j == (int)p.length()) {
            ans = false;
        } else {
            if (j + 1 == (int)p.length() || p[j + 1] != '*') {
                ans = (s[i] == p[j] || p[j] == '.') && f2(s, p, i + 1, j + 1, dp);
            } else {
                ans = f2(s, p, i, j + 2, dp)
                   || ((s[i] == p[j] || p[j] == '.') && f2(s, p, i + 1, j, dp));
            }
        }
        dp[i][j] = ans ? 1 : 2;
        return ans;
    }

    // 严格位置依赖的动态规划
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[n][m] = true;
        // 处理s为空时p的后缀: 只有 x*x*... 模式才能消掉
        for (int j = m - 1; j >= 0; j--) {
            dp[n][j] = j + 1 < m && p[j + 1] == '*' && dp[n][j + 2];
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (j + 1 == m || p[j + 1] != '*') {
                    dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j + 1];
                } else {
                    dp[i][j] = dp[i][j + 2] || ((s[i] == p[j] || p[j] == '.') && dp[i + 1][j]);
                }
            }
        }
        return dp[0][0];
    }
};
```

---

## 05 通配符匹配 — LeetCode 44

**题面：** 类似题目4但`?`匹配任意单字符，`*`匹配任意字符串（不依赖前字符）。比题目4简单。

**核心思路：** `f(i,j)`: ①`p[j]`不是`*`→当前对上且`f(i+1,j+1)`；②`p[j]`是`*`→不匹配`s[i]`(跳过`*`，`f(i,j+1)`)或匹配`s[i]`(停在`*`，`f(i+1,j)`)。完全背包思想一致。

**代码：** 略（与题目4结构类似，更简单）。

---

## 06 购买足量干草的最小花费

**题面：** n个公司各有一种产品，花费c[i]得v[i]千克草，可无限买。必须凑≥H千克，求最小花费。

**核心思路：** 定义翻转：`dp[i][j]`=前i公司**严格j千克**的最小花费（不再求最大价值）。关键扩充：严格等于H可能无解→列扩充到`H+max(v[i])`（覆盖最近整数倍），最后枚举`j∈[H, H+maxV]`取最小`dp[n][j]`。转移：`dp[i][j]=min(dp[i-1][j], dp[i][j-v[i]]+c[i])`。

**坑点：** 无效解用`INT_MAX`表示，转移前要检查`dp[i][j-v[i]]`不是无效解。

**代码：**
```cpp
// 空间压缩版
vector<int> dp(m + 1, INT_MAX); // m = H + maxV
dp[0] = 0;
for (int i = 1; i <= n; i++)
    for (int j = val[i]; j <= m; j++)
        if (dp[j - val[i]] != INT_MAX)
            dp[j] = min(dp[j], dp[j - val[i]] + cost[i]);
int ans = INT_MAX;
for (int j = H; j <= m; j++) ans = min(ans, dp[j]);
return ans;
```
