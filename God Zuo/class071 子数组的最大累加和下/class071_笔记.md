# class071 子数组最大累加和问题与扩展（下）

> B站视频：[算法讲解071](https://www.bilibili.com/video/BV1qu4y187Xn/)
> 前置知识：class005 对数器、class046 前缀信息技巧、class054 单调队列

---

## 01 乘积最大子数组 — LeetCode 152

**题面：** 整数数组，求乘积最大的非空连续子数组的乘积。

**核心思路：** 与累加和版本的关键区别：有负数→负负得正。每步需同时维护以i结尾的**最大乘积**和**最小乘积**。三种可能：自己待着`nums[i]`、乘之前最大`maxVal*nums[i]`、乘之前最小`minVal*nums[i]`。分别取max和min赋给curmax和curmin，滚动更新。

**坑点：** 用`double`防中间溢出，答案转`int`。

**代码：**
```cpp
int maxProduct(vector<int>& nums) {
    double ans = nums[0], minVal = nums[0], maxVal = nums[0], curmin, curmax;
    for (int i = 1; i < (int)nums.size(); i++) {
        curmin = min({(double)nums[i], minVal * nums[i], maxVal * nums[i]});
        curmax = max({(double)nums[i], minVal * nums[i], maxVal * nums[i]});
        minVal = curmin; maxVal = curmax;
        ans = max(ans, maxVal);
    }
    return (int)ans;
}
```

---

## 02 子序列累加和被7整除的最大累加和

**题面：** 非负数组，任选数字组成子序列，累加和必须被7整除，返回最大累加和。

**核心思路：** dp第二位用**余数**而非累加和。`dp[i][j]`=前i个数形成的子序列累加和%7==j的最大累加和（-1表示不存在）。转移：不要`nums[i-1]`→`dp[i-1][j]`；要→找`need=(7+j-cur)%7`，`dp[i-1][need]+x`。初始化`dp[0][0]=0`（空集），其余-1。余数只有7种，O(7n)=O(n)。

**坑点：** 空集的累加和为0，模7为0，所以`dp[0][0]=0`有效；`dp[0][1..6]=-1`无效。

**代码：**
```cpp
int maxSum2(vector<int>& nums) {
    int n = nums.size();
    dp[0][0] = 0;
    for (int j = 1; j < 7; j++) dp[0][j] = -1;
    for (int i = 1, x, cur, need; i <= n; i++) {
        x = nums[i - 1]; cur = nums[i - 1] % 7;
        for (int j = 0; j < 7; j++) {
            dp[i][j] = dp[i - 1][j];
            need = (7 + j - cur) % 7;
            if (dp[i - 1][need] != -1)
                dp[i][j] = max(dp[i][j], dp[i - 1][need] + x);
        }
    }
    return dp[n][0];
}
```

---

## 03 魔法卷轴 — 两次清零机会的最大累加和

**题面：** 数组有正负零，最多2次机会把任意连续一段全变0，求操作后数组整体的最大累加和。

**核心思路：** 三种情况：①0次→全体求和；②1次→`pdp[i]`=0~i必用1次整体最大，转移为`max(pdp[i-1]+nums[i], maxPresum)`，其中`maxPresum`是所有前缀和+0的最大值；③2次→枚举划分点i，`pdp[i-1]+sdp[i]`。`sdp`从右往左对称求。

**坑点：** `maxPresum`初始要考虑0（一个数也不要时前缀和为0，可以全清掉）。

**代码：**
```cpp
int maxSum2(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    int p1 = 0; for (int num : nums) p1 += num;
    int sum = nums[0], maxPresum = max(0, nums[0]);
    for (int i = 1; i < n; i++) {
        pdp[i] = max(pdp[i - 1] + nums[i], maxPresum);
        sum += nums[i];
        maxPresum = max(maxPresum, sum);
    }
    int p2 = pdp[n - 1];
    sdp[n - 1] = 0; sum = nums[n - 1]; maxPresum = max(0, sum);
    for (int i = n - 2; i >= 0; i--) {
        sdp[i] = max(nums[i] + sdp[i + 1], maxPresum);
        sum += nums[i]; maxPresum = max(maxPresum, sum);
    }
    int p3 = INT_MIN;
    for (int i = 1; i < n; i++) p3 = max(p3, pdp[i - 1] + sdp[i]);
    return max(p1, max(p2, p3));
}
```

---

## 04 三个无重叠子数组的最大和 — LeetCode 689

**题面：** 给定数组和整数k，选3段长度为k、不重叠的子数组，使总和最大，返回字典序最小的3个起始下标。

**核心思路：** 三个辅助结构：①`sums[i]`=以i开头长度k的累加和（滑动窗口）；②`prefix[i]`=0~i范围长度k子数组的最大累加和的开头；③`suffix[i]`=i~n-1范围同理。枚举中间子数组i，左侧最优=`prefix[i-1]`，右侧最优=`suffix[i+k]`，总额=`sums[p]+sums[i]+sums[s]`。字典序处理：prefix新>老才更新（相等保留小的），suffix新>=老就更新（相等选新，更靠左）。

**坑点：** prefix和suffix的等号方向不同，都是为保证字典序最小。

**代码：**
```cpp
vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    for (int l = 0, r = 0, sum = 0; r < n; r++) {
        sum += nums[r];
        if (r - l + 1 == k) { sums[l] = sum; sum -= nums[l]; l++; }
    }
    for (int l = 1, r = k; r < n; l++, r++) {
        if (sums[l] > sums[prefix[r - 1]]) prefix[r] = l;
        else prefix[r] = prefix[r - 1];
    }
    suffix[n - k] = n - k;
    for (int l = n - k - 1; l >= 0; l--) {
        if (sums[l] >= sums[suffix[l + 1]]) suffix[l] = l;
        else suffix[l] = suffix[l + 1];
    }
    int a = 0, b = 0, c = 0, maxSum = 0;
    for (int p, s, i = k, j = 2 * k - 1, sum; j < n - k; i++, j++) {
        p = prefix[i - 1]; s = suffix[j + 1];
        sum = sums[p] + sums[i] + sums[s];
        if (sum > maxSum) { maxSum = sum; a = p; b = i; c = s; }
    }
    return {a, b, c};
}
```

---

## 05 翻转一次子数组最大累加和

**题面：** 随意选连续一段翻转（逆序），返回翻转后子数组最大累加和。

**核心思路：**

反转后得到最大累加和，这个子数组累加和的区间一定又一部分是翻转得来的，很容易排除翻转区间都在子数组内或者子数组完全被包含在翻转区间内的可能。

0..i-1 i...n-1

用maxend得到前面的最大子数组累加和，这一部分用于翻转到i前面

sta[i]表示必须以i开头的最大子数组累加和，这部分是没有翻转的。

枚举每一个i位置就能得到最终答案。

**坑点：** 

比如 [-1,-6,-5,4,-2,-3]

最大是4，由maxend得到，对应的是无有效翻转的情况（只翻转一个数字），要加一层判断

**代码：**
```cpp
int maxSumReverse2(vector<int>& nums) {
    int n = nums.size();
    start[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
        start[i] = max(nums[i], nums[i] + start[i + 1]);
    int ans = start[0];
    int end = nums[0], maxEnd = nums[0];
    for (int i = 1; i < n; i++) {
        ans = max(ans, maxEnd + start[i]);
        end = max(nums[i], end + nums[i]);
        maxEnd = max(maxEnd, end);
    }
    ans = max(ans, maxEnd);
    return ans;
}
```

---

## 06 删掉1个数后长度为k的子数组最大累加和

**题面：** 必须删1个数形成新数组，在新数组中找长度为k的子数组最大累加和。删哪个随意。

**核心思路：** 巧妙转化：原问题≡在原数组中考察每个**长度为k+1的窗口**，`窗口累加和 - 窗口内最小值`。无论删的数在答案内部还是外部，该转化都能覆盖。实现：滑动窗口维护累加和+单调队列维护窗口最小值。

**坑点：** n≤k时删完不够k个，返回0。

**代码：**
```cpp
int maxSum2(vector<int>& nums, int k) {
    int n = nums.size();
    if (n <= k) return 0;
    int l = 0, r = 0;
    long long sum = 0;
    int ans = INT_MIN;
    for (int i = 0; i < n; i++) {
        while (l < r && nums[window[r - 1]] >= nums[i]) r--;
        window[r++] = i;
        sum += nums[i];
        if (i >= k) {
            ans = max(ans, (int)(sum - nums[window[l]]));
            if (window[l] == i - k) l++;
            sum -= nums[i - k];
        }
    }
    return ans;
}
```
