# class117 倍增算法和ST表

> 前置知识：二进制基础（讲解003）、二分搜索（讲解006）、辗转相除法求最大公约数（讲解041）、动态规划基础（讲解066~069）。
> 树上倍增与 LCA 在讲解118 开始讲述，本节是倍增和 ST 表（稀疏表）的基础。

---

## 一、两个小问题（位运算基础）

### 题面

1. 给定正数 `x`，已知用 `m` 个二进制位一定能表示 `x`，从高位到低位打印 `x` 每一位的状态（是 1 还是 0）。
2. 给定正数 `x`，打印 `≤x` 最大的 2 的幂，是 2 的几次方。

### 核心思路

1. 从第 `m-1` 位到第 0 位，用 `1 << p` 去试减：减得动则这一位是 1（`t -= 1<<p`），减不动则是 0。本质就是贪心地把 `x` 从高位向低位分解成二进制。
2. 找 `≤x` 最大的 2 的幂：用 `while ((1 << power) <= (x >> 1)) power++;`，即用「当前 2 的幂是否 ≤ x/2」来判断能否安全翻倍。

### 坑点

- 问题 2 的朴素写法 `while ((1 << power) <= x) power++; power--;` **没有考虑溢出**：当 `x` 逼近 `INT_MAX` 时，`1 << power` 会溢出成负数导致死循环。必须改用 `(1 << power) <= (x >> 1)` 的防溢出写法。

### 代码

```cpp
void show1(int x, int m) {
    for (int p = m - 1, t = x; p >= 0; p--) {
        if ((1 << p) <= t) {
            t -= 1 << p;
            cout << x << "的第" << p << "位是1\n";
        } else {
            cout << x << "的第" << p << "位是0\n";
        }
    }
}

void show2(int x) {
    int power = 0;
    // 防止溢出的写法
    while ((1 << power) <= (x >> 1)) {
        power++;
    }
    cout << "<=" << x << "最大的2的幂，是2的" << power << "次方\n";
}
```

---

## 二、国旗计划（倍增 + 覆盖环）

### 题面

给定 `m` 个点（编号 1~m）围成一个环，i 号点顺时针到达 i+1 号点，m 号点顺时针回到 1 号点。给定 `n` 条线段 `(a,b)` 表示从点 a 顺时针到点 b。输入保证所有线段能覆盖整个环，且每条线段不会完全在另一条线段内部（可能有重合但互不包含）。返回长度 n 的结果数组 `ans`，`ans[x]` 表示**一定选 x 号线段**的情况下，至少选几条线段能覆盖整个环。

测试链接：https://www.luogu.com.cn/problem/P4155

### 核心思路

1. **环拆成数轴**：把环复制成 2 倍长的数轴。若线段左边界 > 右边界（跨越了 m→1），把右边界 `+= m` 修正。
2. **排序 + 克隆**：按左边界对线段排序，再克隆一份（左右边界各 `+= m`），得到 `e = 2n` 条线段，编号复用原编号。
3. **定义"跳一步"**：每条线段跳一步能到达的最右线段 = 右边界以内、左边界最靠右的那条线段（因为线段互不包含，最靠右的开头一定蹦得最远）。用双指针 `arrive`（不回退）一次求出所有 `stjump[i][0]`。
4. **倍增建表**：`stjump[i][p] = stjump[stjump[i][p-1]][p-1]`，`power = log2(n)` 决定列数。
5. **求答案**：对每条线段 i，目标 `aim = 左边界 + m`（转一圈回到自己），从高位到低位枚举，只要 `stjump[cur][p]` 的右边界 `< aim` 就跳（累加 `1<<p` 步），最后 `ans = 跳的步数 + 1 + 1`（+1 是起始线段本身，+1 是最后一步补到覆盖）。

### 坑点

- 线段 3 个信息需要 `struct Line { id, l, r }`，因为要 `sort`（C 风格 `int[m][3]` 不能直接 sort）。
- 先修正「左 > 右」再排序；克隆要在排序之后做，且克隆后天然仍有序。
- 总线段数是 `2n`，ST 表列数由 `power = log2(n)` 决定（跳的步数不会超过 n）。
- `jump` 里的 `next != 0` 判断依赖 `stjump` 全局零初始化，0 表示"空"。

### 代码

