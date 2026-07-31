# class084 数位DP（上）笔记

> 视频链接：https://www.bilibili.com/video/BV1cC4y1Q7r3/
> 前置知识：位运算基础（class030-033）、动态规划基础（class066起）

---

## 题目1：统计各位数字都不同的数字个数

### 题面
给定整数 n，代表十进制数字最多有 n 位。若某个数字的每一位都不同，称为有效数字。返回有效数字的个数（不统计负数范围）。

- 测试链接：https://leetcode.cn/problems/count-numbers-with-unique-digits/
- n=0 → 返回 1（只有数字 0）

### 核心思路
直接排列组合，不需要 DP：
- 1 位数：10 种（0~9）
- 2 位数：第一位 1~9（9 种），第二位 0~9 且≠第一位（9 种）→ 9×9
- 3 位数：9×9×8
- k 位数：9×9×8×...×(11-k)
- 把所有位数的结果累加即可

### 坑点
- n=0 时返回 1，不是 0
- 第一位不能选 0，但后续位可以选 0

### 代码
```cpp
int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1;
    int ans = 10;
    for (int s = 9, i = 9, k = 2; k <= n; i--, k++) {
        s *= i;
        ans += s;
    }
    return ans;
}
```

---

## 题目2：最大为N的数字组合

### 题面
给定有序、无重复、不含 '0' 的字符数组 digits（如 ["1","3","5","7"]），可以任意次使用这些字符拼写数字。返回 ≤给定整数 n 的正整数个数。

- 测试链接：https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/

### 核心思路
**方法一（递归）**：从高位到低位线性展开，两个关键状态：
- `free`: 之前是否已经确定比 n 小（1=自由选，0=受限制）
- `fix`: 之前是否选过数字（1=选过，0=一直舍弃）

递归分支：
1. 若 `fix=0`，当前位仍可舍弃（位数比 n 少的全合法）
2. 若 `free=0`，遍历 digits 中 ≤当前位数字的：<cur 则后续 free，=cur 继续受限，>cur break
3. 若 `free=1`，digits 中全可选，直接 ×后续可能性

**方法二（打表加速）**：预处理 `cnt[i]` = 前缀已比 n 小、剩 i 位时有多少种排列（即 `m^i`）。位数不够的提前累加到 ans。只有数字 =cur 时才递归。

- 复杂度：暴力 O(m^n)（无缓存），n≤9 直接过

### 坑点
- offset 是辅助变量（跟随 len，方便提取 n 每位数字），非关键参数
- digits 不含 '0'，所以空前缀（fix=0）走到 len=0 不算有效数字
- 方法二的 cnt[0]=1 表示前缀已经确定的一种情况

### 代码（方法二核心）
```cpp
int f2(int num, int offset, int len) {
    if (len == 0) return 1; // num 自己
    int cur = (num / offset) % 10;
    int ans = 0;
    for (int idx = 0; idx < m; idx++) {
        int i = dig[idx];
        if (i < cur) ans += cnt[len - 1];
        else if (i == cur) ans += f2(num, offset / 10, len - 1);
        else break;
    }
    return ans;
}
```

---

## 题目3：统计整数数目

### 题面
给定两个数字字符串 num1、num2，以及 min_sum、max_sum。若整数 x 满足 num1 ≤ x ≤ num2 且 min_sum ≤ digit_sum(x) ≤ max_sum，称 x 为好整数。返回好整数个数，答案对 1e9+7 取模。

- 测试链接：https://leetcode.cn/problems/count-of-integers/

### 核心思路
**大策略**：`count(num1, num2) = f(0→num2) - f(0→num1) + (check(num1) ? 1 : 0)`

因为 num1 是字符串，做减一操作较麻烦，所以用"不包含 num1"的方式算，最后单独检查 num1 自身。

**递归 f(i, sum, free)**：
- i: 当前处理到第几位（从高位 0 开始）
- sum: 之前决定的数字累加和
- free: 是否已确定比 num 小

剪枝：
- `sum > max_sum` → 返回 0
- `sum + (len-i)×9 < min_sum` → 即使后面全选 9 也不够，返回 0

转移：
- `free=0`（受限制）：pick 从 0 到 cur-1 全变成 free=1，pick=cur 保持 free=0
- `free=1`（自由）：pick 从 0 到 9 全部 free=1

