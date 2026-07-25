# class070 子数组最大累加和问题与扩展（上）

> B站视频：[算法讲解070](https://www.bilibili.com/video/BV1pw411M7Du/)
> 前置知识：class051 二分答案法、class066 一维动态规划

---

## 01 子数组最大累加和 — LeetCode 53

**题面：** 给定整数数组，求非空连续子数组的最大累加和。

**核心思路：** `dp[i]` = 子数组**必须以i结尾**往左延伸的最大累加和。两种选择：自己待着 `nums[i]`，或往左扩 `dp[i-1]+nums[i]`。空间压缩只需一个 `pre` 变量滚动。

附加问题——同时返回开头的`left`、结尾的`right`、累加和`sum`：`pre>=0`时不换开头，`pre<0`时换开头`l=r`，`pre>sum`时更新三个全局变量。`pre`初始为`INT_MIN`保证0位置正确初始化。

**坑点：** 无。

**代码：**
```cpp
int maxSubArray(vector<int>& nums) {
    int n = nums.size(), ans = nums[0];
    for (int i = 1, pre = nums[0]; i < n; i++) {
        pre = max(nums[i], pre + nums[i]);
        ans = max(ans, pre);
    }
    return ans;
}
// 附加：同时求 left, right, sum
int left, right, sum;
void extra(vector<int>& nums) {
    sum = INT_MIN;
    for (int l = 0, r = 0, pre = INT_MIN; r < (int)nums.size(); r++) {
        if (pre >= 0) pre += nums[r];
        else { pre = nums[r]; l = r; }
        if (pre > sum) { sum = pre; left = l; right = r; }
    }
}
```

---

## 02 不选相邻元素的最大累加和（打家劫舍） — LeetCode 198

**题面：** 数组中可以随意选数，但不能选相邻的。求最大累加和。

**核心思路：** 与题目1不同，这里是**子序列**。`dp[i]` = `[0..i]`范围上随意选但不能相邻的最大累加和。转移：①不要`nums[i]`→`dp[i-1]`；②要`nums[i]`→`max(nums[i], dp[i-2]+nums[i])`。空间压缩用`prepre`(dp[i-2])和`pre`(dp[i-1])两变量滚动。

**坑点：** n=1和n=2要单独处理。

**代码：**
```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);
    int prepre = nums[0], pre = max(nums[0], nums[1]);
    for (int i = 2, cur; i < n; i++) {
        cur = max(pre, max(nums[i], prepre + nums[i]));
        prepre = pre; pre = cur;
    }
    return pre;
}
```

---

## 03 环形子数组最大累加和 — LeetCode 918

**题面：** 数组首尾相连（环形），求非空连续子数组最大累加和。

**核心思路：** 答案分两种：①不被隔断→普通子数组最大累加和`maxSum`；②被隔断（开头取一段+结尾取一段）=`all-minSum`（整体减掉中间最差部分）。同时维护`maxpre`和`minpre`。特例：`all==minSum`说明整块被抠掉（空数组不合法），只返回`maxSum`。

**坑点：** `all==minSum`时不能选`all-minSum`（相当于空数组）。

**代码：**
```cpp
int maxSubarraySumCircular(vector<int>& nums) {
    int n = nums.size(), all = nums[0], maxsum = nums[0], minsum = nums[0];
    for (int i = 1, maxpre = nums[0], minpre = nums[0]; i < n; i++) {
        all += nums[i];
        maxpre = max(nums[i], nums[i] + maxpre);
        maxsum = max(maxsum, maxpre);
        minpre = min(nums[i], nums[i] + minpre);
        minsum = min(minsum, minpre);
    }
    return all == minsum ? maxsum : max(maxsum, all - minsum);
}
```

---

## 04 环形数组 + 不能选相邻元素（打家劫舍 II） — LeetCode 213

**题面：** 房屋围成一圈（首尾相邻），不能偷相邻的，求最大金额。

**核心思路：** 按`nums[0]`要不要分两类：①不要`nums[0]`→在`[1, n-1]`上跑普通打家劫舍；②要`nums[0]`→`nums[0] + [2, n-2]`范围上跑普通打家劫舍。取max。

**坑点：** n=1要单独处理。

**代码：**
```cpp
int best(vector<int>& nums, int l, int r) {
    if (l > r) return 0;
    if (l == r) return nums[l];
    if (l + 1 == r) return max(nums[l], nums[r]);
    int prepre = nums[l], pre = max(nums[l], nums[l + 1]);
    for (int i = l + 2, cur; i <= r; i++) {
        cur = max(pre, nums[i] + max(0, prepre));
        prepre = pre; pre = cur;
    }
    return pre;
}
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    return max(best(nums, 1, n - 1), nums[0] + best(nums, 2, n - 2));
}
```

---

## 05 打家劫舍 IV — LeetCode 2560

**题面：** 窃取能力=能偷的房间金额上限。必须偷至少k间（不能相邻），问最小能力值是多少。

**核心思路：** 二分答案法。能力范围`[min(nums), max(nums)]`。判断函数`mostRob(ability)`：能力定了，贪心求最多偷几间——遇到能偷的尽早偷然后跳过相邻。若`mostRob(mid)>=k`则记录答案并搜左边更小能力。

**坑点：** 贪心成立的原因是收益都是+1（偷一间），不是加金额。尽早偷能给后面留更大范围。

**代码：**
```cpp
int check(vector<int> &nums,int n,int ab){
        if(n==1)
            return nums[0] <= ab ? 1 : 0;
        if(n==2)
            return (nums[0] <= ab || nums[1] <= ab) ? 1 : 0;
        int pre2 = nums[0] <= ab ? 1 : 0;
        int pre1 = (nums[0] <= ab || nums[1] <= ab) ? 1 : 0;
        for (int i = 2, cur; i < n;++i){
            cur = max(pre1, pre2 + (nums[i] <= ab ? 1 : 0));
            pre2 = pre1;
            pre1=cur;
        }
        return pre1;
    }

    int minCapability(vector<int> &nums, int k){
        int n = nums.size();
        int l = nums[0], r = nums[0];
        for (int i = 0; i < n;++i){
            l = nums[i] < l ? nums[i] : l;
            r = nums[i] > r ? nums[i] : r;
        }
        int m, ans = 0;
        while(l<=r){
            m = (l + r) / 2;
            if(check(nums,n,m)>=k){
                ans = m;
                r = m - 1;
            }else{
                l = m + 1;
            }
        }
        return ans;
    }
```

---

## 06 子矩阵最大累加和 — 面试题 17.24

**题面：** 二维数组，找子矩阵最大累加和，返回左上角和右下角坐标。

**核心思路：** 压缩数组。枚举起始行`up`和结束行`down`(O(n²))，把`[up..down]`行按列求和压缩成一维数组，在上面跑子数组最大累加和（边生成边判断），同步记录全局最大时的左上角`(up, l)`和右下角`(down, r)`。任何子矩阵必从某行开始到某行结束，枚举了所有组合。

**坑点：** 时间复杂度 O(n²·m)，最坏 O(n³)，已是最优解。空间 O(m)。

**代码：**
```cpp
vector<int> getMaxMatrix(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    int maxSum = INT_MIN, a = 0, b = 0, c = 0, d = 0;
    vector<int> nums(m);
    for (int up = 0; up < n; up++) {
        fill(nums.begin(), nums.end(), 0);
        for (int down = up; down < n; down++) {
            for (int l = 0, r = 0, pre = INT_MIN; r < m; r++) {
                nums[r] += grid[down][r];
                if (pre >= 0) pre += nums[r];
                else { pre = nums[r]; l = r; }
                if (pre > maxSum) {
                    maxSum = pre; a = up; b = l; c = down; d = r;
                }
            }
        }
    }
    return {a, b, c, d};
}
```
