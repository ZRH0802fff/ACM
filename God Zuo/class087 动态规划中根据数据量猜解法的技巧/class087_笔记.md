# class087 动态规划中根据数据量猜解法的技巧

> 前置知识：讲解043（根据数据量猜解法）、讲解066~069（动态规划基础）、讲解072（最长递增子序列）、零一背包。
>
> 核心结论：**一条指令 ≈ 一次操作，运行 1 秒约能执行 10⁷ ~ 10⁸ 条指令**。任何一个 DP 尝试方法，只要估出它的 DP 表规模（或复杂度代入具体数据量）超过这个量级，就必然超时，应该**立即换尝试方法**，不要浪费时间写出来。反过来，如果某个格子的枚举代价太高，也能据此判断出「需要优化到什么程度才能通过」。

---

## 题目1：贿赂怪兽

### 题面

勇士能力从 0 开始，要**依次**通关 1~N 号怪兽（顺序不能变）。来到 i 号怪兽时：

- 若当前能力 **<** i 号怪兽能力 a[i]，**必须**花 b[i] 贿赂它，怪兽能力 a[i] 累加到自身能力上；
- 若当前能力 **≥** a[i]，可以**直接通过**（能力不变），也可以**依然选择贿赂**（能力累加 a[i]）。

求通关所有怪兽的**最小花费**。

> 数据量：课程里**故意不给出**（字幕明确"假设没有数据量"），只给示例规模 n≤1000、能力≤10⁴、钱≤10。题目想通过「能力范围大 / 钱范围小」和「能力范围小 / 钱范围大」两种设定，分别引导出两种 DP 猜法。

### 核心思路

本质是**零一背包**，但「哪个作为背包容量」由数据量决定：

**设定一：能力 a[i] 范围很大，但贿赂金 b[i] 范围不大。**

此时所有贿赂金累加和 `m = Σb[i]` 不大，以「**花的钱**」作为 DP 的列。

定义 `dp[i][j]`：花的钱**不超过 j**，通过前 i 个怪兽，能取得的**最大能力**。若无论如何都通不过，则为 `INT_MIN`。

- 可能性一（不贿赂 i）：要求 `dp[i-1][j] >= a[i]`，则 `dp[i][j] = dp[i-1][j]`；
- 可能性二（贿赂 i）：要求 `j - b[i] >= 0` 且 `dp[i-1][j-b[i]] != INT_MIN`，则 `dp[i][j] = dp[i-1][j-b[i]] + a[i]`。

最后看**最后一行**（通关 N 只），从 `j=0` 往后找第一个非 `INT_MIN` 的列，就是最少花费。

**设定二：能力 a[i] 范围不大，但贿赂金 b[i] 范围很大。**

此时 `Σb[i]` 太大做不了容量，改以「**能力**」作为 DP 的列。令 `m = Σa[i]`。

定义 `dp[i][j]`：能力**正好是 j**，并确保能通过前 i 个怪兽，**至少花多少钱**。无效则为 `INT_MAX`。

- 可能性一（不贿赂 i）：要求 `j >= a[i]` 且 `dp[i-1][j] != INT_MAX`，则 `dp[i][j] = dp[i-1][j]`；
- 可能性二（贿赂 i）：要求 `j - a[i] >= 0` 且 `dp[i-1][j-a[i]] != INT_MAX`，则 `dp[i][j] = dp[i-1][j-a[i]] + b[i]`。

两种可能性取 min。最后答案 = 最后一行整行的最小值。

> 注意设定二的边界：`dp[0][0]=0`（一个怪兽也没有，正好 0 能力，花 0 元），`dp[0][j>0]=INT_MAX`。

### 坑点

- 普通数组（`a`、`b`、`dp`）按规范一律用全局静态数组：`a[MAXN]`、`b[MAXN]`、`dp2D[MAXN][MAXM]`、`dp1D[MAXM]`，其中 `MAXN=1001`、`MAXM=10001`（字幕示例 n≤1000，钱/能力两种设定下 dp 列累加和都 ≤ 10⁴）。`m` 是运行时累加出来的，但全局数组按最大数据量预开即可。
- `compute1`/`compute3` 共用 `dp2D`，但两个版本的第 0 行初始值不同（`compute1` 是 0，`compute3` 是 `INT_MAX`），所以各自开头都要显式初始化第 0 行。
- 用 `INT_MIN`/`INT_MAX` 作「无效」哨兵时，转移前要先判 `!= INT_MIN/INT_MAX`，避免 `+a[i]` 溢出。
- 题目通过 `compute1`（普通二维 DP）即可；`compute3` 在牛客上会爆内存（二维 `MAXN×MAXM` 太大），但 `compute4`（空间压缩）仍能通过，只是时间较大。

### 代码

