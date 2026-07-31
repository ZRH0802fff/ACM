# class080 状压DP（上）

> B站视频：[算法讲解080](https://www.bilibili.com/video/BV15a4y1o7NA/)
> 前置：位运算（003/030-033）、根据数据量猜解（043）、双向广搜（063）、递归→DP（067）

## 核心知识：状压DP

### 是什么

用整数的**位信息**表示某些样本"是否可用/是否用过"。k个样本 → 状态数 2^k，通常 k ≤ 20 才可行（2^20 ≈ 10^6）。每个状态0/1表示对应样本的可用性。

### 什么时候用 / 识别特征

- 问题的每一步从集合中选一个元素，选过的不能再选
- N ≤ 20 且有"是否使用过"的状态需要记住
- 暴力递归会重复计算相同状态（如：先选 A 再选 B 和先选 B 再选 A，后续状态相同）
- **数据量判断：** 2^N × 枚举代价 不超过 10^7~10^8 就可以用状压DP

### 核心套路

递归函数 → 挂记忆化缓存 `dp[status]` → 必要时改严格位置依赖DP → 空间压缩。只对**关键可变参数**做缓存——被决定的参数（如累计和）不用管。

---

## 01 我能赢吗 — LeetCode 464

**题面：** 1~n的数字池，两人轮流取数（不放回），累加和≥m者获胜。问先手能否稳赢。

**核心思路：** `status` 的第 i 位=1 表示数字 i 还能选。遍历所有可选的数字，若存在一个数字使得对手后续必输（`!f(新status, rest-i)`），则自己赢。记忆化缓存 `dp[status]`。

**关键洞察——为什么缓存只对status做：** `rest` 被 `status` 唯一决定——status确定了哪些数被挑走了，累加和也就确定了。反过来不成立（不同挑法可能剩余相同rest）。所以只缓存status。

**状态数量：** 2^(n+1)（多留一个0位弃而不用），每次枚举n个数字 → O(2^n × n)。

**坑点：** m==0 直接true；总和<m直接false。

**代码：**
```cpp
bool f(int n, int status, int rest) {
    if (rest <= 0) return false;
    if (dp[status] != 0) return dp[status] == 1;
    for (int i = 1; i <= n; i++)
        if ((status & (1 << i)) && !f(n, status ^ (1 << i), rest - i))
            return dp[status] = 1, true;
    return dp[status] = -1, false;
}
```

---

## 02 火柴拼正方形 — LeetCode 473

**题面：** 用所有火柴拼正方形（4条等边），不能折断，必须全用。

**核心思路：** 策略：依次冲第一条边→第二条→第三条→第四条，当前边不凑满不开下一条。

- `status`：哪些火柴还能用（1=可用）
- `cur`：当前边已拼长度
- `rest`：还剩几条边

每根火柴：能用 + 不超边长 → ①恰好凑满：`cur=0, rest-1`；②没满：`cur+len, rest`不变。

**关键洞察——为什么dp只对status做：** `cur` 和 `rest` 被 `status` 唯一决定！因为策略是从不超边长的，status 定了→已用火柴总长定了→当前边进度和完成边数也就定了。

**代码：**
```cpp
bool f(vector<int>& nums, int limit, int status, int cur, int rest) {
    if (rest == 0) return status == 0;
    if (dp[status] != 0) return dp[status] == 1;
    for (int i = 0; i < n; i++)
        if ((status & (1 << i)) && cur + nums[i] <= limit) {
            if (cur + nums[i] == limit)
                { if (f(nums, limit, status^(1<<i), 0, rest-1)) return dp[status]=1,true; }
            else
                { if (f(nums, limit, status^(1<<i), cur+nums[i], rest)) return dp[status]=1,true; }
        }
    return dp[status] = -1, false;
}
```

---

## 03 划分为k个相等的子集 — LeetCode 698

**题面：** 同02，但边数改为k（不限于4）。

**核心思路：** 状压DP版——递归函数与02完全相同，只改主函数参数（k条边、边长=sum/k）。

**回溯+剪枝版（纯暴力）：** 建k个桶，每个数字尝试放每个桶（不超过target），大数先放（排序后从后往前）。剪枝策略：①当前桶超target的跳过；②如果相邻桶的累加和相同且当前数字在该桶已失败，跳过相同累加和的桶（因为状态等价）。复杂度 O(K^N)，靠剪枝硬过——数据不苛刻时可能比状压DP还快，但不稳定。

**代码：** 同02，略。

---

## 04 TSP售货员问题 — 洛谷 P1171

**题面：** n个村庄，有向带权图。从1号出发，每个村走一次仅一次，最后回1号。求最短路程。

**核心思路：** `f(s, i)` = 已走村庄状态s（1=走过），当前在i村，走完剩余并回0的最短距离。

- base case：`s == (1<<n)-1`（全走过）→ 直接回0号村，返回 `graph[i][0]`
- 转移：枚举每个未走过的村庄j，`f(s|1<<j, j) + graph[i][j]`，取min

**状态空间：** 2^n × n，n≤19可过C++（Java可能卡空间）。空间优化版将起始村"抠掉"，n减1，状态数减半。

**代码：**
```cpp
int f(int s, int i) {
    if (s == (1 << n) - 1) return graph[i][0];
    if (dp[s][i] != -1) return dp[s][i];
    int ans = INT_MAX;
    for (int j = 0; j < n; j++)
        if ((s & (1 << j)) == 0)
            ans = min(ans, graph[i][j] + f(s | (1 << j), j));
    return dp[s][i] = ans;
}
```
