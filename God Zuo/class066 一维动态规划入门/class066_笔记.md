# class066 从递归入手一维动态规划

> 本节是【必备】阶段动态规划专题的第一课，核心是理解「**动态规划 = 用空间代替重复计算**」。
> 题目 1~4 都从**递归尝试**入手，逐步改出记忆化搜索 → 严格位置依赖 → 空间压缩；题目 5~8 直接用**动态规划的视角**来分析。
> 关键结论：**尝试策略 = 转移方程**，完全一回事；推荐从尝试入手，因为代码好写，一旦尝试错了重想代价轻。

---

## 题目1：斐波那契数

- **测试链接**：https://leetcode.cn/problems/fibonacci-number/
- **题面**：给定 `n`，计算 `F(n)`，其中 `F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)`。数据量 `n ≤ 30`。
- **核心思路**：展示「递归 → 记忆化 → 严格位置依赖 → 空间压缩」四个版本。
  1. `f1(i)` 纯递归：大量重复计算，指数级。
  2. `f2(i)` 记忆化搜索：用 `dp[i]` 缓存已算结果，遇到 `-1` 才继续算。
  3. `fib3` 严格位置依赖：`dp[i] = dp[i-1] + dp[i-2]`，从底到顶填表。
  4. `fib` 空间压缩：只保留 `lastLast`、`last` 两个变量滚动。
- **坑点**：
  - 记忆化搜索要用 `-1` 标记「未计算」，所以全局数组先 `memset(dp, -1, sizeof(dp))`。
  - 严格位置依赖版本里，全局数组可能残留上一版本留下的 `-1`，必须 `memset(dp, 0, sizeof(dp))` 显式清零。
  - 最优解是矩阵快速幂，`O(log n)`，后续课程讲，本节不涉及。
- **代码**（空间压缩版，即 Java 的 `fib4`）：

```cpp
int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int lastLast = 0, last = 1;
    for (int i = 2, cur; i <= n; i++) {
        cur = lastLast + last;
        lastLast = last;
        last = cur;
    }
    return last;
}
```

---

## 题目2：最低票价

- **测试链接**：https://leetcode.cn/problems/minimum-cost-for-tickets/
- **题面**：`days` 数组（元素在 `1~365`）给出要旅行的日子，三种票：`1天 costs[0]`、`7天 costs[1]`、`30天 costs[2]`，求覆盖所有旅行日的最低花费。数据量 `days.length ≤ 365`。
- **核心思路**：
  - 尝试：`f1(i)` 表示 `days[i..]` 的最少花费。对每个起点 `i`，枚举三种票，买第 `k` 种票后能一直覆盖到 `j`（`days[j] >= days[i] + durations[k]` 的第一个位置），则 `ans = min(costs[k] + f1(j))`。
  - 关键：`j` 在三种票之间**单调不回退**（因为 `durations` 递增），所以 `while` 循环整体最多走 `30` 次，枚举行为可视为 `O(1)`。
  - 记忆化：`dp[i]` 缓存 `f2(i)`；严格位置依赖：从 `i=n-1` 倒着填，`dp[i] = min(dp[i], costs[k] + dp[j])`。
- **坑点**：
  - `dp[i]` 初始化为 `INT_MAX` 表示「未计算/无穷大」，不是 `-1`（因为花费非负）。
  - 严格位置依赖版本要 `dp[n]=0` 作为递归边界（无旅行时花费为 0）。
  - `durations` 是固定 `{1,7,30}` 的全局数组，三种票统一用 `for k=0..2` 枚举。
- **代码**（严格位置依赖版）：

```cpp
int mincostTickets(vector<int>& days, vector<int>& costs) {
    int n = days.size();
    for (int i = 0; i <= n; i++) dp[i] = INT_MAX;
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int k = 0, j = i; k < 3; k++) {
            while (j < n && days[i] + durations[k] > days[j]) j++;
            dp[i] = min(dp[i], costs[k] + dp[j]);
        }
    }
    return dp[0];
}
```

---

## 题目3：解码方法

