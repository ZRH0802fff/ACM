# class063 双向广搜 笔记

> 视频：算法讲解063【必备】双向广搜

---

## 用途概述

双向广搜有两大用途：
- **用途一（小优化）**：BFS 从两端展开，哪侧数量少就从哪侧扩，在中间相遇即得最短距离
- **用途二（本体）**：全量暴力展开不可行（如 2^40），但半量展开可行（2^20），左右各自展开再整合，用双指针不回退加速

---

## 题目1：单词接龙（双向广搜用途一）

### 题面
从 beginWord 变到 endWord，每次变一个字母，中间词必须在 wordList 中。求**最短转换序列的单词数**。

- LeetCode 127: https://leetcode.cn/problems/word-ladder/

### 核心思路
**双向 BFS（哪侧小从哪侧扩）**：
- 维护三个集合：`smallLevel`（数量小的一侧）、`bigLevel`（数量大的一侧）、`nextLevel`
- 每次从 small 侧扩展：每个单词每位 a~z 试一遍
- 扩展出的单词如果在 bigLevel 中→相遇，返回 `len`
- 如果在 dict 中→加入 nextLevel，并从 dict 删掉（去重）
- 每次比较 `nextLevel.size()` 和 `bigLevel.size()`，小的一方做下一轮的 small

### 坑点
- 扩展出的单词必须在 dict 中有才入队，且立即从 dict 删除防止重复
- 交换逻辑：小的做 small，大的做 big，next 始终是"从小侧扩出的下一层"

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ladderLength(string begin, string end, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(end)) return 0;
        unordered_set<string> smallLevel, bigLevel, nextLevel;
        smallLevel.insert(begin);
        bigLevel.insert(end);
        for (int len = 2; !smallLevel.empty(); len++) {
            for (const string& w : smallLevel) {
                string word = w;
                for (int j = 0; j < (int)word.length(); j++) {
                    char old = word[j];
                    for (char change = 'a'; change <= 'z'; change++) {
                        if (change != old) {
                            word[j] = change;
                            if (bigLevel.count(word)) return len;
                            if (dict.count(word)) {
                                dict.erase(word);
                                nextLevel.insert(word);
                            }
                        }
                    }
                    word[j] = old;
                }
            }
            if (nextLevel.size() <= bigLevel.size()) {
                swap(smallLevel, nextLevel);
            } else {
                smallLevel.clear();
                swap(smallLevel, bigLevel);
                swap(bigLevel, nextLevel);
            }
            nextLevel.clear();
        }
        return 0;
    }
};
```

---

## 题目2：零食问题 / 世界冰球锦标赛（双向广搜用途二）

### 题面
n 袋零食（n≤40），每袋体积 v[i]（v[i]≤10^9），背包容量 w（w≤2×10^9）。求总体积**不超过 w** 的方案数（不拿也算一种）。答案不取模。

- 牛客 / 洛谷 P4799: https://www.luogu.com.cn/problem/P4799

### 核心思路
**半量展开 + 双指针整合**：
- 全量展开：2^40 ≈ 10^12，不可行
- 分两半：左半 2^20 ≈ 10^6，右半 2^20 ≈ 10^6，各自暴力递归收集所有 ≤ w 的累加和
- 左右排序后双指针：`i` 从 lsum 末尾往左，`j` 从 rsum 开头往右
  - 固定 `lsum[i]`，while `lsum[i] + rsum[j] <= w`：j++
  - `ans += j`（右侧有 j 个方案能和 lsum[i] 组合）
- 复杂度：O(2^(n/2) × n) 可行

### 坑点
- 数值巨大（v[i] 和 w 都可达 2×10^9），用 `long long`
- 递归展开过程中，累加和超过 w 直接剪枝返回
- 双指针不回退：i 递减时 j 只增不减

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40;
const int MAXM = 1 << 20;

long long arr[MAXN];
long long lsum[MAXM];
long long rsum[MAXM];
int n;
long long w;

// arr[i..e-1]范围上展开，到达e就停止
// 返回值 : ans数组填到了什么位置！
int f(int i, int e, long long s, long long w, long long ans[], int j) {
    if (s > w) return j;
    if (i == e) { ans[j++] = s; }
    else {
        j = f(i + 1, e, s, w, ans, j);           // 不要arr[i]
        j = f(i + 1, e, s + arr[i], w, ans, j);  // 要arr[i]
    }
    return j;
}

long long compute() {
    int lsize = f(0, n >> 1, 0, w, lsum, 0);
    int rsize = f(n >> 1, n, 0, w, rsum, 0);
    sort(lsum, lsum + lsize);
    sort(rsum, rsum + rsize);
    long long ans = 0;
    for (int i = lsize - 1, j = 0; i >= 0; i--) {
        while (j < rsize && lsum[i] + rsum[j] <= w) j++;
        ans += j;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> w) {
        for (int i = 0; i < n; i++) cin >> arr[i];
        cout << compute() << '\n';
    }
    return 0;
}
```

---

## 题目3：最接近目标值的子序列和（双向广搜用途二）

### 题面
数组长度 ≤ 40，数值 ±10^7。选一个子序列使累加和与 goal 的绝对差最小，返回最小差值。

- LeetCode 1755: https://leetcode.cn/problems/closest-subsequence-sum/

### 核心思路
**半量展开 + 剪枝 + 双指针**：
- 全量展开 2^40 不行，拆左右各 2^20
- **剪枝**：先算所有正数和 max、所有负数和 min：
  - 若 `max < goal` → 直接返回 `|max-goal|`
  - 若 `min > goal` → 直接返回 `|min-goal|`
- **排序后分组展开**（常数优化）：相同的数字按"选 0/1/2/... 个"一组处理，减少递归层数
- 左右排序后双指针：`i` 从左往右、`j` 从右往左，每步看 `j-1` 是否缩小差值，是则滑

### 坑点
- 排序原数组后分组展开能大幅加速（避免重复递归相同值）
- 双指针不回退：i 递增时 j 只减不增
- 需要先判断 max/min 与 goal 的关系做剪枝

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1 << 20;
int lsum[MAXN], rsum[MAXN], fill_;

void collect(int nums[], int i, int e, int s, int sum[]) {
    if (i == e) { sum[fill_++] = s; }
    else {
        int j = i + 1;
        while (j < e && nums[j] == nums[i]) j++;
        for (int k = 0; k <= j - i; k++) {
            collect(nums, j, e, s + k * nums[i], sum);
        }
    }
}

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        long long minSum = 0, maxSum = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0) maxSum += nums[i];
            else minSum += nums[i];
        }
        if (maxSum < goal) return (int)abs(maxSum - goal);
        if (minSum > goal) return (int)abs(minSum - goal);

        sort(nums.begin(), nums.end());
        static int arr[40];
        for (int i = 0; i < n; i++) arr[i] = nums[i];

        fill_ = 0;
        collect(arr, 0, n >> 1, 0, lsum);
        int lsize = fill_;
        fill_ = 0;
        collect(arr, n >> 1, n, 0, rsum);
        int rsize = fill_;
        sort(lsum, lsum + lsize);
        sort(rsum, rsum + rsize);

        int ans = abs(goal);
        for (int i = 0, j = rsize - 1; i < lsize; i++) {
            while (j > 0 && abs(goal - lsum[i] - rsum[j - 1])
                        <= abs(goal - lsum[i] - rsum[j])) j--;
            ans = min(ans, abs(goal - lsum[i] - rsum[j]));
        }
        return ans;
    }
};
```
