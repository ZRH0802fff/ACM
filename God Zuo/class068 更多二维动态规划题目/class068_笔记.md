# class068 见识更多二维动态规划题目 笔记

> 视频：算法讲解068【必备】见识更多二维动态规划题目

---

## 题目1：不同的子序列

### 题面
给两个字符串 s 和 t，统计在 s 的**子序列**中 t 出现的次数（子序列可以不连续，但不能改变相对次序）。答案对 1000000007 取模。

- LeetCode 115: https://leetcode.cn/problems/distinct-subsequences/
- s、t 长度 ≤ 1000

### 核心思路
**二维 DP，从末尾字符讨论**：
- `dp[i][j]`：s 前缀长度为 i 的所有子序列中，等于 t 前缀长度为 j 的子序列数量
- 可能性1（不要 s[i-1]）：`dp[i][j] = dp[i-1][j]`，永远可以获得
- 可能性2（要 s[i-1]）：只有当 `s[i-1] == t[j-1]` 时，`dp[i][j] += dp[i-1][j-1]`
- 初始：`dp[i][0] = 1`（t 为空串，空子序列即可匹配），`dp[0][j>0] = 0`
- 每个格子依赖**上方**和**左上角**，从左往右、从上往下填即可

### 坑点
- 用 `unsigned long long` 防溢出，取模版用 `int` + `mod = 1000000007`
- 空间压缩：从右往左更新（因为依赖左上角），`dp[0]=1`

### 代码
```cpp
// s、t 的长度 <= 1000
const int MAXN = 1001;
const int MAXM = 1001;

unsigned long long dp[MAXN][MAXM];
unsigned long long dp1D[MAXM];
int dpMod[MAXM];

class Solution {
public:
    // 普通动态规划
    // dp[i][j] : s[前缀长度为i]的所有子序列中，有多少个子序列等于t[前缀长度为j]
    int numDistinct1(string str, string target) {
        int n = str.length();
        int m = target.length();
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = dp[i - 1][j];
                if (str[i - 1] == target[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        return (int)dp[n][m];
    }

    // 空间压缩
    int numDistinct2(string str, string target) {
        int n = str.length();
        int m = target.length();
        memset(dp1D, 0, sizeof(dp1D));
        dp1D[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (str[i - 1] == target[j - 1]) {
                    dp1D[j] += dp1D[j - 1];
                }
            }
        }
        return (int)dp1D[m];
    }

    // 本题说了要取模，所以增加取模的逻辑
    int numDistinct(string str, string target) {
        int mod = 1000000007;
        int n = str.length();
        int m = target.length();
        memset(dpMod, 0, sizeof(dpMod));
        dpMod[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (str[i - 1] == target[j - 1]) {
                    dpMod[j] = (dpMod[j] + dpMod[j - 1]) % mod;
                }
            }
        }
        return dpMod[m];
    }
};
```

---

## 题目2：编辑距离

### 题面
给定两个单词 word1 和 word2，每次可以**插入**（代价 a）、**删除**（代价 b）、**替换**（代价 c）一个字符。求将 word1 转化成 word2 的最小代价。

- LeetCode 72（特例：a=b=c=1）: https://leetcode.cn/problems/edit-distance/
- word1、word2 长度 ≤ 500

### 核心思路
**二维 DP，从末尾字符分类讨论**：

- `dp[i][j]`：s1 前缀长度为 i 变成 s2 前缀长度为 j 的最小代价
- 原初尝试版把「s1 最后一个字符是否参与变换」分成四大可能性：
  - p1（相等才成立）：`dp[i-1][j-1]`
  - p2（不等才成立）：`dp[i-1][j-1] + c`（替换）
  - p3：`dp[i][j-1] + a`（插入 s2 最后一个字符）
  - p4：`dp[i-1][j] + b`（删除 s1 最后一个字符）
- 小优化：若 `s1[i-1] == s2[j-1]`，直接保留 `dp[i][j] = dp[i-1][j-1]`；否则三种操作取 min
- 初始：`dp[i][0] = i*b`，`dp[0][j] = j*a`
- 依赖**左**、**上**、**左上**三个格子

### 坑点
- 相等时有小贪心：直接 `dp[i-1][j-1]`，其他操作一定不优于保留
- 空间压缩用 `leftUp` 变量滚过去保留左上角值
- 这是通用版（a/b/c 可变），LeetCode 上是 a=b=c=1 的特例