- **测试链接**：https://leetcode.cn/problems/decode-ways/
- **题面**：数字到字母的映射 `'A'->"1" ... 'Z'->"26"`，给定只含数字的非空字符串 `s`，求解码方法总数，答案保证 32 位整数。数据量 `s.length ≤ 100`。
- **核心思路**：
  - 尝试：`f1(i)` 表示 `s[i..]` 的有效解码数。若 `s[i]=='0'` 则无法单独解码返回 0；否则 `s[i]` 单独解一位 `+ f1(i+1)`，若 `s[i]s[i+1]` 构成的两位数 `≤26` 则还能两位合解 `+ f1(i+2)`。
  - 严格位置依赖：`dp[i] = dp[i+1]`（当前位单独解），加上 `dp[i+2]`（两位合解，需 `s[i]s[i+1] ≤ 26` 且 `s[i]` 非 0）。
  - 空间压缩：只保留 `next = dp[i+1]`、`nextNext = dp[i+2]`。
- **坑点**：
  - `'0'` 单独不能映射，但 `"10"`、`"20"` 可以两位合解（`10/20 ≤ 26`），所以 `s[i]=='0'` 时只能作为「两位」的后一位，不能单独解。
  - 两位合解的条件要同时检查「`s[i] != '0'`」和「两位数 `≤ 26`」。
  - 边界 `dp[n]=1`：空串算 1 种（作为递归终止的种子）。
- **代码**（空间压缩版，即 Java 的 `numDecodings4`）：

```cpp
int numDecodings(string s) {
    int next = 1;      // dp[i+1]
    int nextNext = 0;  // dp[i+2]
    for (int i = s.length() - 1, cur; i >= 0; i--) {
        if (s[i] == '0') {
            cur = 0;
        } else {
            cur = next;
            if (i + 1 < s.length() && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
                cur += nextNext;
            }
        }
        nextNext = next;
        next = cur;
    }
    return next;
}
```

---

## 题目4：解码方法 II

- **测试链接**：https://leetcode.cn/problems/decode-ways-ii/
- **题面**：同题目3，但字符串中可出现 `'*'`，表示 `1~9` 的任一数字（不含 0），答案对 `10^9+7` 取模。数据量 `s.length ≤ 10^5`。
- **核心思路**：在题目3的基础上，把「一位」「两位」的贡献按 `*` 与否分情况计数。
  - **单独解码一位**：`s[i]=='*'` 时乘 9，否则乘 1。
  - **两位合解**，分四种情况：
    - `num num`：`(s[i]-'0')*10 + s[i+1]-'0' <= 26` 才加。
    - `num *`：`s[i]=='1'` 时 `*` 可取 `1~9` 共 9 种；`s[i]=='2'` 时 `*` 可取 `1~6` 共 6 种。
    - `* num`：`s[i+1]<='6'` 时 `*` 可取 `1~2` 共 2 种；否则 `*` 只能取 1 共 1 种。
    - `* *`：`11~19` 和 `21~26` 共 15 种（没有 10、20，因为 `*` 不能取 0）。
  - 每一步 `ans %= mod`。
- **坑点**：
  - `*` 表示 `1~9`，**不含 0**，所以 `* *` 没有 `10`、`20`，是 15 种不是更多。
  - 答案会溢出，`dp` 数组和中间量都要用 `long long`，每步取模。
  - 空间压缩版的循环末尾 `cur` 要**重置为 0**（否则 `s[i]=='0'` 分支会残留上一轮的 `cur`）。
- **代码**（空间压缩版，即 Java 的 `numDecodings4`）：

```cpp
int numDecodings(string str) {
    int n = str.length();
    long long cur = 0, next = 1, nextNext = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (str[i] != '0') {
            cur = (str[i] == '*' ? 9 : 1) * next;
            if (i + 1 < n) {
                if (str[i] != '*') {
                    if (str[i + 1] != '*') {
                        if ((str[i] - '0') * 10 + str[i + 1] - '0' <= 26) cur += nextNext;
                    } else {
                        if (str[i] == '1') cur += nextNext * 9;
                        if (str[i] == '2') cur += nextNext * 6;
                    }
                } else {
                    if (str[i + 1] != '*') {
                        if (str[i + 1] <= '6') cur += nextNext * 2;
                        else cur += nextNext;
                    } else {
                        cur += nextNext * 15;
                    }
                }
            }
            cur %= mod;
        }
        nextNext = next;
        next = cur;
        cur = 0;
    }
    return (int) next;
}
```

