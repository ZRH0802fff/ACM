# class085 数位DP（下）笔记

> 视频链接：https://www.bilibili.com/video/BV1uC4y1Q72c/
> 前置知识：位运算基础（class030-033）、动态规划基础（class066起）、数位DP上期（class084）

---

## 题目1：Windy数

### 题面
给定正整数 a、b，定义 **windy 数**为「不含前导零，且任意两个相邻数字之差至少为 2」的正整数。返回 [a, b] 范围上 windy 数的个数。

- 测试链接：https://www.luogu.com.cn/problem/P2657
- 例：164 是 windy 数（|1-6|=5、|6-4|=2），100 不是

### 核心思路
大思路与上期一致：`compute(a,b) = cnt(b) - cnt(a-1)`，只需求出 `cnt(num)` = 0~num 范围上 windy 数个数。

**递归 f(num, offset, len, pre, free)**，关键状态只有后三个：
- `len`：从高位开始，还剩下几位没决定
- `pre`：前一位数字；**`pre == 10` 表示从没选过数字**（与「选了 0」是两回事，因为 0 会影响后一位能否选 1）
- `free`：之前位是否已确定比 num 小（1=自由选，0=受 num 限制）

分支（对照代码逐条展开）：
1. `free==0 && pre==10` → 来到 num 最高位：
   - 当前位「一个数字也不要」→ `f(..., 10, 1)`（位数变少，注定比 num 小）
   - 选 `1..cur-1` → 都比 cur 小，free=1
   - 选 `cur` → 与 num 相同，free=0
2. `free==0 && pre!=10` → 之前选过数字、且与 num 相同：遍历 `0..9`，需满足 `i<=pre-2 || i>=pre+2`（相邻差≥2），再分 `i<cur`（free=1）与 `i==cur`（free=0）
3. `free==1 && pre==10` → 已确定比 num 小、且没选过数字：仍可「不选数字」，或选 `1..9`
4. `free==1 && pre!=10` → 已确定比 num 小、且选过数字：遍历 `0..9` 满足 `|i-pre|>=2`，全部 free=1

- 复杂度：O(len × 11 × 2 × 10)（pre 有 0~9 加一个 10 共 11 种取值）

### 坑点
- `num == 0` 需特判返回 1（0 自身是 windy 数）
- `pre == 10`（没选过）与「选 0」完全不同，前者后续首位可自由选 1~9，后者会限制后一位不能选 1
- offset 由 len 完全决定（上节课内容），不是关键参数

### 代码
```cpp
int f(int num, int offset, int len, int pre, int free) {
    if (len == 0) return 1;
    if (dp[len][pre][free] != -1) return dp[len][pre][free];
    int cur = num / offset % 10;
    int ans = 0;
    if (free == 0) {
        if (pre == 10) {
            ans += f(num, offset / 10, len - 1, 10, 1); // 一个数字也不要
            for (int i = 1; i < cur; i++)
                ans += f(num, offset / 10, len - 1, i, 1);
            ans += f(num, offset / 10, len - 1, cur, 0);
        } else {
            for (int i = 0; i <= 9; i++) {
                if (i <= pre - 2 || i >= pre + 2) {
                    if (i < cur)      ans += f(num, offset / 10, len - 1, i, 1);
                    else if (i == cur) ans += f(num, offset / 10, len - 1, cur, 0);
                }
            }
        }
    } else {
        if (pre == 10) {
            ans += f(num, offset / 10, len - 1, 10, 1);
            for (int i = 1; i <= 9; i++)
                ans += f(num, offset / 10, len - 1, i, 1);
        } else {
            for (int i = 0; i <= 9; i++)
                if (i <= pre - 2 || i >= pre + 2)
                    ans += f(num, offset / 10, len - 1, i, 1);
        }
    }
    return dp[len][pre][free] = ans;
}
```

> 加强版（02_Windy数加强版.cpp）只是把 `int` 换成 `long long`、`MAXLEN` 改为 21，逻辑完全相同。

---

## 题目2：萌数

### 题面
定义 **萌数** 为「存在长度至少为 2 的回文子串」的数字（如 101、110、111、1234321、45568）。给定 l、r（可能高达 1000 位，需用字符串），返回 [l, r] 范围上萌数的个数，答案对 1e9+7 取模。

- 测试链接：https://www.luogu.com.cn/problem/P3413

### 核心思路
**大策略**：l、r 是超长字符串，无法直接算 `l-1`（有借位）。改为：
```
ans = cnt(r) - cnt(l) + (check(l) ? 1 : 0)
```
即求 `0~r` 与 `0~l` 的萌数个数之差，再单独验证 l 自身是不是萌数，是则补加 1。

**正难则反**：萌数 = 总数 − 非萌数。
- **总数**：把字符串 num 表达的数值对 MOD 取余（同余原理，逐位 `all = (all*10 + num[i]) % MOD`）
- **非萌数**：满足「每位 i 都和 i-1、i-2 不同」——因为萌数等价于存在某位 `num[i]==num[i-1]` 或 `num[i]==num[i-2]`

