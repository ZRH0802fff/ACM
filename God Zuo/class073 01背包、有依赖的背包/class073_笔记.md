# class073 背包DP — 01背包、有依赖的背包

> B站视频：[算法讲解073](https://www.bilibili.com/video/BV1NN41137jF/)
> 前置知识：class067、class068（二维DP及空间压缩）

---

## 01 01背包模板 — 洛谷 P1048

**题面：** 背包容量t，n个物品各有体积w[i]和价值v[i]，每件最多选一次，求最大价值。

**核心思路：** `dp[i][j]`=前i个物品容量不超过j的最大价值。转移：①不要i→`dp[i-1][j]`；②要i→`dp[i-1][j-w[i]]+v[i]`（需`j≥w[i]`）。空间压缩：一维数组**从右往左**更新，`j<w[i]`时天然继承上一行不更新。

**坑点：** 从右往左是为了保证读到的左侧值还是上一行的（未被覆盖）。

**代码：**
```cpp
// 空间压缩版
int dp[MAXT];
for (int i = 1; i <= n; i++) {
    for (int j = t; j >= cost[i]; j--) {
        dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
    }
}
return dp[t];
```

---

## 02 夏季特惠 — LeetCode 未公开

**题面：** 预算X元，每个商品有原价、现价、快乐值。总优惠金额≥总超过金额即可购买。求最大快乐值。

**核心思路：** 转化：`delta=(原价-现价)-现价=优惠-现价`。若`delta≥0`→必买，预算加delta，快乐值直接累加；若`delta<0`→待定商品，真正花费`=-delta`。最后在待定商品上跑01背包。

**坑点：** `delta≥0`的商品不能放进背包——它们不消耗预算反而增加预算，必须直接处理。

**代码：**
```cpp
while (m--) {
    int pre, cur, happy; cin >> pre >> cur >> happy;
    int well = (pre - cur) - cur; // 优惠 - 现价
    if (well >= 0) {
        x += well; ans += happy;  // 必买
    } else {
        cost[++idx] = -well;       // 真正花费
        val[idx] = happy;
    }
}
// 然后对cost[1..idx]跑01背包
for (int i = 1; i <= idx; i++)
    for (int j = x; j >= cost[i]; j--)
        dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
return ans + dp[x];
```

---

## 03 目标和 — LeetCode 494

**题面：** 非负数组，每个数前添加`+`或`-`后串联成表达式，求结果等于target的表达式数量。

**核心思路：** 设A=正号集合累加和，B=负号集合累加和，则`sumA-sumB=target`且`sumA+sumB=sum`，解得`sumA=(target+sum)/2`。问题变成：**有多少子序列累加和恰好为(sum+target)/2**。01背包求方案数：`dp[j] += dp[j-nums[i]]`（从右往左）。剪枝：`target>sum`或`(target&1)!=(sum&1)`→返回0。

**额外技巧—负数下标平移：** 暴力尝试版sum可能为负，把所有sum平移到`[0, 2*sum]`区间。

**坑点：** `(target+sum)`必须是偶数（奇偶性不同则无解）；空集方案数为1（`dp[0]=1`）。

**代码：**
```cpp
int findTargetSumWays(vector<int>& nums, int target) {
    int sum = 0; for (int x : nums) sum += x;
    if (sum < target || ((target & 1) != (sum & 1))) return 0;
    return subsets(nums, (target + sum) / 2);
}
int subsets(vector<int>& nums, int t) {
    if (t < 0) return 0;
    vector<int> dp(t + 1);
    dp[0] = 1;
    for (int num : nums)
        for (int j = t; j >= num; j--)
            dp[j] += dp[j - num];
    return dp[t];
}
```

---

## 04 最后一块石头的重量 II — LeetCode 1049

**题面：** 一堆石头，每次取两块对撞：重量相同→全碎；不同→剩差值。最后最多剩一块，求最小可能重量。

**核心思路：** 转化：将石头分成A、B两组对撞，最终重量=`|sumA-sumB|`。让两组之差尽量小≡在数组中选若干个数使累加和尽量接近`sum/2`。01背包：`dp[j]`=容量不超过j能凑出的最大累加和。答案=`sum - 2*dp[sum/2]`。

**坑点：** 是尽量接近但不超过`sum/2`，不是恰好等于。

**代码：**
```cpp
int lastStoneWeightII(vector<int>& stones) {
    int sum = 0; for (int s : stones) sum += s;
    int t = sum / 2;
    vector<int> dp(t + 1);
    for (int s : stones)
        for (int j = t; j >= s; j--)
            dp[j] = max(dp[j], dp[j - s] + s);
    return sum - 2 * dp[t];
}
```

---

## 05 有依赖的背包 — 洛谷 P1064

**题面：** 物品分主件和附件，每个主件最多2个附件。必须先买主件才能买其附件。给定总钱数，求最大收益（价格×重要度）。

**核心思路：** 不是每个物品单独展开，而是**以主件为单位**做可能性展开。每个主件组有最多5种方案：①不要主件；②只要主件；③主件+附件1；④主件+附件2；⑤主件+附件1+附件2。辅数组：`king[i]`标记是否主件、`fans[i]`附件数、`follows[i][2]`附件编号。只有主件才更新DP表，副件跟随主件展开。空间压缩：一维数组从右往左。

**坑点：** 记得用变量`p`记录上一个展开的主件行号，因为上一行可能是跳过的副件行。

**代码：**
```cpp
// 空间压缩版核心
for (int i = 1; i <= m; i++) {
    if (!king[i]) continue; // 副件跳过
    for (int j = n; j >= cost[i]; j--) {
        // 方案②：只要主件
        dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        int f1 = fans[i] >= 1 ? follows[i][0] : -1;
        int f2 = fans[i] >= 2 ? follows[i][1] : -1;
        // 方案③：主件+附件1
        if (f1 != -1 && j - cost[i] - cost[f1] >= 0)
            dp[j] = max(dp[j], dp[j - cost[i] - cost[f1]] + val[i] + val[f1]);
        // 方案④：主件+附件2
        if (f2 != -1 && j - cost[i] - cost[f2] >= 0)
            dp[j] = max(dp[j], dp[j - cost[i] - cost[f2]] + val[i] + val[f2]);
        // 方案⑤：全要
        if (f1 != -1 && f2 != -1 && j - cost[i] - cost[f1] - cost[f2] >= 0)
            dp[j] = max(dp[j], dp[j - cost[i] - cost[f1] - cost[f2]]
                        + val[i] + val[f1] + val[f2]);
    }
}
return dp[n];
```
