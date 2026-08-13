# 左神算法课 Java → C++ 转换规范

> **使用说明**：将本文档放到任意电脑上，按下方「路径配置」章节设置好三个目录路径即可开始转换。

---

## 路径配置

使用前设置以下三个路径（替换为你本机的实际路径）：

| 变量 | 说明 | 示例 |
|---|---|---|
| `<JAVA_SRC>` | Java 源码根目录 | `D:\document\code document\zuo\src\` |
| `<CPP_OUT>` | C++ 输出根目录 | `D:\document\ACM\God Zuo\` |
| `<SUBTITLE_DIR>` | 字幕文件所在目录（通常为桌面） | `C:\Users\xxx\Desktop\` |

---

## 一、整体转换要求

### 1.1 核心原则

1. **大思路不变**：保持原有算法逻辑，多个版本的方法都保留（暴力递归、记忆化搜索、严格位置依赖DP、空间压缩）
2. **保留原注释**：Java 代码中的**所有注释必须完整保留**，一字不漏地搬到 C++ 中：
   - 开头的题目描述和测试链接
   - 状态/位图的图解示例（如 `1 1 1 0 1 0 1 1`）
   - 每个参数的含义说明
   - 关键步骤的行内注释（`// 考察所有数字，但是不能选择之前选了的数字`）
   - 算法名的标注（如 `// Brian Kernighan算法`、`// 记忆化搜索`）
   - **不能为了代码看起来简洁而删掉任何注释**

3. **竞赛风格头文件**：
   ```cpp
   #include <bits/stdc++.h>
   using namespace std;
   ```

4. **🔥 数组选择规则（最重要）**：

   **核心原则：Java 普通数组（无论 `static` 还是局部 `new int[n]`）→ C++ 全局静态数组；Java `ArrayList` → C++ `vector`。**

   | Java | C++ | 示例 |
   |---|---|---|
   | `static int[] indegree` | 全局 `int indegree[MAXN]` | 类级别静态数组 |
   | `static int[][] dp` | 全局 `int dp[MAXN][MAXM]` | DP 缓存表 |
   | 局部 `new int[n]` / `new int[n][m]` | 全局 `int a[MAXN]` / `int dp[MAXN][MAXM]` | 普通数组，运行时才知道大小就开比最大数据量稍大的全局数组 |
   | `static int[] father` | 全局 `int father[MAXN]` | 并查集 |
   | `static int[] head/next/to` | 全局 `int head[MAXN]` 等 | 链式前向星 |
   | `ArrayList<ArrayList<>>` | `vector<vector<int>>` | 动态数组（唯一用 vector 的地方） |
   | 局部 `int[] edges`（需排序） | 全局 `Edge edges[MAXM]` | C 数组无法 sort |

   **额外硬性规定（不受上述规则影响）**：
   - **拓扑排序的入度表和队列始终用全局静态数组**，即使 Java 是局部的：
     ```cpp
     int indegree[MAXN];
     int queue_[MAXN];
     int l, r;
     ```
   - LeetCode 函数签名中的 `vector<int>&` 传参保留，返回值可用 `vector<int>` 以匹配接口。

   **判断流程**：
   1. 先看 Java 源码：它是普通数组（`int[]` / `int[][]`）还是 `ArrayList`？
   2. 普通数组（无论 `static` 还是局部 `new`）→ C++ 全局静态数组
   3. `ArrayList` → C++ `vector`
   4. 普通数组需要排序 → 全局 `struct` 数组
   5. 拓扑 indegree/queue → 不管 Java 怎么写，一律全局

### 1.2 LeetCode 题目 vs 非 LeetCode 题目

**LeetCode 题目**（有测试链接的）：
- 解法放入 `class Solution`，主方法名匹配 LeetCode 提交要求
- 额外辅助方法作为 `public` 成员保留，或作为全局函数放在 class 前面
- `main()` 中写测试代码

