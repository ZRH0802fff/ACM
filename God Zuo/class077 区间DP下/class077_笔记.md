# class077 区间DP（下）

> B站视频：[算法讲解077](https://www.bilibili.com/video/BV1NK4y1q7Sm/)
> 前置知识：class076（区间DP上）

---

## 01 完成配对需要的最少字符数量（括号配对）

**题面：** 字符串由`[`、`]`、`(`、`)`组成，最少插入多少个括号使所有括号正确配对。

**核心思路：** `f(l,r)` = 让`s[l..r]`正确配对的最少插入数。两种可能性：
- 可能性1：`s[l]`与`s[r]`本就配对 → `f(l+1, r-1)`
- 可能性2：枚举划分点`m`，左右各自配对 → `f(l,m) + f(m+1,r)`

取min。base case：`l==r→1`，`l+1==r→`配对0/不配对2。

**坑点：** 可能性1和可能性2都要考虑，不能只看两端配对。

**代码：**
```cpp
const int maxn = 210;
int dp[maxn][maxn];
string s;

int f(int l,int r){
    if(l==r)
        return 1;
    if(l+1==r){
        if((s[l]=='(' && s[r]==')') || (s[l]=='[' && s[r]==']')){
            return 0;
        }else{
            return 2;
        }
    }
    if(dp[l][r]!=-1)
        return dp[l][r];

    int p1 = INT_MAX;
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')){
        p1 = f(l + 1, r - 1);
    }
    int p2 = INT_MAX;
    for (int k = l; k < r;++k){
        p2 = min(p2, f(l, k) + f(k + 1, r));
    }
    int ans = min(p1, p2);
    dp[l][r] = ans;
    return ans;
}

int main(){
    cin >> s;
    int n = s.length();
    for (int i = 0; i < n;++i){
        for (int j = 0; j < n;++j)
            dp[i][j] = -1;
    }
    cout << f(0, n - 1)<<'\n';
    return 0;
}
```

---

## 02 涂色（奇怪打印机） — LeetCode 664

**题面：** 每次可以把一段连续区间涂成同一颜色（后涂覆盖先涂），求涂出目标串的最少次数。

**核心思路：** `dp[l][r]` = 涂出`s[l..r]`的最少次数。
- 若`s[l]==s[r]` → `dp[l][r] = dp[l][r-1]`（因为涂`[l..r]`时顺带把最右涂了）
- 否则枚举划分点m → `dp[l][r] = min(dp[l][m] + dp[m+1][r])`

**坑点：** `s[l]==s[r]`时`dp[l][r-1]`和`dp[l+1][r]`等价。

**代码：**
```cpp
class Solution {
public:
    int dp[105][105];

    int f(string& s,int l,int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans = INT_MAX;
        if(l==r){
            ans = 1;
        }else if(l+1==r){
            ans = s[l] == s[r] ? 1 : 2;
        }else{
            if(s[l]==s[r]){
                ans = f(s, l, r - 1);
            }else{
                for (int m = l; m < r;++m){
                    ans = min(ans, f(s,l, m) + f(s,m + 1, r));
                }
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    int strangePrinter(string s) {
        int n = s.length();
        for (int i = 0; i < n;++i){
            for (int j = 0; j < n;++j){
                dp[i][j] = -1;
            }
        }
        return f(s, 0, n - 1);
    }
};


int strangePrinter(string str) {
    int n = str.length();
    dp[n-1][n-1] = 1;
    for (int i = 0; i < n-1; i++) {
        dp[i][i] = 1;
        dp[i][i+1] = str[i]==str[i+1] ? 1 : 2;
    }
    for (int l = n-3; l >= 0; l--)
        for (int r = l+2; r < n; r++) {
            if (str[l] == str[r])
                dp[l][r] = dp[l][r-1];
            else {
                int ans = INT_MAX;
                for (int m = l; m < r; m++)
                    ans = min(ans, dp[l][m] + dp[m+1][r]);
                dp[l][r] = ans;
            }
        }
    return dp[0][n-1];
}
```

---

## 03 合唱队 — 洛谷 P3205

**题面：** n个人按编号排列，有一个理想队形（给定数组）。每次从当前队伍的最左或最右选一个人加入新队列的末尾。求有多少种出队方式能得到理想队形，结果对19650827取模。

**推导状态转移方程**

从左边进来肯定前 1 个人比他高，前 1 个人有 2 种情况，要么在 *i*+1 号位置，要么在 *j* 号位置。

同理，

从右边进来肯定前 1 个人比他矮，前 1 个人有 2 种情况，要么在 *j*−1 号位置，要么在 *i* 号位置。

那么状态转移方程就出来了：

```cpp
if(a[i]<a[i+1])f[i][j][0]+=f[i+1][j][0];
if(a[i]<a[j])f[i][j][0]+=f[i+1][j][1];
if(a[j]>a[i])f[i][j][1]+=f[i][j-1][0];
if(a[j]>a[j-1])f[i][j][1]+=f[i][j-1][1];
f[i][j][0]%=19650827;
f[i][j][1]%=19650827;
```

**坑点：** 第三维记录"最后加入的是左端还是右端"，从小区间往大区间推。

**代码：**
```cpp
int compute() {
    memset(dp3d, 0, sizeof(dp3d));
    for (int i = 1; i < n; i++)
        if (nums[i] < nums[i+1])
            dp3d[i][i+1][0] = dp3d[i][i+1][1] = 1;
    for (int l = n-2; l >= 1; l--)
        for (int r = l+2; r <= n; r++) {
            if (nums[l] < nums[l+1])
                dp3d[l][r][0] = (dp3d[l][r][0] + dp3d[l+1][r][0]) % MOD;
            if (nums[l] < nums[r])
                dp3d[l][r][0] = (dp3d[l][r][0] + dp3d[l+1][r][1]) % MOD;
            if (nums[r] > nums[l])
                dp3d[l][r][1] = (dp3d[l][r][1] + dp3d[l][r-1][0]) % MOD;
            if (nums[r] > nums[r-1])
                dp3d[l][r][1] = (dp3d[l][r][1] + dp3d[l][r-1][1]) % MOD;
        }
    return (dp3d[1][n][0] + dp3d[1][n][1]) % MOD;
}
```

---

## 04 移除盒子 — LeetCode 546

**题面：** 盒子有颜色，每轮移除k个连续的相同颜色盒子得`k*k`分。求最大总分。

**核心思路：** 三维dp。`f(l,r,k)` = `[l..r]`范围上消除，前面有k个与`boxes[l]`同色的连续盒子。先合并两端同色的（`s`指针跳过），`cnt=k+s-l+1`。两种选择：①前缀直接消：`cnt*cnt+f(s+1,r,0)`；②前缀跟后面的同色盒子一起消：枚举`m`满足`boxes[l]==boxes[m]`且`boxes[m-1]!=boxes[m]`（剪枝），`f(s+1,m-1,0)+f(m,r,cnt)`。

**坑点：** 第三维k记录"前面跟了几个同色盒子"，是区间DP的扩展维度。O(n⁴)。

**代码：**
```cpp
class Solution {
public:
    // 时间复杂度O(n^4)
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        memset(dp, 0, sizeof(dp));
        return f(boxes, 0, n - 1, 0);
    }

    // boxes[l....r]范围上要去消除，前面跟着k个连续的和boxes[l]颜色一样的盒子
    // 这种情况下，返回最大得分
    int f(vector<int>& boxes, int l, int r, int k) {
        if (l > r) {
            return 0;
        }
        // l <= r
        if (dp[l][r][k] > 0) {
            return dp[l][r][k];
        }
        int s = l;
        while (s + 1 <= r && boxes[l] == boxes[s + 1]) {
            s++;
        }
        // boxes[l...s]都是一种颜色，boxes[s+1]就不是同一种颜色了
        // cnt是总前缀数量 : 之前的相同前缀(k个) + l...s这个颜色相同的部分(s-l+1个)
        int cnt = k + s - l + 1;
        // 可能性1 : 前缀先消
        int ans = cnt * cnt + f(boxes, s + 1, r, 0);
        // 可能性2 : 讨论前缀跟着哪个后，一起消掉
        for (int m = s + 2; m <= r; m++) {
            if (boxes[l] == boxes[m] && boxes[m - 1] != boxes[m]) {
                // boxes[l] == boxes[m]是必须条件
                // boxes[m - 1] != boxes[m]是剪枝条件，避免不必要的调用
                ans = max(ans, f(boxes, s + 1, m - 1, 0) + f(boxes, m, r, cnt));
            }
        }
        dp[l][r][k] = ans;
        return ans;
    }
};

```

---

## 05 合并石头的最低成本 — LeetCode 1000

**题面：** n堆石头，每次将连续k堆合并为1堆，成本为这k堆的石子总数。求合并成1堆的最低成本，不能则返回-1。

**核心思路：** 前提：`(n-1)%(k-1)==0`才能合成1堆。`dp[l][r]` = `l..r`合并到不能再合并的最小成本。枚举`m`（步长`k-1`）：`dp[l][r]=min(dp[l][m]+dp[m+1][r])`。若`(r-l)%(k-1)==0`（最终能成1份），额外加上`sum[l..r]`。`m`跳`k-1`保证左右子问题的份数约束。

**坑点：** 合并前必须先检查`(n-1)%(k-1)==0`；枚举m的步长必须是`k-1`。

**代码：**
```cpp
int mergeStones(vector<int>& stones, int k) {
    int n = stones.size();
    if ((n-1)%(k-1) != 0) return -1;
    presum[0] = 0;
    for (int i = 0; i < n; i++) presum[i+1] = presum[i] + stones[i];
    memset(dp, 0, sizeof(dp));
    for (int l = n-2; l >= 0; l--)
        for (int r = l+1; r < n; r++) {
            int ans = INT_MAX;
            for (int m = l; m < r; m += k-1)
                ans = min(ans, dp[l][m] + dp[m+1][r]);
            if ((r-l)%(k-1) == 0)
                ans += presum[r+1] - presum[l];
            dp[l][r] = ans;
        }
    return dp[0][n-1];
}
```

---

## 06 统计不同回文子序列 — LeetCode 730

**题面：** 给定字符串s，返回**不同的**非空回文子序列个数（对1e9+7取模）。

**核心思路：** O(n²)。`dp[i][j]` = `s[i..j]`上不同回文子序列个数。预处理`left[i]`=`i`左边最近同字符位置，`right[i]`=`i`右边最近同字符位置。

若`s[i]!=s[j]`：`dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]`（容斥）

若`s[i]==s[j]`（设为`a`）：分三种情况——
- 内部无`a`：`2*dp[i+1][j-1] + 2`（`a`、`aa`两个新的）
- 内部有1个`a`：`2*dp[i+1][j-1] + 1`（`aa`一个）
- 内部≥2个`a`：`2*dp[i+1][j-1] - dp[l+1][r-1]`（`aa`重复计算了）

**坑点：** 减法取模要`+MOD`再`%MOD`；`left/right`预处理是关键。

**代码：**
```cpp
int countPalindromicSubsequences(string str) {
    int n = str.length();
    // 预处理 left/right
    memset(last, -1, sizeof(last));
    for (int i = 0; i < n; i++) { leftIdx[i]=last[str[i]]; last[str[i]]=i; }
    for (int i = 0; i < 256; i++) last[i] = n;
    for (int i = n-1; i >= 0; i--) { rightIdx[i]=last[str[i]]; last[str[i]]=i; }
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int i = n-2; i >= 0; i--)
        for (int j = i+1; j < n; j++) {
            if (str[i] != str[j])
                dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1] + MOD;
            else {
                int l = rightIdx[i], r = leftIdx[j];
                if (l > r) dp[i][j] = dp[i+1][j-1]*2 + 2;
                else if (l == r) dp[i][j] = dp[i+1][j-1]*2 + 1;
                else dp[i][j] = dp[i+1][j-1]*2 - dp[l+1][r-1] + MOD;
            }
            dp[i][j] %= MOD;
        }
    return (int)dp[0][n-1];
}
```
