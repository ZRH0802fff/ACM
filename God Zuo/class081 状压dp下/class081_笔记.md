# class081 状压DP（下）

> B站视频：[算法讲解081](https://www.bilibili.com/video/BV1Tu4y1g7GU/)
> 前置：class080（状压DP上）

## 核心知识

本节课展示状压DP与多种技巧的组合：反转思路（谁做状态）、枚举子集、质因子打表、Brian Kernighan 逐位提取。

### 关键枚举技巧：遍历集合的所有子集

```cpp
for (int sub = status; sub > 0; sub = (sub - 1) & status) {
    // sub 是 status 的一个非空子集
}
```

---

## 01 每个人戴不同帽子的方案数 — LeetCode 1434

**题面：** n人(≤10)，40种帽子。每人有喜好列表，一人一顶不同帽，求方案数。

**核心思路——反转思考：** 若对帽子状压 ⛔ 2^40太大。反转——**对人状压**：n≤10，状态仅2^10。预处理 `hats[i]` = i号帽子能满意哪些人（位图）。

递归：`f(i, s)` = 从i号帽子出发，已满足的人状态为s，有多少种方案。
- 可能性1：i号帽子不分配给任何人 → `f(i+1, s)`
- 可能性2：i号帽子分配给某个它能满足且还没帽子的人 → 累加 `f(i+1, s|1<<p)`

**优化（f2）：** 用 Brian Kernighan 算法逐位提取帽子能满足的人，跳过 for 循环遍历所有人。`rightOne = cur & -cur` 提取最右侧1，处理后 `cur ^= rightOne` 去掉该位。

**坑点：** 帽子编号1~40，递归从1到m；`hats[i]` 的人位是从0开始。

**代码：**
```cpp
int f(int m, int n, int i, int s) {
    if (s == (1 << n) - 1) return 1;
    if (i == m + 1) return 0;
    if (dp[i][s] != -1) return dp[i][s];
    int ans = f(m, n, i + 1, s); // 不分配这顶帽子
    int cur = hats[i];
    while (cur) {
        int rightOne = cur & -cur;
        if ((s & rightOne) == 0)
            ans = (ans + f(m, n, i + 1, s | rightOne)) % MOD;
        cur ^= rightOne;
    }
    return dp[i][s] = ans;
}
```

---

## 02 最优账单平衡 — LeetCode 465

**题面：** 给定转账交易，求还清所有债务的最少交易笔数。

**核心思路——分两步：**

**第一步：** 算出每个人的净收支，去掉为0的。问题变成——把这些人分成尽量多的"不可再拆分组"，每组内部净收支之和=0。最少交易数 = n - 最大组数。

**第二步：** 状压DP求"集合最多能分成多少和为0的不可拆分组"。

- 若集合累加和=0：随便移除一个元素，递归求剩余集合最多能分的组数，然后+1。**不管移除哪个元素结论都一样**，所以试第一个就break。
- 若集合累加和≠0：枚举移除每个元素，取剩余部分能分的最大组数（不加1）。

**为什么只用对set做缓存：** sum 被 set 决定——set 确定后累加和就是确定的。

**坑点：** 单元素集合的sum≠0（因为数组里没0），直接返回0。判断"集合是否只有一个元素"用 `set & (set-1) == 0`。

**代码：**
```cpp
int f(vector<int>& debt, int set, int sum, int n) {
    if (dp[set] != -1) return dp[set];
    int ans = 0;
    if ((set & (set - 1)) != 0) { // 不只一个元素
        if (sum == 0) {
            for (int i = 0; i < n; i++)
                if (set & (1 << i))
                    return dp[set] = f(debt, set ^ (1 << i), sum - debt[i], n) + 1;
        } else {
            for (int i = 0; i < n; i++)
                if (set & (1 << i))
                    ans = max(ans, f(debt, set ^ (1 << i), sum - debt[i], n));
        }
    }
    return dp[set] = ans;
}
```

---

## 03 好子集的数目 — LeetCode 1994

**题面：** 好子集=所有元素乘积的每种质因子只出现一次。求不同好子集个数。

**核心思路：** 1~30以内只有10个质数 {2,3,5,7,11,13,17,19,23,29}。**打表** `own[i]`：数字i的质因子位图。含平方因子（如4,8,9,12）的数字标记为0（无效）。

**数字1特权：** 1不含任何质因子。有cnt₁个1，它们可以任意组合附加到任何好子集上，贡献 2^cnt₁ 倍。

**递归：** `f(i, s)` = 从数字i往下，要凑出质因子状态恰好为s，有多少种子集。从30递减到1：
- 不要i → `f(i-1, s)`
- 要i（条件：`own[i]≠0` 且 `(s & own[i]) == own[i]`）→ `cnt[i] × f(i-1, s^own[i])`

**空间压缩：** 依赖上一行和自己左上方，从右往左一维数组更新。

**坑点：** 最终答案累加所有 `s ≠ 0` 的 dp[s]；取模时减法先+MOD。

**代码（空间压缩版）：**
```cpp
dp[0] = 1;
for (int j = 0; j < cnt[1]; j++) dp[0] = (dp[0] << 1) % MOD;
for (int i = 2; i <= 30; i++) {
    int cur = own[i], times = cnt[i];
    if (cur && times)
        for (int s = LIMIT - 1; s >= 0; s--)
            if ((s & cur) == cur)
                dp[s] = (1LL * dp[s ^ cur] * times + dp[s]) % MOD;
}
int ans = 0;
for (int s = 1; s < LIMIT; s++) ans = (ans + dp[s]) % MOD;
```

---

## 04 分配重复整数 — LeetCode 1655

**题面：** 数组中若干种数（每种有出现次数），m个顾客各要 quantity[i] 个相同数字。问能否满足。

**核心思路：** 统计每种数字的个数 `cnt[]`。预处理 `sum[mask]` = 顾客子集需要多少个数字。

状压DP：`f(status, index)` = 用第index种及之后的数字，能否满足剩余订单status。

核心枚举：**遍历 status 的所有子集**，尝试用当前数字的个数一次满足某个子集：
```cpp
for (int sub = status; sub > 0; sub = (sub - 1) & status)
    if (sum[sub] <= cnt[index] && f(status ^ sub, index + 1))
        return true;
```
若所有子集都不行，再尝试"跳过当前数字"。

**坑点：** 枚举子集 `sub = (sub-1) & status` 是状压DP的必背模板。时间复杂度 O(n × 3^m)（枚举子集的所有子集）。

**代码：**
```cpp
bool f(vector<int>& cnt, int status, int index) {
    if (status == 0) return true;
    if (index == cnt.size()) return false;
    if (dp[status][index] != 0) return dp[status][index] == 1;
    int k = cnt[index];
    for (int sub = status; sub > 0; sub = (sub - 1) & status)
        if (sum[sub] <= k && f(cnt, status ^ sub, index + 1))
            return dp[status][index] = 1, true;
    if (f(cnt, status, index + 1)) return dp[status][index] = 1, true;
    return dp[status][index] = -1, false;
}
```