```cpp
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/
#include <bits/stdc++.h>
using namespace std;

// 全局结构体/辅助函数放这里
struct Info { ... };
Info f(TreeNode* x) { ... }

class Solution {
public:
    // 主方法（匹配LeetCode接口签名）
    int numDistinct(string s, string t) { ... }

    // 额外版本也放 public
    int numDistinct2(string s, string t) { ... }
};

// 测试代码
int main() {
    Solution sol;
    cout << sol.numDistinct(s, t) << endl;
    return 0;
}
```

**非 LeetCode 题目**（无测试链接）：
- 保留原结构：全局函数 + 对数器 `main()`

```cpp
#include <bits/stdc++.h>
using namespace std;

// 全局函数
void swapXor(int arr[], int i, int j) {
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
}

int main() {
    // 对数器 + 测试代码
    int arr[] = {3, 5};
    swapXor(arr, 0, 1);
    cout << arr[0] << " " << arr[1] << endl;
    return 0;
}
```

---

## 二、文件与命名规则

### 2.1 文件夹组织

```
<CPP_OUT>/
├── class068 更多二维动态规划题目/
│   ├── 01_不同的子序列.cpp
│   ├── 02_编辑距离.cpp
│   ├── 03_交错字符串.cpp
│   ├── 04_有效涂色问题.cpp
│   ├── 05_最少删除成为子串.cpp
│   ├── class068_笔记.md
│   └── 算法讲解068.txt          ← 字幕文件移入
├── class069 三维动态规划/
│   ├── 01_一和零.cpp
│   ├── ...
├── class030 异或运算/
│   ├── 01_异或交换两数.cpp
│   ├── ...
```

### 2.2 文件夹命名规则

| 场景 | 命名方式 | 示例 |
|---|---|---|
| 已有 Python 版同名文件夹 | 原名称 + ` cpp版` | `class052 单调栈 cpp版/` |
| 全新转换（无同名文件夹） | `classXXX 课题名` | `class068 更多二维动态规划题目/` |

### 2.3 文件命名规则

- 格式：`<序号>_<中文描述>.cpp`
- **序号必须与 Java 源文件的 Code 编号一致**，如 Java 的 `Code02_TopoSortDynamicLeetcode.java` → C++ 的 `02_拓扑排序_Leetcode.cpp`
- **同一题有多个解时，使用相同序号**，如 Java 有 `Code02_TopoSortDynamicLeetcode.java` 和 `Code02_TopoSortStaticNowcoder.java`，C++ 对应 `02_拓扑排序_Leetcode.cpp` 和 `02_拓扑排序_牛客_静态.cpp`
- 序号用两位数：`01_`、`02_`、...
- 描述用简洁的中文题目名称

### 2.4 个人练习文件

- 每道题可另存一份 `My<序号>.cpp`，内容是对标答的默写/练习
- 转换脚本只生成 `01_xxx.cpp` 等标答文件，`MyXX.cpp` 由用户自行维护

---

## 三、C++ 化要点（语法对照表）

### 3.1 普通数组 — 一律用全局静态数组，不用 vector

这是最重要的规则。Java 的普通数组（`int[]` / `int[][]`，无论 `static` 还是局部 `new`）都转成 C++ 全局静态数组。

```cpp
// ❌ 错误：用 vector
vector<int> dp(n + 1, 0);
vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

// ✅ 正确：全局静态数组（定义在 #include 之后、class 之前）
const int MAXN = 505;
int dp[MAXN][MAXN];          // 自动零初始化
int dp1D[MAXN];

// 使用前按需初始化（如记忆化搜索需要 -1）
memset(dp, -1, sizeof(dp));
memset(dp, 0, sizeof(dp));  // 严格位置依赖的DP必须显式清零
```

**「不用 vector」的两个例外**：
1. Java 的 `ArrayList` → C++ `vector`
2. LeetCode 题目函数签名中的传参是 `vector`，保留以匹配接口（但自己实现的部分仍用全局数组）

```cpp
// ✅ 例外：接口本身就是 vector，保留
int missingNumber(vector<int>& nums) { ... }
int maxWidthRamp(vector<int>& nums) { ... }
```