### 代码
```cpp
// word1、word2 的长度 <= 500
const int MAXN = 501;
const int MAXM = 501;

int dp[MAXN][MAXM];
int dp1D[MAXM];

class Solution {
public:
    // LeetCode 入口：插入、删除、替换代价均为 1
    int minDistance(string word1, string word2) {
        return editDistance2(word1, word2, 1, 1, 1);
    }

    // 原初尝试版
    // a : str1中插入1个字符的代价
    // b : str1中删除1个字符的代价
    // c : str1中改变1个字符的代价
    // 返回从str1转化成str2的最低代价
    int editDistance1(string str1, string str2, int a, int b, int c) {
        int n = str1.length();
        int m = str2.length();
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; j++) {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int p1 = INT_MAX;
                if (str1[i - 1] == str2[j - 1]) {
                    p1 = dp[i - 1][j - 1];
                }
                int p2 = INT_MAX;
                if (str1[i - 1] != str2[j - 1]) {
                    p2 = dp[i - 1][j - 1] + c;
                }
                int p3 = dp[i][j - 1] + a;
                int p4 = dp[i - 1][j] + b;
                dp[i][j] = min(min(p1, p2), min(p3, p4));
            }
        }
        return dp[n][m];
    }

    // 枚举小优化版
    int editDistance2(string str1, string str2, int a, int b, int c) {
        int n = str1.length();
        int m = str2.length();
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; j++) {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(min(dp[i - 1][j] + b, dp[i][j - 1] + a), dp[i - 1][j - 1] + c);
                }
            }
        }
        return dp[n][m];
    }

    // 空间压缩
    int editDistance3(string str1, string str2, int a, int b, int c) {
        int n = str1.length();
        int m = str2.length();
        memset(dp1D, 0, sizeof(dp1D));
        for (int j = 1; j <= m; j++) {
            dp1D[j] = j * a;
        }
        for (int i = 1, leftUp, backUp; i <= n; i++) {
            leftUp = (i - 1) * b;
            dp1D[0] = i * b;
            for (int j = 1; j <= m; j++) {
                backUp = dp1D[j];
                if (str1[i - 1] == str2[j - 1]) {
                    dp1D[j] = leftUp;
                } else {
                    dp1D[j] = min(min(dp1D[j] + b, dp1D[j - 1] + a), leftUp + c);
                }
                leftUp = backUp;
            }
        }
        return dp1D[m];
    }
};
```

---

## 题目3：交错字符串

### 题面
给定 s1、s2、s3，判断 s3 是否由 s1 和 s2 **交错组成**（保持各自相对次序，可随意穿插）。类似洗扑克牌。

- LeetCode 97: https://leetcode.cn/problems/interleaving-string/
- s1、s2 长度 ≤ 100，s3 长度 ≤ 200

### 核心思路
**二维 DP，讨论 s3 最后一个字符来自谁**：
- 前提：`len(s1)+len(s2) == len(s3)`，否则直接 false
- `dp[i][j]`：s1 前缀 i 个 + s2 前缀 j 个，能否交错出 s3 前缀 i+j 个
- 转移：
  - s3 最后字符来自 s1：`s1[i-1]==s3[i+j-1] && dp[i-1][j]`
  - s3 最后字符来自 s2：`s2[j-1]==s3[i+j-1] && dp[i][j-1]`
  - 两者或关系
- 初始：`dp[0][0]=true`，第 0 行/第 0 列看单字符串与 s3 的前缀是否匹配
- 每个格子依赖**左**和**上**，类似最小路径和

### 坑点
- 这是常见错误做法：三指针外排（遇到相同字符不知选哪个）
- 必须先检查总长度是否匹配

### 代码
```cpp
// s1、s2 的长度 <= 100，s3 的长度 <= 200
const int MAXN = 101;
const int MAXM = 101;

bool dp[MAXN][MAXM];
bool dp1D[MAXM];

class Solution {
public:
    // 普通动态规划
    bool isInterleave1(string str1, string str2, string str3) {
        if (str1.length() + str2.length() != str3.length()) {
            return false;
        }
        int n = str1.length();
        int m = str2.length();
        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) {
            if (str1[i - 1] != str3[i - 1]) {
                break;
            }
            dp[i][0] = true;
        }
        for (int j = 1; j <= m; j++) {
            if (str2[j - 1] != str3[j - 1]) {
                break;
            }
            dp[0][j] = true;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = (str1[i - 1] == str3[i + j - 1] && dp[i - 1][j])
                        || (str2[j - 1] == str3[i + j - 1] && dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }

    // 空间压缩
    bool isInterleave(string str1, string str2, string str3) {
        if (str1.length() + str2.length() != str3.length()) {
            return false;
        }
        int n = str1.length();
        int m = str2.length();
        memset(dp1D, false, sizeof(dp1D));
        dp1D[0] = true;
        for (int j = 1; j <= m; j++) {
            if (str2[j - 1] != str3[j - 1]) {
                break;
            }
            dp1D[j] = true;
        }
        for (int i = 1; i <= n; i++) {
            dp1D[0] = str1[i - 1] == str3[i - 1] && dp1D[0];
            for (int j = 1; j <= m; j++) {
                dp1D[j] = (str1[i - 1] == str3[i + j - 1] && dp1D[j])
                       || (str2[j - 1] == str3[i + j - 1] && dp1D[j - 1]);
            }
        }
        return dp1D[m];
    }
};
```