### 坑点
- 前导零无所谓（不影响 digit sum），所以不需要像题目4那样区分首位
- 必须挂缓存才能过（len 可达 23，sum 可达 400）
- 每一步取模，`(ans - f() + MOD) % MOD` 防负数
- dp 每次调用前 memset 重置（因为 len/max_sum 可能不同）

### 代码
```cpp
int f(int i, int sum, int free) {
    if (sum > maxSum) return 0;
    if (sum + (len - i) * 9 < minSum) return 0;
    if (i == len) return 1;
    if (dp[i][sum][free] != -1) return dp[i][sum][free];
    int cur = num[i] - '0';
    int ans = 0;
    if (free == 0) {
        for (int pick = 0; pick < cur; pick++)
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
        ans = (ans + f(i + 1, sum + cur, 0)) % MOD;
    } else {
        for (int pick = 0; pick <= 9; pick++)
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
    }
    return dp[i][sum][free] = ans;
}
```

---

## 题目4：完全没有重复的数字个数

### 题面
给定正整数 n，返回 [1, n] 范围内每一位都互不相同的正整数个数。

- 测试链接：https://leetcode.cn/problems/count-special-integers/

### 核心思路

**分两块计算**：

**第一块**：位数少于 len 的所有情况（排列组合）
- 1 位：9（1~9）
- 2 位：9×9
- 3 位：9×9×8
- ...累加到 len-1 位

**第二块**：位数 = len 且 ≤ n 的情况
- 预处理 `cnt[i]`：已确定前缀不为空，剩 i 位待选时的排列数
  - 例 len=4: cnt[3]=9×8×7, cnt[2]=8×7, cnt[1]=7, cnt[0]=1
- 首位 < n 首位：`(first-1) × cnt[len-1]`
- 首位 = n 首位：递归 f(len-1, offset/10, status)

**递归 f(len, offset, status)**：status 用位图标记 0~9 哪些数字已使用。
- 遍历 0 到 cur-1，若未用过 → `ans += cnt[len-1]`（直接结算）
- 若 cur 未用过 → 递归 `f(len-1, offset/10, status|(1<<cur))`
- 若 cur 用过 → 自身非法，只算比它小的

### 坑点
- 递归前提是"已确定前缀不为空"，这样后续位可以选 0
- n≤10^9（最多 9 位），不挂缓存也能过
- 挂缓存则状态数 = len × 2^10 ≈ 9×1024，每个状态枚举 10 → O(9×1024×10)
- 注意 cnt 表的计算依赖 len（不同 len 的 cnt 不同）

### 代码
```cpp
int f(int num, int len, int offset, int status) {
    if (len == 0) return 1; // num 自己
    int ans = 0;
    int first = (num / offset) % 10;
    for (int cur = 0; cur < first; cur++) {
        if ((status & (1 << cur)) == 0)
            ans += cnt[len - 1];
    }
    if ((status & (1 << first)) == 0)
        ans += f(num, len - 1, offset / 10, status | (1 << first));
    return ans;
}
```

---

## 题目5：至少有1位重复的数字个数

### 题面
给定正整数 n，返回 [1, n] 范围内至少有 1 位重复数字的正整数个数。

- 测试链接：https://leetcode.cn/problems/numbers-with-repeated-digits/

### 核心思路
直接用题目4的结果：`numDupDigitsAtMostN(n) = n - countSpecialNumbers(n)`

"每位都不同"的补集就是"至少有一位重复"。

### 坑点
- 直接复用题目4的 countSpecialNumbers 即可
- 不需要额外递归

### 代码
```cpp
int numDupDigitsAtMostN(int n) {
    return n - countSpecialNumbers(n);
}
```

---

## 数位DP通用模板

```
递归 f(i, 状态...):
    1. base case: i == len → 返回 1（前缀本身是有效答案）
    2. 剪枝条件（如累加和超限）
    3. 如果已缓存 → 返回缓存
    4. cur = num[i] - '0'
    5. 分支：
       - free=0: pick 0..cur-1 → free=1; pick=cur → free=0
       - free=1: pick 0..9 → 全 free=1
    6. 存入缓存，返回结果
```

**关键点**：
- 大多数数位 DP 位数少（≤10），裸递归能过
- 位数多时挂缓存即可（状态数 = 位数 × 少量标志位）
- offset 只是辅助提取数字，非关键参数
- 灵活使用预处理表（排列组合）加速结算