---

## 题目5：丑数 II

- **测试链接**：https://leetcode.cn/problems/ugly-number-ii/
- **题面**：求第 `n` 个丑数（只含质因数 2、3、5 的正整数，第 1 个是 1）。数据量 `n ≤ 1690`。
- **核心思路**：三指针。`dp[1]=1`，从第 2 个开始，`dp[i]` 取三个候选的最小值：
  - `a = dp[i2]*2`、`b = dp[i3]*3`、`c = dp[i5]*5`，`dp[i] = min(a,b,c)`。
  - 哪个候选被选中，对应指针就后移一位（`i2/i3/i5++`）。
  - 本质是「三个有序序列归并」，`dp[i2]*2`、`dp[i3]*3`、`dp[i5]*5` 都是单调不减的。
- **坑点**：
  - 指针后移用**三个独立 if** 而不是 else-if，因为可能存在 `dp[i2]*2 == dp[i3]*3`（如 6）的重复，两个指针都要后移才能去重。
  - 全局数组只写 `dp[1..n]`，`dp[0]` 不用；多次调用会重写 `dp[1]` 并覆盖后续，无副作用。
- **代码**：

```cpp
int nthUglyNumber(int n) {
    dp[1] = 1;
    for (int i = 2, i2 = 1, i3 = 1, i5 = 1, a, b, c, cur; i <= n; i++) {
        a = dp[i2] * 2;
        b = dp[i3] * 3;
        c = dp[i5] * 5;
        cur = min(min(a, b), c);
        if (cur == a) i2++;
        if (cur == b) i3++;
        if (cur == c) i5++;
        dp[i] = cur;
    }
    return dp[n];
}
```

---

## 题目6：最长有效括号

- **测试链接**：https://leetcode.cn/problems/longest-valid-parentheses/
- **题面**：给定只含 `'('` 和 `')'` 的字符串，求最长有效（格式正确且连续）括号子串长度。数据量 `s.length ≤ 3×10^4`。
- **核心思路**：一维 DP，`dp[i]` 表示「**必须以 i 结尾**」的最长有效括号长度。只处理 `s[i]==')'`：
  - 设 `p = i - dp[i-1] - 1`，是「与 `s[i]` 配对的左括号」的候选位置。
  - 若 `p >= 0 && s[p]=='('`，则 `dp[i] = dp[i-1] + 2 + (p-1 >= 0 ? dp[p-1] : 0)`。
    - `dp[i-1]` 是中间一段已经匹配的长度；`+2` 是当前这对 `()`；`dp[p-1]` 是左括号前还连着的一段有效长度。
  - 答案取所有 `dp[i]` 的最大值。
- **坑点**：
  - 只更新 `s[i]==')'` 的位置，`s[i]=='('` 时 `dp[i]` 恒为 0（以左括号结尾不可能有效）。
  - `p` 可能越界为负数，先判 `p >= 0` 再访问 `s[p]`。
  - `p-1` 也可能越界，三元表达式兜底取 0。
- **代码**：

```cpp
int longestValidParentheses(string str) {
    int n = str.length();
    memset(dp, 0, sizeof(dp));
    int ans = 0;
    for (int i = 1, p; i < n; i++) {
        if (str[i] == ')') {
            p = i - dp[i - 1] - 1;
            if (p >= 0 && str[p] == '(') {
                dp[i] = dp[i - 1] + 2 + (p - 1 >= 0 ? dp[p - 1] : 0);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}
```

---

## 题目7：环绕字符串中唯一的子字符串