---

## 题目4：有效涂色问题

### 题面
n 个格子，m 种颜色。每个格子涂一种颜色。当涂满 n 个格子后，m 种颜色**都使用了**，称为一种有效方法。求有效方法数，结果对 1000000007 取模。n, m ≤ 5000。

- 无在线测试，对数器验证

### 核心思路
**二维 DP，分开辟新颜色和不开辟两种情况**：
- `dp[i][j]`：前 i 个格子涂了 j 种颜色的方法数
- 不开辟新颜色：前 i-1 格已凑齐 j 种，第 i 格复用 j 种之一 → `dp[i-1][j] * j`
- 开辟新颜色：前 i-1 格只有 j-1 种，第 i 格选一种新颜色 → `dp[i-1][j-1] * (m-(j-1))`
- `dp[i][j] = dp[i-1][j]*j + dp[i-1][j-1]*(m-j+1)`
- 初始：`dp[i][1] = m`（任意一行，只能凑一种颜色就是 m 种选法）
- 依赖**上方**和**左上角**

### 坑点
- 中间乘法可能超 int，需用 `long long` 中转再取模
- 注意 `m-j+1` 表示剩余可选颜色数

### 代码
```cpp
const int MOD = 1000000007;
const int MAXN = 5001;

int dp[MAXN][MAXN];

// 正式方法
// 时间复杂度O(n * m)
int ways2(int n, int m) {
    // dp[i][j]:
    // 一共有m种颜色
    // 前i个格子涂满j种颜色的方法数
    for (int i = 1; i <= n; i++) {
        dp[i][1] = m;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            dp[i][j] = (int)(((long long)dp[i - 1][j] * j) % MOD);
            dp[i][j] = (int)((((long long)dp[i - 1][j - 1] * (m - j + 1)) + dp[i][j]) % MOD);
        }
    }
    return dp[n][m];
}
```

---

## 题目5：删除至少几个字符可以变成另一个字符串的子串

### 题面
给定 s1 和 s2，求 s1 至少删除多少个字符可以变成 s2 的**子串**（子串必须连续）。

- 无在线测试，对数器验证

### 核心思路
**二维 DP，定义很巧妙**：
- `dp[i][j]`：s1 前缀 i 个字符，至少删除多少个字符，能变成 s2 前缀 j 个字符的**任意后缀串**
- 若 `s1[i-1] == s2[j-1]`：保留，问题变为 `dp[i-1][j-1]`
- 若不等：删掉 s1[i-1]，`1 + dp[i-1][j]`
- 初始：`dp[i][0] = i`（s2 为空，删掉 s1 全部），`dp[0][j] = 0`（s1 为空天生是任意后缀串）
- 最终答案：**最后一行的最小值**（因为 s1 整体变成的可能是 s2 以任意位置结尾的后缀串）

### 坑点
- 返回值是 `min(dp[n][0..m])` 而非 `dp[n][m]`——因为变成的子串可能以 s2 任意位置结尾
- 依赖**上方**和**左上**，常规填表即可

### 代码
```cpp
const int MAXN = 1001;
const int MAXM = 1001;

int dp[MAXN][MAXM];

// 正式方法，动态规划
int minDelete2(string str1, string str2) {
    int n = str1.length();
    int m = str2.length();
    memset(dp, 0, sizeof(dp));
    // dp[len1][len2] :
    // s1[前缀长度为i]至少删除多少字符，可以变成s2[前缀长度为j]的任意后缀串
    for (int i = 1; i <= n; i++) {
        dp[i][0] = i;
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = dp[i - 1][j] + 1;
            }
        }
    }
    int ans = INT_MAX;
    for (int j = 0; j <= m; j++) {
        ans = min(ans, dp[n][j]);
    }
    return ans;
}
```
