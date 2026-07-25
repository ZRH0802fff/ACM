# class055 单调队列（下）

> B站视频：[算法讲解055](https://www.bilibili.com/video/BV1py4y1T7uL/)
> 前置知识：class054（单调队列上）

## 核心知识：单调队列的进阶用法

除了经典"滑动窗口最值"的用法，单调队列在很多题目里还用来**维持答案的可能性**：

1. 先分析题意，发现元素的**单调性**（值越小/越大越有优势，位置越靠后越有优势）
2. 用单调队列按规定好的单调性组织候选
3. 从**队头**淘汰"已过期/已被结算"的元素，从**队尾**淘汰"被新元素碾压、不再有希望"的元素
4. 配合前缀和、二分答案等技巧，解决更复杂的问题

**本质：** 队列中维护的是对"未来答案"仍有竞争力的候选元素。

---

## 01 和至少为K的最短子数组 — LeetCode 862

**题面：** 数组有正有负，求累加和 ≥ k 的最短非空子数组长度。

**核心思路：** 前缀和 + 单调递增队列（存前缀和下标）。遍历 i：
- **队头结算：** `pref[i] - pref[q[h]] >= k` → 计算长度更新答案，弹出队头（后面的 i 只会更长）
- **队尾维护递增：** `pref[q[t-1]] >= pref[i]` → 弹出队尾（当前 pref 更小且更靠后，完全碾压旧值）

**坑点：** 和普通的滑动窗口不同——这里窗口大小不固定，且数组有负数所以前缀和不单调。两个 while 条件各司其职。

**代码：**
```cpp
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + nums[i];
    h = t = 0; int ans = INT_MAX;
    for (int i = 0; i <= n; i++) {
        while (h < t && pref[i] - pref[q[h]] >= k)
            ans = min(ans, i - q[h++]);
        while (h < t && pref[q[t - 1]] >= pref[i]) t--;
        q[t++] = i;
    }
    return ans == INT_MAX ? -1 : ans;
}
```

---

## 02 满足不等式的最大值 — LeetCode 1499

**题面：** 给定二维点集 points（x 递增），找 max(y_j+y_i+x_j-x_i) 满足 x_j-x_i ≤ k。

**核心思路：** `y_j+y_i+|x_j-x_i| = y_j+x_j + (y_i-x_i)`（j>i）。维护关于 `y_i-x_i` 的**单调递减队列**。对于每个点 j：
- 淘汰过期：`x_i + k < x_j` 就弹出队头
- 结算答案：队头（yi-xi 最大）+ `y_j+x_j`
- 维护递减：队尾 `y_i-x_i ≤ y_j-x_j` 则弹出（被碾压），入队

**坑点：** 队中存的是点的**下标**，方便取值和判断过期。

**代码：**
```cpp
int findMaxValueOfEquation(vector<vector<int>>& pts, int k) {
    h = t = 0; int ans = INT_MIN;
    for (int j = 0; j < pts.size(); j++) {
        int xj = pts[j][0], yj = pts[j][1];
        while (h < t && pts[q[h]][0] + k < xj) h++;
        if (h < t) {
            int xi = pts[q[h]][0], yi = pts[q[h]][1];
            ans = max(ans, yj + xj + yi - xi);
        }
        int diff = yj - xj;
        while (h < t) {
            int ti = q[t - 1];
            if (pts[ti][1] - pts[ti][0] <= diff) t--; else break;
        }
        q[t++] = j;
    }
    return ans;
}
```

---

## 03 最大任务分配 — LeetCode 2071

**题面：** tasks 有难度，workers 有能力值，pills 片药每片给工人 +strength 力量。求最多能完成多少个任务。

**核心思路：** 二分答案 + 贪心。`check(m)`：用最强的 m 个工人做最简单的 m 个任务。每个工人：先把不吃药能做的任务入队头；能做就做最**简单**的（队头出）；否则吃药+把吃药后能做的入队，做最**难**的（队尾出）。

**坑点：** 双端队列：不吃药从队头出（做简单的），吃药从队尾出（做最难的，把简单的留给没药的工人）。吃了药还做不了→check 失败。

**代码：**
```cpp
auto check = [&](int m) -> bool {
    if (m == 0) return true;
    h = t = 0; int cnt = 0;
    for (int i = wsize - m, j = 0; i < wsize; i++) {
        int w = workers[i];
        while (j < m && tasks[j] <= w) q[t++] = j++;
        if (h < t && tasks[q[h]] <= w) { h++; }  // 不吃药
        else {
            while (j < m && tasks[j] <= w + strength) q[t++] = j++;
            if (h < t) { cnt++; t--; }  // 吃药，做最难的
            else return false;
        }
    }
    return cnt <= pills;
};
```