```cpp
const int MAXN = 200001;
const int LIMIT = 18;

int power;

// 每条线段3个信息 : 线段编号、线段左边界、线段右边界
struct Line {
    int id, l, r;
};
Line line[MAXN << 1];

// stjump[i][p] : 从i号线段出发，跳的次数是2的p次方，能到达的最右线段的编号
int stjump[MAXN << 1][LIMIT];
int ans[MAXN];
int n, m;

// <=n最接近的2的幂，是2的几次方
int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) ans++;
    return ans;
}

void build() {
    for (int i = 1; i <= n; i++)
        if (line[i].l > line[i].r) line[i].r += m;
    sort(line + 1, line + n + 1, [](const Line& a, const Line& b) {
        return a.l < b.l;
    });
    for (int i = 1; i <= n; i++) {
        line[i + n].id = line[i].id;
        line[i + n].l = line[i].l + m;
        line[i + n].r = line[i].r + m;
    }
    int e = n << 1;
    for (int i = 1, arrive = 1; i <= e; i++) {
        while (arrive + 1 <= e && line[arrive + 1].l <= line[i].r) arrive++;
        stjump[i][0] = arrive;
    }
    for (int p = 1; p <= power; p++)
        for (int i = 1; i <= e; i++)
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
}

int jump(int i) {
    int aim = line[i].l + m, cur = i, next, ans = 0;
    for (int p = power; p >= 0; p--) {
        next = stjump[cur][p];
        if (next != 0 && line[next].r < aim) {
            ans += 1 << p;
            cur = next;
        }
    }
    return ans + 1 + 1;
}
```

---

## 三、ST表查询最大值和最小值

### 题面

给定长度 n 的数组 arr，m 次查询 `arr[l~r]` 上的最大值和最小值，每次查询打印「最大值 − 最小值」。

测试链接：https://www.luogu.com.cn/problem/P2880

### 核心思路

- 建两张 ST 表 `stmax` / `stmin`，`st[i][p]` 表示从 i 开始、长度 `2^p` 区间上的最大值 / 最小值。
- 转移：`st[i][p] = max/min(st[i][p-1], st[i + 2^(p-1)][p-1])`（左右两半各长 `2^(p-1)`）。
- 预处理 `lg[i] = lg[i>>1] + 1`（`lg[0] = -1`），`lg[i]` 表示 ≤i 最大的 2 的幂是几次方，查询时直接查表得到列号 p。
- 查询 `[l,r]`：`p = lg[r-l+1]`，结果 = `max(stmax[l][p], stmax[r-2^p+1][p]) - min(stmin[l][p], stmin[r-2^p+1][p])`。

### 坑点

- `LIMIT = 16`（`2^15 ≤ 50001 < 2^16`，所以次方 0~15 共 16 列）。
- 查询时左右两段允许重叠——最大/最小值是「可重复贡献问题」，重叠不影响结果。

### 代码

```cpp
const int MAXN = 50001;
const int LIMIT = 16;

int arr[MAXN];
int lg[MAXN];   // lg[i] : 查询<=i情况下，最大的2的幂，是2的几次方
int stmax[MAXN][LIMIT];
int stmin[MAXN][LIMIT];

void build(int n) {
    lg[0] = -1;
    for (int i = 1; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
        stmax[i][0] = arr[i];
        stmin[i][0] = arr[i];
    }
    for (int p = 1; p <= lg[n]; p++)
        for (int i = 1; i + (1 << p) - 1 <= n; i++) {
            stmax[i][p] = max(stmax[i][p - 1], stmax[i + (1 << (p - 1))][p - 1]);
            stmin[i][p] = min(stmin[i][p - 1], stmin[i + (1 << (p - 1))][p - 1]);
        }
}

int query(int l, int r) {
    int p = lg[r - l + 1];
    int a = max(stmax[l][p], stmax[r - (1 << p) + 1][p]);
    int b = min(stmin[l][p], stmin[r - (1 << p) + 1][p]);
    return a - b;
}
```

---

## 四、ST表查询最大公约数

### 题面

给定长度 n 的数组 arr，m 次查询 `arr[l~r]` 上所有数的最大公约数。

测试链接：https://www.luogu.com.cn/problem/P1890

### 核心思路

与最大/最小值 ST 表完全同理，只是合并操作换成 `gcd`（辗转相除法，讲解041）。因为 `gcd` 也是「可重复贡献」运算（左半 gcd 与右半 gcd 再取 gcd 即整体 gcd），重叠无影响。

### 坑点

- `build` 中会调用 `gcd`，而 `gcd` 定义在 `build` 之后，需要**先声明** `int gcd(int a, int b);`。
- `MAXN = 1001`，`LIMIT = 10`（`2^10 = 1024 > 1001`）。

### 代码