```cpp
const int MAXN = 1001;  // 字幕示例 n <= 1000
const int MAXM = 10001; // dp列累加和 <= 1000 * 10
int a[MAXN], b[MAXN];
int dp2D[MAXN][MAXM]; // 二维，compute1 / compute3 共用
int dp1D[MAXM];       // 一维，compute2 / compute4 共用

// 设定一：能力范围大、钱范围小，dp 列 = 钱的累加和
int compute1(int n) {
    int m = 0;
    for (int i = 1; i <= n; i++) m += b[i];
    for (int j = 0; j <= m; j++) dp2D[0][j] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp2D[i][j] = INT_MIN;
            if (dp2D[i - 1][j] >= a[i]) {
                dp2D[i][j] = dp2D[i - 1][j];
            }
            if (j - b[i] >= 0 && dp2D[i - 1][j - b[i]] != INT_MIN) {
                dp2D[i][j] = max(dp2D[i][j], dp2D[i - 1][j - b[i]] + a[i]);
            }
        }
    }
    for (int j = 0; j <= m; j++) {
        if (dp2D[n][j] != INT_MIN) return j;
    }
    return -1;
}

// 设定二：能力范围小、钱范围大，dp 列 = 能力的累加和
int compute3(int n) {
    int m = 0;
    for (int i = 1; i <= n; i++) m += a[i];
    dp2D[0][0] = 0;
    for (int j = 1; j <= m; j++) dp2D[0][j] = INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp2D[i][j] = INT_MAX;
            if (j >= a[i] && dp2D[i - 1][j] != INT_MAX) {
                dp2D[i][j] = dp2D[i - 1][j];
            }
            if (j - a[i] >= 0 && dp2D[i - 1][j - a[i]] != INT_MAX) {
                dp2D[i][j] = min(dp2D[i][j], dp2D[i - 1][j - a[i]] + b[i]);
            }
        }
    }
    int ans = INT_MAX;
    for (int j = 0; j <= m; j++) ans = min(ans, dp2D[n][j]);
    return ans == INT_MAX ? -1 : ans;
}
```

---

## 题目2：选 k 个数字使两集合累加和相差不超过 1

### 题面

给定正数 `n`，表示 1~n 每个数字可选且**只能选一次**；给定 `k`，从中挑 k 个数字构成集合 A，剩下构成集合 B。要求 `|sum(A) - sum(B)| <= 1`。能做到返回 A 的任意一种选法（长度 k），做不到返回空数组。

- `2 <= n <= 10^6`，`1 <= k <= n`
- 无测试链接（大厂笔试），用对数器验证。

### 核心思路

如果直接当「零一背包 + 决策路径」写，需要三维可变参数：位置 i（10⁶）、已选个数 k（10⁶）、累加和 sum（更大），**表规模远超 10⁷~10⁸，必然超时**。

但注意到数组**非常特殊**：1~n 是连续的、每个数字恰好一个。最优解不需要 DP，纯数值计算：

1. 令 `sum = (1+n)*n/2`。若 sum 为偶数，A 必须正好凑出 `sum/2`；若为奇数，A 可凑 `sum/2` 或 `sum/2+1` 任一个。
2. 问题变为：1~n 中挑 k 个数，累加和正好凑 `target`。

**凑法（build）**：

- 前 k 个数（1..k）的累加和最小，记为 `minKSum = k*(k+1)/2`。
- 每个数字能「往右提升」的最大幅度是 `range = n - k`（因为 k 个数互不相同、连续）。
- 若 `target < minKSum` 或 `target > minKSum + range*k`（后者即最大的 k 个数之和），直接返回空。
- `need = target - minKSum`（还需补的数值）。
  - `rightSize = need / range`：有多少个数字要**整体搬到最右边**；
  - 余数 `need % range` 决定「中间那个数」往右跳多少：`midIndex = (k - rightSize) + need % range`；
  - `leftSize = k - rightSize - (need % range == 0 ? 0 : 1)`：左边保留几个原封不动的数。
- 拼装：左边抄 `1..leftSize`，中间（若余数非 0）放 `midIndex`，右边抄 `n, n-1, ...`（共 rightSize 个）。

### 坑点

- 函数名 `generate` 与 `std::generate` 冲突，改名为 `build`。
- `long` 累加和会溢出 int（`n=10^6` 时 sum 约 5×10¹¹），必须用 `long long`。
- 余数为 0 时**中间没有跳变的数**，`leftSize` 不需要再减 1。
- 偶数只有一种方案；奇数时先试 `sum/2`，失败再试 `sum/2+1`。
- 返回数组按规范用全局 `ansArr`/`ansLen`（`ansLen=0` 表示空）；三维验证 dp 用全局 `dp3D`，大小要按对数器的实际 `n ∈ [2, 61]` 留足（`MAXV=62`、`MAXS=947`）。

### 代码