- **测试链接**：https://leetcode.cn/problems/unique-substrings-in-wraparound-string/
- **题面**：`base` 是 `"abcd..z"` 无限环绕的字符串，统计 `s` 中有多少个**不同**的非空子串也出现在 `base` 中。数据量 `s.length ≤ 10^5`。
- **核心思路**：**按「结尾字符 + 最大延伸长度」去重**。
  - 先把字符转成 `0~25`：`s[i] = str[i]-'a'`。
  - `dp[c]` 记录「以字符 `c` 结尾、满足 base 环绕规则」的最长延伸长度。
  - 扫描时维护连续环绕长度 `len`：`(pre==25 && cur==0) || pre+1==cur` 时 `len++`，否则 `len=1`，然后 `dp[cur] = max(dp[cur], len)`。
  - 最后 `sum(dp[0..25])`。
  - 正确性：以某个字符结尾、长度为 `L` 的合法子串，其长度 `1..L` 的子串也一定合法，所以「以 `c` 结尾」贡献的不同子串数就是 `dp[c]`，累加 26 个字符即可，天然去重。
- **坑点**：
  - 环绕规则是 `'z'` 后接 `'a'`（`pre==25 && cur==0`），别漏掉。
  - 用 `max` 保留每个结尾字符的最长延伸，不能直接累加每次的 `len`（会重复计数）。
- **代码**：

```cpp
int findSubstringInWraproundString(string str) {
    int n = str.length();
    for (int i = 0; i < n; i++) s[i] = str[i] - 'a';
    memset(dp, 0, sizeof(dp));
    dp[s[0]] = 1;
    for (int i = 1, cur, pre, len = 1; i < n; i++) {
        cur = s[i];
        pre = s[i - 1];
        if ((pre == 25 && cur == 0) || pre + 1 == cur) len++;
        else len = 1;
        dp[cur] = max(dp[cur], len);
    }
    int ans = 0;
    for (int i = 0; i < 26; i++) ans += dp[i];
    return ans;
}
```

---

## 题目8：不同的子序列 II

- **测试链接**：https://leetcode.cn/problems/distinct-subsequences-ii/
- **题面**：给定字符串 `s`，求不同非空子序列的个数，对 `10^9+7` 取模。数据量 `s.length ≤ 2000`。
- **核心思路**：增量构造 + 按结尾字符去重。
  - 维护 `all` = 当前所有不同子序列个数（含空序列，初始 1）；`cnt[x]` = 以字符 `x` 结尾的不同子序列个数。
  - 遍历字符 `x`：新增的子序列 = 「在之前所有子序列后面接上 `x`」− 「以 `x` 结尾的旧子序列」（它们接上 `x` 后与旧结果重复）。
  - 即 `newAdd = all - cnt[x]`（取模要 `+mod` 保证非负）；然后 `cnt[x] += newAdd`，`all += newAdd`。
  - 最终答案是 `all - 1`（去掉空序列）。
- **坑点**：
  - 减法取模要 `(all - cnt[x] + mod) % mod` 防负数。
  - 最终答案 `all - 1` 也可能为负，同样要 `+mod` 再取模。
- **代码**：

```cpp
int distinctSubseqII(string s) {
    int mod = 1000000007;
    memset(cnt, 0, sizeof(cnt));
    int all = 1, newAdd;
    for (char x : s) {
        newAdd = (all - cnt[x - 'a'] + mod) % mod;
        cnt[x - 'a'] = (cnt[x - 'a'] + newAdd) % mod;
        all = (all + newAdd) % mod;
    }
    return (all - 1 + mod) % mod;
}
```

---

## 本节小结

1. **动态规划 = 用空间代替重复计算**。任何 DP 一定对应一个有重复调用行为的递归，都可以从递归入手逐步改出。
2. **尝试策略 = 转移方程**。新手/难题先写递归尝试，再改记忆化 → 严格位置依赖 → 空间压缩，逐步推进、容易 debug。
3. 题目 1~4 是「从递归到 DP」的标准四步（暴力 → 记忆化 → 严格位置依赖 → 空间压缩）；题目 5~8 是「直接 DP 视角」的经典模型（三指针归并、结尾位置依赖、按结尾字符去重、增量构造去重）。