```cpp
const int MAXN = 1001;
const int LIMIT = 10;

int arr[MAXN];
int lg[MAXN];
int stgcd[MAXN][LIMIT];

int gcd(int a, int b);

void build(int n) {
    lg[0] = -1;
    for (int i = 1; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
        stgcd[i][0] = arr[i];
    }
    for (int p = 1; p <= lg[n]; p++)
        for (int i = 1; i + (1 << p) - 1 <= n; i++)
            stgcd[i][p] = gcd(stgcd[i][p - 1], stgcd[i + (1 << (p - 1))][p - 1]);
}

// 算法讲解041 - 辗转相除法求最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int query(int l, int r) {
    int p = lg[r - l + 1];
    return gcd(stgcd[l][p], stgcd[r - (1 << p) + 1][p]);
}
```

---

## 五、出现次数最多的数有几个（有序数组 + 分桶 + ST表）

### 题面

给定长度 n 的**有序**数组 arr，m 次查询 `arr[l~r]` 上出现次数最多的数有几个。

题目查看：https://www.luogu.com.cn/problem/UVA11235　提交：https://vjudge.net/problem/UVA-11235（对数器验证亦可）

### 核心思路

利用「有序」这个性质把相同数字归为一个"桶"：

1. `bucket[i]`：下标 i 属于几号桶；`lft[i]` / `rgt[i]`：第 i 号桶的左 / 右边界。桶的词频 = `rgt[i] - lft[i] + 1`（无需单独存词频数组）。
2. 对「桶的词频」构建最大值 ST 表 `stmax`。
3. 查询 `[l,r]`：`lbucket = bucket[l]`，`rbucket = bucket[r]`。
   - 若 `lbucket == rbucket`，答案 = `r - l + 1`。
   - 否则：`a = rgt[lbucket] - l + 1`（左桶命中数），`b = r - lft[rbucket] + 1`（右桶命中数），中间桶（`lbucket+1 ~ rbucket-1`）若存在则用 ST 表查最大词频 `c`，答案 = `max(a, b, c)`。

### 坑点

- `arr[0]` 设成极小值（如 `-23333333`），这样从下标 1 开始能自然识别第一个桶的开始。
- `l > r` 时要先交换（防"捣乱"查询）。
- 中间桶可能不存在（`lbucket + 1 == rbucket` 时），必须判断 `lbucket + 1 < rbucket` 才查 ST 表。

### 代码

```cpp
const int MAXN = 100001;
const int LIMIT = 17;

int arr[MAXN];
int lg[MAXN];
int bucket[MAXN];
int lft[MAXN];
int rgt[MAXN];
int stmax[MAXN][LIMIT];

void build(int n) {
    // 题目给定的数值范围-100000 ~ +100000
    // 把arr[0]设置成不会到达的数字即可
    arr[0] = -23333333;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i - 1] != arr[i]) {
            rgt[cnt] = i - 1;
            lft[++cnt] = i;
        }
        bucket[i] = cnt;
    }
    rgt[cnt] = n;
    lg[0] = -1;
    for (int i = 1; i <= cnt; i++) {
        lg[i] = lg[i >> 1] + 1;
        stmax[i][0] = rgt[i] - lft[i] + 1;
    }
    for (int p = 1; p <= lg[cnt]; p++)
        for (int i = 1; i + (1 << p) - 1 <= cnt; i++)
            stmax[i][p] = max(stmax[i][p - 1], stmax[i + (1 << (p - 1))][p - 1]);
}

int query(int l, int r) {
    if (l > r) { int tmp = l; l = r; r = tmp; }
    int lbucket = bucket[l];
    int rbucket = bucket[r];
    if (lbucket == rbucket) return r - l + 1;
    // a : 最左侧桶在此时l~r范围上的数字有几个
    // b : 最右侧桶在此时l~r范围上的数字有几个
    int a = rgt[lbucket] - l + 1, b = r - lft[rbucket] + 1, c = 0;
    if (lbucket + 1 < rbucket) {
        int from = lbucket + 1, to = rbucket - 1, p = lg[to - from + 1];
        c = max(stmax[from][p], stmax[to - (1 << p) + 1][p]);
    }
    return max(max(a, b), c);
}
```

---

## 总结：ST 表的适用范围与优缺点

- **适用**：可重复贡献问题（区间最大值、最小值、gcd、区间按位与、区间按位或等）——即两段有重叠也不影响最终答案的查询。
- **不适用**：区间求和等（重叠部分需要额外减掉，不方便）。
- **优点**：构建 `O(n log n)`，构建后单次查询 `O(1)`，代码量比线段树小。
- **缺点**：空间 `O(n log n)`（比线段树/树状数组大），只能维护可重复贡献信息，且**不支持修改**（一旦改值 ST 表就废了）。