**递归 f(num, i, pp, p, free)**：
- `i`：当前第几位（从高位 0 开始）
- `p`：前一位数字，`10` 表示没选过
- `pp`：前前一位数字，`10` 表示没选过
- `free`：之前位是否已确定比 num 小

分支结构与 windy 数几乎一样，只是每次选择都多校验「与 pp、p 都不同」这一限制：
- `free==0 && p==10`：最高位。可不选数字，或选 `1..cur-1`（free=1），或选 `cur`（free=0，但需 `pp!=cur && p!=cur`）
- `free==0 && p!=10`：之前选过数字且与 num 相同，遍历 `0..cur-1` 中 `pp!=cur && p!=cur` 的（free=1），以及 `cur` 若合法则 free=0
- `free==1 && p==10`：自由且没选过，可不选数字或选 `1..9`
- `free==1 && p!=10`：自由且选过，遍历 `0..9` 中 `pp!=cur && p!=cur` 的

**check(l)**：线性扫一遍，若某位与 i-1 或 i-2 相同即返回 true。

- 复杂度：O(N × 11 × 11 × 2 × 10)，N=1000，约 10⁷~10⁸，稳过

### 坑点
- 答案每一步都要取模，减法用 `(ans - f() + MOD) % MOD` 防负数
- `num[0] == '0'`（即整个字符串是 "0"）需特判返回 0
- 每次调用 cnt 前都要 `build` 重置 dp 表
- 输入保证无前导零

### 代码
```cpp
int f(string& num, int i, int pp, int p, int free) {
    if (i == (int)num.length()) return 1;
    if (dp[i][pp][p][free] != -1) return dp[i][pp][p][free];
    int ans = 0;
    if (free == 0) {
        if (p == 10) {
            ans = (ans + f(num, i + 1, 10, 10, 1)) % MOD; // 当前位不选数字
            for (int cur = 1; cur < num[i] - '0'; cur++)
                ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
            ans = (ans + f(num, i + 1, p, num[i] - '0', 0)) % MOD;
        } else {
            for (int cur = 0; cur < num[i] - '0'; cur++)
                if (pp != cur && p != cur)
                    ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
            if (pp != num[i] - '0' && p != num[i] - '0')
                ans = (ans + f(num, i + 1, p, num[i] - '0', 0)) % MOD;
        }
    } else {
        if (p == 10) {
            ans = (ans + f(num, i + 1, 10, 10, 1)) % MOD;
            for (int cur = 1; cur <= 9; cur++)
                ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
        } else {
            for (int cur = 0; cur <= 9; cur++)
                if (pp != cur && p != cur)
                    ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
        }
    }
    return dp[i][pp][p][free] = ans;
}

int cnt(string& num) {
    if (num[0] == '0') return 0;
    int n = num.length();
    long long all = 0, base = 1;
    for (int i = n - 1; i >= 0; i--) {
        all = (all + base * (num[i] - '0')) % MOD;
        base = (base * 10) % MOD;
    }
    build(n);
    return (int)((all - f(num, 0, 10, 10, 0) + MOD) % MOD);
}
```

---

## 题目3：二进制没有连续1的数字个数

### 题面
给定正整数 n，统计 [0, n] 范围的非负整数中，二进制表示不存在连续 1 的整数个数。

- 测试链接：https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/
- 例：n=5 → 5（0、1、2、4、5），3（二进制 11）含连续 1 不算

### 核心思路
**辅助表 cnt[len]**：二进制有 len 位、自由填、不含连续 1 的状态个数。
- 递推：最高位填 0 → 剩 len-1 位自由；最高位填 1 → 次高位必须填 0，剩 len-2 位自由
- 故 `cnt[len] = cnt[len-1] + cnt[len-2]`（斐波那契），初始 `cnt[0]=1`（空串）、`cnt[1]=2`（0、1）
- n 是正整数，第 31 位符号位必为 0，所以只打表到 cnt[30] 即可

**递归 f(num, i)**（i 从 30 往 0，前缀始终与 num 完全一样）：
- `i == -1` → return 1（num 自身合法，一路跟到底未违规）
- 若 num 第 i 位为 1：
  - 该位填 0，后面 i 位自由填 → 直接结算 `ans += cnt[i]`
  - 若更高位（i+1）也是 1 → 出现连续 1，前缀不可能再合法，提前 return
  - 否则递归 `f(num, i-1)`（该位填 1，与 num 相同）
- 若 num 第 i 位为 0：只能填 0，直接递归 `f(num, i-1)`

**方法二**：因为这是「单决策」递归（要么结算、要么只往下一层），可等义改写为迭代：从 30 往 -1 遍历，遇到 1 累加 cnt[i]，遇连续两个 1 提前 break，走到 -1 时 ans++。