**运行时才知道大小的处理**：提前开一个比最大数据量稍大的全局静态数组。

**函数需要返回数组的处理**：结果写入全局静态数组，调用方直接读，连传参都省了。

### 3.2 二维数组替换 — struct 替代 C 风格二维数组

C 风格二维数组 `int arr[MAXN][3]` 无法用 `std::sort`，用 struct 替代：

```cpp
// ❌ 不能直接用 sort
int arr[MAXN][3];
sort(arr, arr + n);  // 编译错误！

// ✅ 用 struct
struct Item {
    int a, b, c;
} arr[MAXN];

// struct 可赋值、可排序（需自定义比较器）
sort(arr, arr + n, [](const Item& x, const Item& y) {
    return x.a < y.a;
});
```

### 3.3 栈和队列 — 不用 STL，用数组模拟

```cpp
// ❌ 不用 STL
stack<int> stk;
queue<int> q;

// ✅ 用全局静态数组 + l/r 指针
const int MAXN = 50005;
int stk[MAXN];  // 栈
int r;          // 栈顶指针，r=0 表示空栈

// 压栈
stk[r++] = x;

// 弹栈
int top = stk[--r];

// 栈顶
int top = stk[r - 1];

// 判空
if (r == 0) { ... }
```

### 3.4 常用 Java → C++ 对照

| Java | C++ | 备注 |
|---|---|---|
| `Integer.MAX_VALUE` | `INT_MAX` | 需 `#include <climits>` / bits 已包含 |
| `Long.MAX_VALUE` | `LLONG_MAX` | |
| `Long.MIN_VALUE` | `LLONG_MIN` | |
| `Math.min(a, b)` | `std::min(a, b)` | |
| `Math.max(a, b)` | `std::max(a, b)` | |
| `Math.min(a, b, c)` | `std::min({a, b, c})` | 需 C++11 以上 |
| `Math.max(a, b, c)` | `std::max({a, b, c})` | |
| `s.toCharArray()` | `s[i]` 直接下标 | `string` 可直接下标访问 |
| `s2.contains(str)` | `s2.find(str) != string::npos` | |
| `Math.random()` | `rand() % N` | 种子：`srand(time(0))` |
| `System.currentTimeMillis()` | `chrono::steady_clock` | 用于计时 |
| `new int[n][n]`（默认全0） | `int arr[MAXN][MAXN]`（全局自动零初始化） | 局部/类成员数组需 `memset` |
| `long` | `long long` | 防溢出 |
| `s.length()` | `s.length()` 或 `s.size()` | string 两者等价 |
| `arr.length` | `sizeof(arr)/sizeof(arr[0])` 或直接用 `n` | 全局数组一般配合常量 `MAXN` |

### 3.5 取模操作

```cpp
const int MOD = 1000000007;

// 加法取模
dp[j] = (dp[j] + dp[j - 1]) % MOD;

// ⚠️ 注意：中间结果可能超 int，必要时用 long long
long long temp = (long long)a * b % MOD;
```

---

## 四、代码结构模板

### 4.1 LeetCode 题目模板（有全局数组）

```cpp
// <题目描述>
// 测试链接 : https://leetcode.cn/problems/xxxxx/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
int dp[MAXN][MAXN];
int dp1D[MAXN];

class Solution {
public:
    // 暴力尝试
    int solve1(string s) { ... }

    // 记忆化搜索
    int solve2(string s) { ... }

    // 严格位置依赖的动态规划
    int solve3(string s) { ... }

    // 空间压缩（最终提交版，方法名匹配LeetCode）
    int solve(string s) { ... }
};

int main() {
    Solution sol;
    cout << sol.solve("test case") << endl;
    return 0;
}
```

### 4.2 非 LeetCode 题目模板

