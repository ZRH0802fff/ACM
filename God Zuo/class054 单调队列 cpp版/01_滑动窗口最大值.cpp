// 滑动窗口最大值（单调队列经典用法模版）
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧
// 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回 滑动窗口中的最大值 。
// 测试链接 : https://leetcode.cn/problems/sliding-window-maximum/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int q[MAXN];
int h, t;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0 || k == 0) return {};
        int m = n - k + 1;
        vector<int> ans(m);
        h = t = 0;

        // 1. 先形成长度为 k-1 的窗口
        for (int i = 0; i < k - 1; i++) {
            while (h < t && nums[q[t - 1]] <= nums[i]) t--;
            q[t++] = i;
        }

        // 2. 窗口补齐为 k，同步滑动
        for (int l = 0, r; l < m; l++) {
            r = l + k - 1;
            while (h < t && nums[q[t - 1]] <= nums[r]) t--;
            q[t++] = r;
            ans[l] = nums[q[h]];
            if (q[h] == l) h++;
        }
        return ans;
    }
};