```cpp
const int MAXN = 1000001; // 结果数组最多 k <= n <= 10^6 个
const int MAXV = 62, MAXK = 62, MAXS = 947; // 三维dp只用于对数器验证
int ansArr[MAXN];
int ansLen;
int dp3D[MAXV][MAXK][MAXS];

void pick(int n, int k) {
    long long sum = (long long)(n + 1) * n / 2;
    build(sum / 2, n, k);
    if (ansLen == 0 && (sum & 1) == 1) {
        build(sum / 2 + 1, n, k);
    }
}

void build(long long sum, int n, int k) {
    long long minKSum = (long long)(k + 1) * k / 2;
    int range = n - k;
    if (sum < minKSum || sum > minKSum + (long long)range * k) {
        ansLen = 0;
        return;
    }
    long long need = sum - minKSum;
    int rightSize = (int)(need / range);
    int midIndex = (k - rightSize) + (int)(need % range);
    int leftSize = k - rightSize - (need % range == 0 ? 0 : 1);
    ansLen = k;
    for (int i = 0; i < leftSize; i++) ansArr[i] = i + 1;
    if (need % range != 0) ansArr[leftSize] = midIndex;
    for (int i = k - 1, j = 0; j < rightSize; i--, j++) ansArr[i] = n - j;
}
```

---

## 题目3：两个排列的最长公共子序列长度

### 题面

给出由 1~n 组成的两个排列，求它们的最长公共子序列长度。`n <= 10^5`。

### 核心思路

经典的 LCS 需要 `n×n` 二维表，`10^5 × 10^5 = 10^10`，**远超规模，不可行**。但本题两个串是**排列**（元素互不相同），可以转成 LIS：

1. 遍历第一个排列 A，记录每个值的位置：`where[A[i]] = i`。
2. 把第二个排列 B 的每个值改写为它在 A 中的位置：`B[i] = where[B[i]]`。
3. 对改写后的 B 求**最长递增子序列（LIS）**，长度即答案。

**为什么对**：在 B 中从左往右选递增子序列 → 对应「第二个串从左往右选」；递增本身 → 对应「第一个串中下标从左往右」。两个方向都从左往右，且每个值在 A 中唯一，所以 LIS 长度 = LCS 长度。复杂度 `O(n log n)`。

### 坑点

- `ends` 数组与 `std::ends`（标准库流操纵符）冲突，改名为 `endsArr`。
- C++ 要求函数先声明后使用：`bs` 定义在 `lis` 之前，`lis` 定义在 `compute` 之前。
- 数组按 Java static 转成全局静态数组（`MAXN = 100001`）。
- 用二分找「>= num 的最左位置」实现 LIS（讲解 072 的标准做法）。

### 代码

```cpp
const int MAXN = 100001;
int a[MAXN], b[MAXN], where[MAXN], endsArr[MAXN];
int n;

int bs(int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (endsArr[m] >= num) { ans = m; r = m - 1; }
        else l = m + 1;
    }
    return ans;
}

int lis() {
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs(len, b[i]);
        if (find == -1) endsArr[len++] = b[i];
        else endsArr[find] = b[i];
    }
    return len;
}

int compute() {
    for (int i = 0; i < n; i++) where[a[i]] = i;
    for (int i = 0; i < n; i++) b[i] = where[b[i]];
    return lis();
}
```

---

## 题目4：使数组严格递增的最小操作数

### 题面

给两个整数数组 `arr1`、`arr2`。一次操作：从 arr2 中选一个数替换 arr1 中的一个位置。求让 arr1 **严格递增**所需的最小操作数；做不到返回 -1。

- `1 <= arr1.length, arr2.length <= 2000`，`0 <= arr1[i], arr2[i] <= 10^9`。

### 核心思路

**第一步：预处理 arr2。** 先排序，再去重（重复数字不可能用两次，否则无法严格递增），得到 arr2 的有效区间 `[0, m)`，严格递增。

**关键猜法**：如果暴力设一个「前一位被替换成了几」的参数，因为值域到 10⁹，DP 表规模爆炸。最优解只用**一个可变参数 i**，配合一个强潜台词：

> `f(i)`：arr1 中 `[0, i-1]` 已严格递增，且 `arr1[i-1]` **一定是原装的（没被替换）**；问让 `[i, n-1]` 整体严格递增，还需要几次替换。

枚举「下一个最近的**原装**位置 j」（j 从 i 到 n）：

- j 之前的位置 `[i, j-1]` 都必须用 arr2 替换，且要「刚好比前一位大」地**依次**取 arr2 里的数（尽量小）。
- 若 `pre < arr1[j]`（j 位置能原装），则 `分支代价 = k（已替换次数） + f(j+1)`。
- 若 arr2 中找不到比当前 pre 大的数（`find == -1`），或 arr2 不够长（`find >= m`），提前 break。
- j == n 的分支：`[i, n-1]` 全替换，代价就是 k。

