# class076 区间DP（上）

> B站视频：[算法讲解076](https://www.bilibili.com/video/BV1NQ4y1b7Uo/)
> 前置知识：class067、class068（二维DP及空间压缩）

## 核心知识：区间DP两种展开方式

区间DP = 解决大范围`[L,R]`的问题，拆成小范围再汇总。两种常见展开方式：

| 方式 | 特点 | 复杂度 | 题目 |
|------|------|--------|------|
| 基于两侧端点 | 依赖`L+1/R-1`等固定位置，无for枚举 | O(n²) | 1, 2 |
| 基于范围划分点 | 枚举中间划分点`m`，左右分别求解 | O(n³) | 3, 4, 5, 6 |

---

## 01 让字符串成为回文串的最少插入次数 — LeetCode 1312

**题面：** 给定字符串，可在任意位置插入任意字符，求使其成为回文串的最少插入次数。

**核心思路：** `f(l,r)` = 让`s[l..r]`变回文的最少插入数。分情况：
- `l==r` → 0（单字符天然回文）
- `l+1==r` → `s[l]==s[r] ? 0 : 1`
- `s[l]==s[r]` → `f(l+1, r-1)`（两端自我消化）
- `s[l]!=s[r]` → `min(f(l+1,r), f(l,r-1)) + 1`（搞定一端，加一个字符配它）

**坑点：** 无。

**代码：**
```cpp
// 记忆化搜索
class Solution {
public:
    int dp[505][505];

    int f1(string& s,int l,int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans = 0;
        if(l==r){
            ans = 0;
        }else if(l+1==r){
            ans = s[l] == s[r] ? 0 : 1;
        }else{
            if(s[l]==s[r]){
                ans = f1(s, l + 1, r - 1);
            }else{
                ans = min(f1(s, l + 1, r), f1(s, l, r - 1)) + 1;
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    int minInsertions(string s) {
        int n = s.length();
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j)
                dp[i][j] = -1;
        }
        return f1(s, 0, n - 1);
    }
};

// 严格位置依赖的动态规划
class Solution {
public:
    int dp[505][505];

    int minInsertions(string s) {
        int n = s.length();
        for (int i = 0; i < n;++i)
            dp[i][i] = 0;
        for (int l = 0; l < n - 1;++l)
            dp[l][l + 1] = s[l] == s[l + 1] ? 0 : 1;
        for (int l = n - 3; l >= 0;--l){
            for (int r = l + 2; r < n;++r){
                if(s[l]==s[r]){
                    dp[l][r] = dp[l + 1][r - 1];
                }else{
                    dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1;
                }
            }
        }
        return dp[0][n - 1];
    }
};
```

---

## 02 预测赢家 — LeetCode 486

**题面：** 非负数组，两人轮流从两端取数，都绝顶聪明（零和博弈）。玩家1先手，问玩家1能否获胜（得分≥玩家2）。

**核心思路：** `f(l,r)` = 在`[l..r]`上先手能得的最大分数。玩家1拿走`nums[l]`后，玩家2会在`[l+1..r]`上做对自己最有利的选择，给玩家1留下后续的**最小值**（因为零和博弈）：
```cpp
p1 = nums[l] + min(f(l+2,r), f(l+1,r-1))  // 拿左边
p2 = nums[r] + min(f(l+1,r-1), f(l,r-2))  // 拿右边
return max(p1, p2)
```
答案：`sum = Σnums`，`first = dp[0][n-1]`，`second = sum - first`，`return first >= second`。

**坑点：** 每个玩家的得分决策都基于"给对手留下最差局面"。

**代码：**
```cpp
class Solution {
public:
    int dp[25][25];

    int f(vector<int>& nums,int l, int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans;
        if (l == r){
            ans = nums[l];
        }else if(l==r-1){
            ans = nums[l] > nums[r] ? nums[l] : nums[r];
        }else{
            int p1 = nums[l] + min(f(nums, l + 2, r), f(nums, l + 1, r - 1));
            int p2 = nums[r] + min(f(nums, l + 1, r - 1), f(nums, l, r - 2));
            ans = max(p1, p2);
        }
        dp[l][r] = ans;
        return ans;
    }

    bool predictTheWinner(vector<int>& nums) {
        int sum = 0;
        int n = nums.size();
        for(int n:nums)
            sum += n;
        for (int i = 0; i < n;++i){
            for (int j = 0; j < n;++j)
                dp[i][j] = -1;
        }
        int f1 = f(nums, 0, n - 1);
        int f2 = sum - f1;
        return f1 >= f2;
    }
};
```

---

## 03 多边形三角剖分的最低得分 — LeetCode 1039

**题面：** 凸n边形的顶点有权值，划分为n-2个三角形，每个三角形得分=三个顶点值乘积，总分为各三角形得分之和。求最低总分。

**核心思路：** `f(l,r)` = 顶点`l..r`围成的多边形的最低三角剖分得分。选中间点`m`（`l<m<r`），三角形`(l,m,r)`的得分=`arr[l]*arr[m]*arr[r]`，左侧`f(l,m)`+右侧`f(m,r)`递归。枚举所有m取min。

**坑点：** `l==r`或`l+1==r`时无法构成三角形，返回0。O(n³)。

**代码：**
```cpp
class Solution {
public:
    int dp[55][55];

    int f(vector<int>& arr,int l,int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans=INT_MAX;
        if(l==r || l+1==r){
            ans = 0;
        }else{
            for (int m = l + 1; m < r; ++m){
                ans = min(ans, f(arr, l, m) + arr[l] * arr[m] * arr[r] + f(arr, m, r));
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    int minScoreTriangulation(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j)
                dp[i][j] = -1;
        }
        return f(arr, 0, n - 1);
    }
};


class Solution {
public:
    int dp[55][55];

    int minScoreTriangulation(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n;++i)
            dp[i][i] = 0;
        for (int i = 0; i < n - 1;++i)
            dp[i][i + 1] = 0;
        for (int l = n - 3; l >= 0; --l){
            for (int r = l + 2; r < n; ++r){
                dp[l][r] = INT_MAX;
                for (int m = l + 1; m < r; ++m){
                    dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r] + arr[l] * arr[m] * arr[r]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
```

---

## 04 切棍子的最小成本 — LeetCode 1547

**题面：** 长n的木棍，需要在cuts点切开。每次切割成本=当前切割段长度，可自由决定切割顺序。求最小总成本。

**核心思路：** 给cuts排序后补0和n（方便算长度）。`f(l,r)` = 切完`[l..r]`切点的最小成本。选第一个切点`k`，当前段长=`arr[r+1]-arr[l-1]`加上左右递归。枚举所有k取min。O(m³)，m是切点数量。

**坑点：** 需要在cuts前后补`0`和`n`来算长度。

**代码：**
```cpp
class Solution {
public:
    int dp[105][105];

    int f(int* arr,int l,int r){
        if(l>r)
            return 0;
        if(l==r)
            return arr[r + 1] - arr[l - 1];
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans = INT_MAX;
        for (int k = l; k <= r;++k){
            ans = min(ans, f(arr,l, k - 1) + f(arr,k + 1, r));
        }
        ans += arr[r + 1] - arr[l - 1];
        dp[l][r] = ans;
        return ans;
    }

    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        sort(cuts.begin(), cuts.end());
        int arr[m + 2];
        arr[0] = 0;
        for (int i = 1; i <= m; ++i){
            arr[i] = cuts[i - 1];
        }
        arr[m + 1] = n;
        for (int i = 0; i <= m;++i){
            for (int j = 0; j <= m;++j)
                dp[i][j] = -1;
        }
        return f(arr, 1, m);
    }
}; 

int minCost(int n, vector<int>& cuts) {
    int m = cuts.size();
    sort(cuts.begin(), cuts.end());
    arr[0] = 0; arr[m + 1] = n;
    for (int i = 1; i <= m; i++) arr[i] = cuts[i - 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++)
        dp[i][i] = arr[i + 1] - arr[i - 1];
    for (int l = m - 1; l >= 1; l--)
        for (int r = l + 1; r <= m; r++) {
            int nxt = INT_MAX;
            for (int k = l; k <= r; k++)
                nxt = min(nxt, dp[l][k - 1] + dp[k + 1][r]);
            dp[l][r] = arr[r + 1] - arr[l - 1] + nxt;
        }
    return dp[1][m];
}
```

---

## 05 戳气球 — LeetCode 312

**题面：** `nums[i]`个气球，戳爆`i`得`nums[i-1]*nums[i]*nums[i+1]`分。边界外=1。求最大得分。

**核心思路：** **关键洞察：尝试每个气球"最后打爆"**（而不是最先打爆！）。设潜台词：调用`f(l,r)`时保证`arr[l-1]`和`arr[r+1]`一定没爆。预处理：首尾补1。枚举最后打爆的气球`k`：
```
ans = arr[l-1]*arr[k]*arr[r+1] + f(l, k-1) + f(k+1, r)
```
最先打爆不行→因为B的右侧"最近的没爆气球"会随之前的打爆顺序变化，信息不够。

**坑点：** 必须"最后打爆"的尝试方式，配合"两端没爆"的潜台词。

**代码：**
```cpp
class Solution {
public:
    int dp[310][310];

    int f(int *arr, int l,int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans;
        if(l==r)
            ans = arr[l - 1] * arr[l] * arr[r + 1];
        else{
            ans=max(arr[l-1]*arr[l]*arr[r+1]+f(arr,l+1,r)
                   ,arr[l-1]*arr[r]*arr[r+1]+f(arr,l,r-1));
            for (int k = l + 1; k < r; ++k){
                ans = max(ans, arr[l - 1] * arr[k] * arr[r + 1] + f(arr, l, k - 1) + f(arr, k + 1, r));
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        int arr[n + 2];
        arr[0] = 1;
        arr[n + 1] = 1;
        for (int i = 1; i <= n; ++i)
            arr[i] = nums[i - 1];
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j)
                dp[i][j] = -1;
        }
        return f(arr, 1, n);
    }
};


int maxCoins(vector<int>& nums) {
    int n = nums.size();
    arr[0] = arr[n + 1] = 1;
    for (int i = 0; i < n; i++) arr[i + 1] = nums[i];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++)
        dp[i][i] = arr[i - 1] * arr[i] * arr[i + 1];
    for (int l = n; l >= 1; l--)
        for (int r = l + 1; r <= n; r++) {
            int ans = max(arr[l-1]*arr[l]*arr[r+1] + dp[l+1][r],
                          arr[l-1]*arr[r]*arr[r+1] + dp[l][r-1]);
            for (int k = l + 1; k < r; k++)
                ans = max(ans, arr[l-1]*arr[k]*arr[r+1]
                          + dp[l][k-1] + dp[k+1][r]);
            dp[l][r] = ans;
        }
    return dp[1][n];
}
```

---

## 06 布尔运算 — LeetCode 面试题 08.14

**题面：** 字符串`0/1`与`&|^`交替（范式：偶数下标数字，奇数下标逻辑符）。可加括号改变运算顺序。返回得到指定result的方法数。

**核心思路：** `f(l,r)`返回`int[2]`：`[false方法数, true方法数]`。枚举每个逻辑符`k`最后执行（`k=l+1, l+3, ...`，步长2），左侧`f(l,k-1)`、右侧`f(k+1,r)`。根据`s[k]`的类型（`&|^`）组合左右true/false的方法数累加。

**坑点：** 内存化搜索版本就够了；范式要求`l`和`r`位置必须是数字；逻辑符位置一定是奇数下标，枚举步长为2。

**代码：**
```cpp
int* f(string& s, int l, int r) {
    if (has[l][r]) return dp[l][r];
    int fcnt = 0, tcnt = 0;
    if (l == r) {
        fcnt = s[l] == '0' ? 1 : 0;
        tcnt = s[l] == '1' ? 1 : 0;
    } else {
        for (int k = l + 1; k < r; k += 2) {
            int *tmp1 = f(s, l, k - 1), *tmp2 = f(s, k + 1, r);
            int a = tmp1[0], b = tmp1[1], c = tmp2[0], d = tmp2[1];
            if (s[k] == '&') { fcnt += a*c+a*d+b*c; tcnt += b*d; }
            else if (s[k] == '|') { fcnt += a*c; tcnt += a*d+b*c+b*d; }
            else { fcnt += a*c+b*d; tcnt += a*d+b*c; }
        }
    }
    dp[l][r][0] = fcnt; dp[l][r][1] = tcnt; has[l][r] = true;
    return dp[l][r];
}
```
