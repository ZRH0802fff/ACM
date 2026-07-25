// 滑动窗口最大值（单调队列经典用法模版）
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧
// 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回 滑动窗口中的最大值 。
// 测试链接 : https://leetcode.cn/problems/sliding-window-maximum/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int q[100010];
    int n, h, t, l, r;

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        n = nums.size();
        if(n==0 || k==0)
            return {};
        int m = n - k + 1;
        vector<int> ans(m);
        h = t = 0;
        for (int i = 0; i < k - 1; ++i){
            while(h<t && nums[q[t-1]]<=nums[i]) --t;
            q[t++] = i;
        }
        for (l = 0; l < m; ++l){
            r = l + k - 1;
            while(h<t && nums[q[t-1]]<=nums[r]) --t;
            q[t++] = r;
            ans[l] = nums[q[h]];
            if(q[h]==l) ++h;
        }
        return ans;
    }
};