```cpp
// <题目描述>

#include <bits/stdc++.h>
using namespace std;

// 全局数组
const int MAXN = 100005;
int arr[MAXN];

// 核心函数
int solve(int n) { ... }

// 对数器/测试
int main() {
    // 随机测试 or 手动测试
    return 0;
}
```

---

## 五、编译与运行

### 5.1 编译命令

```bash
g++ -std=c++14 -O2 -o test.exe file.cpp && ./test.exe
```

> **MinGW GCC 8.1.0 注意**：`bits/stdc++.h` 在 `-std=c++17` 下有 bug（`<filesystem>` 编译失败），用 `-std=c++14` 解决。
> Linux / 新版编译器（GCC 9+）无此问题，也可以用 `-std=c++17`。

### 5.2 验证要求

- 每个 cpp 文件写完**必须编译并运行**，确保输出与预期一致
- **不能只编译不跑** — 运行时错误（如数组越界、未初始化）编译期发现不了

### 5.3 类成员数组未初始化陷阱

```cpp
// ⚠️ C++ 类成员数组不会自动零初始化！
// Java 的 new int[n][n] 默认全0，但 C++ 类里的 int dp[MAXN][MAXN] 是垃圾值

// ✅ 严格位置依赖的 DP 方法开头必须加：
memset(dp, 0, sizeof(dp));

// 否则 DP 依赖的零值边界（如 dp[l][l-1] 跨边界访问依赖零值）
// 会是垃圾值，导致结果错误
```

---

## 六、笔记生成流程

每次转换完一个 class 的代码后，生成 `classXXX_笔记.md`：

### 6.1 步骤

1. 在 `<SUBTITLE_DIR>` 找到对应字幕文件（命名如 `算法讲解030【必备】异或运算的骚操作.txt` 或 `class072.txt`）
2. 结合生成的 cpp 代码 + 字幕内容生成笔记
3. 笔记保存到 `<CPP_OUT>/<class目录>/classXXX_笔记.md`
4. 将字幕文件从 `<SUBTITLE_DIR>` **移动**到 `<CPP_OUT>/<class目录>/`，原位置删掉

### 6.2 笔记格式（每道题四个部分）

- **题面**：用简短的话提炼题目信息，说清楚输入输出和限制条件
- **核心思路**：推理过程、关键灵感、转移方程的推导
- **坑点**：易错点、边界条件、特例判断
- **代码**：贴上 cpp 文件中核心解法的代码（不需要 main 测试部分、不需要暴力对数器）

---

## 附录 A：已转换 class 一览

| class | 课题 | 题目数 | 备注 |
|---|---|---|---|
| class030 | 异或运算 | 6 | |
| class031 | 位运算 | 6 | |
| class032 | 位图 | 2 | |
| class033 | 位运算实现加减乘除 | 1 | |
| class068 | 更多二维动态规划题目 | 5 | |
| class069 | 三维动态规划 | 5 | |
| class076 | 区间DP（上） | 6 | |
| class077 | 区间DP（下） | 6 | |
| class078 | 树型DP | 7 | |
| class079 | 树型DP和树上背包 | 6 | |
| class086 | 动态规划中得到具体决策方案的技巧 | 4 | |
| class087 | 动态规划中根据数据量猜解法的技巧 | 4 | |

> 完成新 class 的转换后，在此表添加一行记录。

---

## 附录 B：快速检查清单

转换完成后，逐项确认：

- [ ] `#include <bits/stdc++.h>` + `using namespace std;`
- [ ] Java 所有注释完整保留
- [ ] 普通数组全部替换为全局静态数组（`ArrayList` 和接口参数除外）
- [ ] 类成员数组已 `memset`
- [ ] STL 栈/队列替换为数组模拟
- [ ] C 风格多维数组改为 struct
- [ ] `Integer.MAX_VALUE` → `INT_MAX`
- [ ] `long` → `long long`
- [ ] 文件放入正确的 class 文件夹，命名 `01_汉语描述.cpp`
- [ ] `g++ -std=c++14 -O2` 编译通过
- [ ] 运行输出正确
- [ ] 笔记已生成，字幕已归档
