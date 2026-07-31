# class083 动态规划中用观察优化枚举的技巧（下）

> B站视频：[算法讲解083](https://www.bilibili.com/video/BV1pN41157uX/)
> 前置：class066-082 动态规划系列

## 核心知识

上节课讲"观察并优化转移方程"，本节课继续。同时引入"**观察并设计高效的查询结构**"来优化枚举——题目1用二分查找，题目3用有序数组+二分，题目4用minSums高效结构。

本节课还讲了一个重要的窗口技巧（题目4）：**窗口不回退**——当只关心"最长/最大"答案时，换开头后窗口不需要从头扩，只需要看能不能吸收下一块形成更长的答案。

---

## 01 规划兼职工作 — LeetCode 1235

**题面：** n份工作（开始时间、结束时间、报酬），时间不重叠，求最大报酬。

**核心思路：** 按结束时间排序。`dp[i]` = 0..i份工作的最大报酬。工作i：①不做→`dp[i-1]`；②做→`profit[i] + dp[find(i-1, start[i])]`。find：二分找"结束时间≤start[i]的最右工作"。O(n log n)。

**观察点：** dp有单调性——范围越大收益只增不减，所以选"尽量靠右的结束时间≤start的工作"最优。二分替代线性枚举。

**代码：**
```cpp
sort(jobs, jobs + n, [](auto& a, auto& b) { return a[1] < b[1]; });
dp[0] = jobs[0][2];
for (int i = 1; i < n; i++) {
    int start = jobs[i][0];
    dp[i] = jobs[i][2];
    if (jobs[0][1] <= start)
        dp[i] += dp[find(i - 1, start)];
    dp[i] = max(dp[i], dp[i - 1]);
}
```

---

## 02 K个逆序对数组 — LeetCode 629

**题面：** 1~n的排列，求恰好k个逆序对的排列数。

**核心思路：** `dp[i][j]` = 用1..i形成恰好j个逆序对的排列数。把i插入到1..(i-1)排列的第几位就增加多少逆序对。

**方法1（O(n²k)超时）：** 内层for枚举p。

**方法2（窗口累加和O(nk)）：** 画格子观察发现`dp[i][j]`是对上一行某段区间的累加——
- `i > j`：窗口只扩不缩，`window += dp[i-1][j]`
- `i ≤ j`：窗口右扩左缩，`window = window + dp[i-1][j] - dp[i-1][j-i]`

**观察点：** 每个格子的依赖画图后是滑动窗口，用一个window变量维护累加和即可。

**代码：**
```cpp
dp[0][0] = 1;
for (int i = 1, window; i <= n; i++) {
    dp[i][0] = 1; window = 1;
    for (int j = 1; j <= k; j++) {
        if (i > j) window = (window + dp[i-1][j]) % MOD;
        else window = ((window + dp[i-1][j]) % MOD - dp[i-1][j-i] + MOD) % MOD;
        dp[i][j] = window;
    }
}
```

---

## 03 自由之路 — LeetCode 514

**题面：** 环形轮盘ring，每次操作：①按按钮输入当前字符（代价1）；②顺时针/逆时针旋转一格（代价1）。给定key，求输入key的最小代价。

**核心思路：** `f(i, j)` = 指针在ring[i]，要输入key[j..]的最小代价。

**关键贪心——枚举优化：** 若`ring[i]==key[j]`直接按，不需要移动。否则只需考虑**顺时针最近的key[j]**和**逆时针最近的key[j]**两个位置，中间的其他同名字符一定不会更优！

**高效查询结构：** 预处理`where[c][k]` = 字符c在ring中的所有位置（有序数组）。顺时针最近→二分找`>i`的最左；逆时针最近→二分找`<i`的最右。环形距离公式：`distance1 = jump>i ? jump-i : n-i+jump`。

**代码：**
```cpp
if (ring[i] == key[j]) {
    ans = 1 + f(i, j + 1);
} else {
    int jump1 = clockFind(i, key[j]); // 顺时针最近
    int d1 = jump1 > i ? jump1 - i : n - i + jump1;
    int jump2 = counterClockFind(i, key[j]); // 逆时针最近
    int d2 = i > jump2 ? i - jump2 : i + n - jump2;
    ans = min(d1 + f(jump1, j), d2 + f(jump2, j));
}
```

---

## 04 累加和不大于k的最长子数组 — 牛客 ★窗口不回退

**题面：** 数组有正负零，求累加和 ≤ k 的最长子数组长度。要求O(n)。

**核心思路：** 关键在于"只关心更长的答案"——窗口不回退！

**预处理两个结构（O(n)）：**
- `minSums[i]`：以i开头往右扩，能得到的**最小**子数组累加和
- `minSumEnds[i]`：取得该最小值时的结束位置

生成方式（从右往左）：若`minSums[i+1] < 0`，吞下它更小 → `minSums[i] = nums[i] + minSums[i+1]`，右边界继承；否则自己待着。

**主流程（窗口不回退）：** 从i=0开始，每次尝试把"下一块"（minSums[end]）吞进窗口：若能吞（`sum+minSums[end] ≤ k`）→吞入，end跳到下一块末尾+1。吞完后结算当前窗口长度`end-i`。然后换开头i+1：窗口吐掉nums[i]，end不退回！因为"以i+1开头更短的答案我们根本不关心"。

**坑点：** 如果窗口根本没扩出来（`end==i`），说明i位置连自己一块都进不来，end跳到i+1跟上i。

**代码：**
```cpp
// 预处理
minSums[n-1] = nums[n-1]; minSumEnds[n-1] = n-1;
for (int i = n-2; i >= 0; i--) {
    if (minSums[i+1] < 0)
        minSums[i] = nums[i] + minSums[i+1],
        minSumEnds[i] = minSumEnds[i+1];
    else
        minSums[i] = nums[i], minSumEnds[i] = i;
}
// 主流程——窗口不回退
int ans = 0;
for (int i = 0, sum = 0, end = 0; i < n; i++) {
    while (end < n && sum + minSums[end] <= k)
        sum += minSums[end], end = minSumEnds[end] + 1;
    ans = max(ans, end - i);
    if (end > i) sum -= nums[i];
    else end = i + 1;
}
```

---

## 总结：优化枚举的两大类

| 类型 | 技巧 | 题目 |
|------|------|------|
| 观察转移方程 | best变量替代枚举 | 股票3、股票4 |
| 观察转移方程 | 窗口累加和 | K逆序对、DI序列 |
| 设计查询结构 | 二分查找 | 工作安排、自由之路 |
| 设计查询结构 | 预处理+窗口不回退 | 最长子数组 |
