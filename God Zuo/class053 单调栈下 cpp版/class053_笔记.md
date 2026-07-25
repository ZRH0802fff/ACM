# class053 单调栈（下）

> B站视频：[算法讲解053](https://www.bilibili.com/video/BV1Nk4y1A7R2/)
> 前置知识：class052（单调栈上）

## 核心知识：单调栈的进阶用法

除了经典"找左右最近且小"的用法，单调栈在很多题目里还用来**维持答案的可能性**：

1. 先分析题意，发现**单调性**（越靠左/右越有优势，或者值越大/小越有优势）
2. 用单调栈按规定好的单调性来组织候选答案
3. 当某个条件触发时，从栈顶开始淘汰不再有希望的候选
4. 每次淘汰结算当前候选的答案，或者排除它参与后续答案

**本质：** 保持栈中元素对"未来答案"仍有竞争力，没竞争力的弹出并结算。

---

## 01 最大宽度坡 — LeetCode 962

**题面：** 数组 nums，求最大的 `j-i` 满足 `i<j` 且 `nums[i] <= nums[j]`。

**核心思路：** 先从左往右建**严格递减栈**（只有比栈顶更小的才入栈）。再从右往左遍历 j，如果 `nums[栈顶] <= nums[j]` 则弹出结算宽度。递减栈保证了：栈里的每个 i 都代表一个"谷底"，如果连栈顶都能被 j 覆盖，那栈顶后面的更大值更有可能被后续 j 覆盖，层层结算。

**坑点：** 栈建好后不需要重新遍历建栈的部分 —— 从右往左一次性结算。

**代码：**
```cpp
int maxWidthRamp(vector<int>& nums) {
    int n = nums.size(); r = 0; stk[r++] = 0;
    for (int i = 1; i < n; i++)
        if (nums[stk[r - 1]] > nums[i]) stk[r++] = i;
    int ans = 0;
    for (int j = n - 1; j >= 0; j--)
        while (r > 0 && nums[stk[r - 1]] <= nums[j])
            ans = max(ans, j - stk[--r]);
    return ans;
}
```

---

## 02 去除重复字母 — LeetCode 316

**题面：** 字符串 s，去除重复字母使每个字母只出现一次，且返回字典序最小的结果。

**核心思路：** 单调递增栈（字典序最小）。统计每个字符剩余次数 `cnts`。遍历时：若当前字符已在栈里→跳过；否则不停弹出栈顶，条件：栈顶字符 > 当前字符 **且** 栈顶字符后面还会出现（`cnts[栈顶] > 0`）。弹出后从 `enter` 集合移除。最后当前字符入栈。

**坑点：** 必须用 `enter` 标记栈中已有字符避免重复入栈；弹出一个字符后要同步更新 enter。

**代码：**
```cpp
string removeDuplicateLetters(string s) {
    int cnts[256] = {}; bool enter[256] = {}; r = 0;
    for (char c : s) cnts[c]++;
    for (char c : s) {
        cnts[c]--;
        if (!enter[c]) {
            while (r > 0 && stk[r - 1] > c && cnts[stk[r - 1]] > 0)
                enter[stk[--r]] = false;
            stk[r++] = c; enter[c] = true;
        }
    }
    stk[r] = '\0'; return string(stk);
}
```

---

## 03 吃掉所有小鱼的步数 — LeetCode 2289

**题面：** 数组 nums，每一步 num[i] > nums[i+1] 则吃掉 nums[i+1]。返回多少步后数组变成非递减。

**核心思路：** 从右往左遍历，维护单调递增栈（存 `(值, 所需轮数)`）。当前数能吃掉比它小的栈顶：`curTurns++`，同时如果被吃的鱼花了 `t` 轮才消化完，那 `curTurns = max(curTurns, t)`。吃到最后入栈。全局取最大 `curTurns`。

**坑点：** "消化"时间——如果被吃掉的鱼自己花了 T 轮去吃别人，当前鱼必须等它消化完。

**代码：**
```cpp
int totalSteps(vector<int>& nums) {
    int n = nums.size(), ans = 0; r = 0;
    for (int i = n - 1; i >= 0; i--) {
        int cur = 0;
        while (r > 0 && valStk[r - 1] < nums[i]) {
            r--; cur++;
            if (turnsStk[r] > cur) cur = turnsStk[r];
        }
        valStk[r] = nums[i]; turnsStk[r] = cur; r++;
        if (cur > ans) ans = cur;
    }
    return ans;
}
```

---

## 04 统计全1子矩形个数 — LeetCode 1504

**题面：** 01 矩阵，统计全由 1 组成的子矩形总数量（不是最大面积，是计数）。

**核心思路：** 行压缩成直方图 height。每行用单调栈（递增）。弹出 cur 时，**只有 height[cur] > height[j] 才结算**（相等时跳过，由最右边的那个统一结算，避免重复）。结算公式：`(height[cur] - bottom) * len * (len + 1) / 2`，其中 bottom = max(左边更矮高度, 右边更矮高度)，len = 当前段的列数。含义是该高度区间的所有可能矩形底部组合。

**坑点：** 计算公式 `len*(len+1)/2` 是组合数（选左右端点）；`bottom` 取左右边界的更高值。

**代码：**
```cpp
int numSubmat(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size(), ans = 0;
    memset(height, 0, sizeof(height));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            height[j] = mat[i][j] == 0 ? 0 : height[j] + 1;
        r = 0;
        for (int j = 0; j < m; j++) {
            while (r > 0 && height[stk[r - 1]] >= height[j]) {
                int cur = stk[--r];
                if (height[cur] > height[j]) {
                    int left = r > 0 ? stk[r - 1] : -1;
                    int len = j - left - 1;
                    int leftH = left != -1 ? height[left] : 0;
                    int bottom = leftH > height[j] ? leftH : height[j];
                    ans += (height[cur] - bottom) * len * (len + 1) / 2;
                }
            }
            stk[r++] = j;
        }
        while (r > 0) {
            int cur = stk[--r], left = r > 0 ? stk[r - 1] : -1;
            int len = m - left - 1;
            int leftH = left != -1 ? height[left] : 0;
            ans += (height[cur] - leftH) * len * (len + 1) / 2;
        }
    }
    return ans;
}
```