所有分支取 min。用 `bs(arr2, m, pre)` 找 arr2 有效区间上 **> pre 的最左位置**，之后每次 `find++` 依次取下一个数，无需重复二分。

**记忆化搜索 `makeArrayIncreasing1`** → **严格位置依赖 `makeArrayIncreasing2`**：`dp[n]=0`，从 `i=n-1` 到 0 反推（因为 `f(i)` 依赖更大的下标 `f(j+1)`），逻辑照抄递归。

复杂度 `O(n * min(n, m))`，外加每个 i 一次 `O(log m)` 的二分（并列关系）。

### 坑点

- `pre = i == 0 ? INT_MIN : arr1[i-1]`：i=0 时「前一位」视为负无穷。
- `next` 可能为 `INT_MAX`（无效），只有 `next != INT_MAX` 才参与 `min(ans, k + next)`。
- `find` 每次用完后 `find++`，同时要判 `find < m` 防止越出有效区。
- LeetCode 提交入口是 `makeArrayIncreasing`，Java 源码只有 1/2 两个版本，需补一个入口调用 `makeArrayIncreasing2`。
- `bs` 与 `f1` 作为全局函数放在 `class Solution` 之前；`dp` 是全局 `int dp[MAXN]`（`MAXN=2001`），`arr1`/`arr2` 保留 `vector<int>&` 接口。

### 代码

```cpp
const int MAXN = 2001; // arr1.length <= 2000
int dp[MAXN];

int bs(vector<int>& arr2, int size, int num) {
    int l = 0, r = size - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (arr2[m] > num) { ans = m; r = m - 1; }
        else l = m + 1;
    }
    return ans;
}

int f1(vector<int>& arr1, vector<int>& arr2, int n, int m, int i) {
    if (i == n) return 0;
    if (dp[i] != -1) return dp[i];
    int ans = INT_MAX;
    int pre = i == 0 ? INT_MIN : arr1[i - 1];
    int find = bs(arr2, m, pre);
    for (int j = i, k = 0, next; j <= n; j++, k++) {
        if (j == n) {
            ans = min(ans, k);
        } else {
            if (pre < arr1[j]) {
                next = f1(arr1, arr2, n, m, j + 1);
                if (next != INT_MAX) ans = min(ans, k + next);
            }
            if (find != -1 && find < m) pre = arr2[find++];
            else break;
        }
    }
    return dp[i] = ans;
}

class Solution {
public:
    int makeArrayIncreasing1(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        int m = 1;
        for (int i = 1; i < (int)arr2.size(); i++)
            if (arr2[i] != arr2[m - 1]) arr2[m++] = arr2[i];
        int n = arr1.size();
        memset(dp, -1, sizeof(dp));
        int ans = f1(arr1, arr2, n, m, 0);
        return ans == INT_MAX ? -1 : ans;
    }

    int makeArrayIncreasing2(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        int m = 1;
        for (int i = 1; i < (int)arr2.size(); i++)
            if (arr2[i] != arr2[m - 1]) arr2[m++] = arr2[i];
        int n = arr1.size();
        dp[n] = 0;
        for (int i = n - 1, ans, pre, find; i >= 0; i--) {
            ans = INT_MAX;
            pre = i == 0 ? INT_MIN : arr1[i - 1];
            find = bs(arr2, m, pre);
            for (int j = i, k = 0, next; j <= n; j++, k++) {
                if (j == n) {
                    ans = min(ans, k);
                } else {
                    if (pre < arr1[j]) {
                        next = dp[j + 1];
                        if (next != INT_MAX) ans = min(ans, k + next);
                    }
                    if (find != -1 && find < m) pre = arr2[find++];
                    else break;
                }
            }
            dp[i] = ans;
        }
        return dp[0] == INT_MAX ? -1 : dp[0];
    }

    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        return makeArrayIncreasing2(arr1, arr2);
    }
};
```

---

## 总结

四道题串起「根据数据量猜解法」这一技巧：

1. **贿赂怪兽**：同一题，数据量不同 → 选择「钱」还是「能力」做背包容量（两种猜法）。
2. **选 k 个数**：普通零一背包表规模 10¹⁰ 必炸 → 利用「1~n 连续」的特殊性，纯数值构造。
3. **两个排列 LCS**：`n²` 表必炸 → 排列元素唯一，转成 LIS 做到 `O(n log n)`。
4. **使数组严格递增**：值域 10⁹ 的「前一位替换值」参数必炸 → 用「i-1 必原装」的潜台词把参数压成 1 个。

拿到题先**估 DP 表规模 / 复杂度**，超 10⁷~10⁸ 就换尝试方法或优化枚举，这是决定「哪种解法能过」的元能力。
