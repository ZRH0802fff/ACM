# class082 动态规划中用观察优化枚举的技巧（上）

> B站视频：[算法讲解082](https://www.bilibili.com/video/BV1PN411j7aG/)
> 前置：class066-081 动态规划系列

## 核心知识

动态规划复杂度 = 状态数 × 每个状态的枚举代价。记忆化搜索在一个格子需要走for循环枚举若干子过程时，可能不是最优解。改出**严格位置依赖的动态规划**建立空间感后，通过**观察转移方程**可以发现相邻状态的枚举有重叠，从而用**窗口累加和**或**best变量**替代枚举，将枚举代价降为O(1)。

本节课重点：股票问题系列（1-6）+ DI序列（题目7）。**题目4（股票k次交易）和题目7**最能体现观察优化枚举的技巧。

---

## 01 买卖股票的最佳时机 — LeetCode 121

**题面：** 只能买卖一次，求最大利润。

**核心思路：** 枚举每个点作为卖出时机。遍历时维护0..i的最小值min，当天利润 = prices[i] - min。

**代码：**
```cpp
int ans = 0;
for (int i = 1, minVal = prices[0]; i < n; i++) {
    minVal = min(minVal, prices[i]);
    ans = max(ans, prices[i] - minVal);
}
```

---

## 02 买卖股票的最佳时机 II — LeetCode 122

**题面：** 无限次交易，同一时刻最多持有一股。

**核心思路：** 抓住所有上坡。`ans += max(prices[i]-prices[i-1], 0)`。上坡分批累加等价于一次完整的低买高卖。

**代码：**
```cpp
int ans = 0;
for (int i = 1; i < n; i++)
    ans += max(prices[i] - prices[i - 1], 0);
```

---

## 03 买卖股票的最佳时机 III — LeetCode 123

**题面：** 最多完成两笔交易。

**核心思路：** `dp2[i]` = 0..i范围上发生两次交易，且第二次在i时刻卖出的最大利润。

**方法1（超时，O(n²)）：** `dp2[i] = max(dp1[j] + prices[i] - prices[j])`，j∈[0,i]枚举第二次买入时机。

**方法2（观察优化，O(n)）：** 把式子改写：`dp2[i] = prices[i] + max(dp1[j] - prices[j])`。引入`best[i] = max(dp1[k] - prices[k]) for k≤i`，则`dp2[i] = best[i] + prices[i]`。best[i]从前一步best[i-1]和当前新指标`dp1[i]-prices[i]`取max即可。

**方法3→4（合并+空间压缩）：** 所有更新塞一个循环，用滚动变量替代数组。

**代码（最终版）：**
```cpp
int dp1 = 0, best = -prices[0], ans = 0;
for (int i = 1, minVal = prices[0]; i < n; i++) {
    minVal = min(minVal, prices[i]);
    dp1 = max(dp1, prices[i] - minVal);
    best = max(best, dp1 - prices[i]);
    ans = max(ans, best + prices[i]);
}
```

---

## 04 买卖股票的最佳时机 IV — LeetCode 188 ★核心模板

**题面：** 最多k笔交易。

**核心思路：** 剪枝：`k >= n/2` → 等价无限次（题目2）。

DP定义：`dp[i][j]` = 0..j范围上进行i次交易的最大利润。转移：
```
dp[i][j] = max( dp[i][j-1],                          // j不参与
                max_{p<j} dp[i-1][p] - prices[p] + prices[j] )  // j为卖出时机
```
用`best`变量维护`max(dp[i-1][p] - prices[p])`：初始`best = dp[i-1][0]-prices[0]`，每步`best = max(best, dp[i-1][j]-prices[j])`，则`dp[i][j] = max(dp[i][j-1], best+prices[j])`。

**空间压缩（最终版）：**
```cpp
if (k >= n / 2) return free(prices);
memset(dp, 0, sizeof(dp));
for (int i = 1, best, tmp; i <= k; i++) {
    best = dp[0] - prices[0];
    for (int j = 1; j < n; j++) {
        tmp = dp[j];
        dp[j] = max(dp[j - 1], best + prices[j]);
        best = max(best, tmp - prices[j]);
    }
}
return dp[n - 1];
```

**坑点：** 枚举优化和股票3完全一样——都是把`dp[i-1][p]-prices[p]`的最大值用滚动变量维护，省掉内层for。

---

## 05 买卖股票含手续费 — LeetCode 714

**题面：** 无限次交易，每笔卖出扣手续费fee。

**核心思路：** 状态机：
- `prepare`：获得收益的同时已扣掉一次购买+手续费的最优情况
- `done`：无限次交易的最大收益

转移：`done = max(done, prepare + prices[i])`（今天卖出），`prepare = max(prepare, done - prices[i] - fee)`（今天买入或保持）。

**代码：**
```cpp
int prepare = -prices[0] - fee, done = 0;
for (int i = 1; i < n; i++) {
    done = max(done, prepare + prices[i]);
    prepare = max(prepare, done - prices[i] - fee);
}
```

---

## 06 买卖股票含冷冻期 — LeetCode 309

**题面：** 卖出后冷冻1天不能买入。

**核心思路：** `prepare[i]` = 0..i上无限次交易+必须扣一次购买的最优。`done[i]` = 0..i上无限次交易的最大收益。因为有冷冻期，`prepare[i] = max(prepare[i-1], done[i-2] - prices[i])`（必须等一天）。

**空间压缩：** 只需 `prepare`, `done2`(done[i-2]), `done1`(done[i-1]) 三个变量滚动。

---

## 07 DI序列的有效排列 — LeetCode 903 ★观察优化枚举

**题面：** 字符串s由D/I组成，用0~n的数字排列满足D=下降、I=上升关系，求方案数。

**核心思路（巧妙的状态设计）：** `f(i, less)` = 来到位置i，前一个数字已确定但不知道是谁，只知道**还没用过的数字中比前一个小的有less个**。不需要知道具体哪些数字用过！

**枚举展开：**
- 开头或`s[i-1]=='D'`：下一个选比前一个小的 → 枚举 `nextLess ∈ [0, less-1]`
- `s[i-1]=='I'`：下一个选比前一个大的 → 枚举 `nextLess ∈ [less, less+(n-i-less)-1]`

**优化枚举（观察法）：** dp[i][less]对nextLess的求和有重叠——
- D时：`dp[i][less] = dp[i][less-1] + dp[i+1][less-1]`（前缀和）
- I时：`dp[i][less] = dp[i][less+1] + dp[i+1][less]`（后缀和）

从O(n³)降至O(n²)。

**代码：**
```cpp
for (int less = 0; less <= n; less++) dp[n][less] = 1;
for (int i = n - 1; i >= 0; i--) {
    if (i == 0 || s[i - 1] == 'D') {
        dp[i][1] = dp[i + 1][0];
        for (int less = 2; less <= n; less++)
            dp[i][less] = (dp[i][less - 1] + dp[i + 1][less - 1]) % MOD;
    } else {
        dp[i][n - i - 1] = dp[i + 1][n - i - 1];
        for (int less = n - i - 2; less >= 0; less--)
            dp[i][less] = (dp[i][less + 1] + dp[i + 1][less]) % MOD;
    }
}
```