- 复杂度：O(30)，等效 O(1)

### 坑点
- 连续两个 1 时提前 return/break，不再累加也不递归
- 递归能走到 `i==-1` 说明 num 自身合法，必须返回 1
- cnt 表只需生成 0~30

### 代码（方法一）
```cpp
int f(int num, int i) {
    if (i == -1) return 1; // num自身合法
    int ans = 0;
    if ((num & (1 << i)) != 0) {
        ans += cnt[i];
        if ((num & (1 << (i + 1))) != 0) {
            return ans; // 连续两个1，提前结束
        }
    }
    ans += f(num, i - 1);
    return ans;
}
```

### 代码（方法二 · 迭代）
```cpp
int findIntegers2(int n) {
    cnt[0] = 1; cnt[1] = 2;
    for (int len = 2; len <= 30; len++)
        cnt[len] = cnt[len - 1] + cnt[len - 2];
    int ans = 0;
    for (int i = 30; i >= -1; i--) {
        if (i == -1) { ans++; break; }
        if ((n & (1 << i)) != 0) {
            ans += cnt[i];
            if ((n & (1 << (i + 1))) != 0) break;
        }
    }
    return ans;
}
```

---

## 题目4：范围内位上计数

### 题面
给定正整数 a、b（均 ≥1）和数码 d，求 [a, b] 范围上所有整数中，数码 d 一共出现了多少次。

- 测试链接（三个，同一算法）：
  - https://leetcode.cn/problems/digit-count-in-range/
  - https://www.luogu.com.cn/problem/P2602（求每个数码 0~9 各出现多少次）
  - https://leetcode.cn/problems/number-of-digit-one/（只统计 1）
- 例：10~100 中数码 5 出现次数（15、25、35、45、55 计 2 次、65、75、85、95）……

### 核心思路
大思路：`count(b, d) - count(a-1, d)`，其中 `count(num, d)` 统计 **1~num**（不是 0~num）范围内 d 的出现次数。

**逐位统计**：分别统计个位、十位、百位……上 d 出现的次数，累加。对当前位维护三个量：
- `left`：当前位「左边」的情况数（前缀股数）
- `right`：当前位「右边」的情况数（后缀自由变化数，随循环 ×10 增长）
- `cur`：当前位的数字

按 cur 与 d 的大小关系分三种情况（以 1~30583、d=5 为例）：
1. `cur < d`：前缀只能取 `0..3057`（即 left 股），右边固定
2. `cur > d`：前缀可取 `0..304`（left 股）再乘 right，另外当前位自身还能再凑一股（前缀=305），额外加 right
3. `cur == d`：前缀 left 股 × right，另外前缀=当前前缀时，右边只能取 `0..(num%right)`，额外加 `num % right + 1`

统一公式：
```
ans += left * right;
if (cur > d)      ans += right;
else if (cur == d) ans += num % right + 1;
```

**d == 0 的特殊处理**：因为统计范围是 1~num（从 1 开始），当前位填 0 时，其高位前缀不能全为 0（否则这个数根本没有这一位）。所以 `left--`。

三个题目只是外层差异：05 求单个 d；06 求 0~9 全部（用 long long 防溢出，循环跑 10 次）；07 只求 d=1。

- 复杂度：O(num 的位数)

### 坑点
- 范围是 **1~num**，不是 0~num，所以 `d==0` 时 `left` 要减 1
- `cur == d` 时加的是 `num % right + 1`（含 0 这一股），不要漏 +1
- 循环条件 `tmp != 0`，right 随 `tmp /= 10` 逐步 ×10

### 代码
```cpp
int count(int num, int d) {
    int ans = 0;
    // left : 当前位左边的情况数
    // right : 当前位右边的情况数
    // cur : 当前位的数字
    for (int right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        cur = tmp % 10;
        if (d == 0) left--;
        ans += left * right;
        if (cur > d)       ans += right;
        else if (cur == d) ans += num % right + 1;
    }
    return ans;
}
```

---

## 数位DP总结（下期核心）

- **可能性展开是核心**：把递归每一种分支（是否选数字、是否 free、与 num 当前位相等/小于）全部列出来，代码反而最好写，不需要复杂化简。
- **常见状态**：`len`（剩几位）、`pre`（前一位，`10` 表示从没选过数字）、`free`（是否已确定比 num 小）、`pp`（前前一位）。
- **pre/pp 用 10 表示「没选过数字」**：与「选了 0」是两回事，前者后续首位可 1~9，后者会限制下一位。
- **大数用字符串**：位数超 long long 时用字符串 + 同余原理逐位取模；求范围改用 `cnt(r)-cnt(l)+check(l)` 绕开 `l-1` 借位。
- **正难则反**：萌数这类「存在…」的定义，常反过来求「不存在…」再补集。
- **预处理表加速结算**：排列组合表 / cnt[len] 表，把「自由填」的部分一次性结算掉，避免递归到底。
