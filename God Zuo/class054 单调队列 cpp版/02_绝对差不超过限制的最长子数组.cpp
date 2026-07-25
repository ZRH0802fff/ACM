// 绝对差不超过限制的最长连续子数组 — LeetCode 1438
// max - min <= limit 的最长子数组

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int maxQ[MAXN], minQ[MAXN];
int maxH, maxT, minH, minT;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        maxH = maxT = minH = minT = 0;
        int ans = 0;
        // [l, r) 窗口，r 是下一个要进入的数
        for (int l = 0, r = 0; l < n; l++) {
            while (r < n && ok(nums, limit, nums[r])) {
                push(nums, r);
                r++;
            }
            int len = r - l;
            if (len > ans) ans = len;
            pop(l);
        }
        return ans;
    }

    bool ok(vector<int>& nums, int limit, int number) {
        int maxVal = number;
        if (maxH < maxT && nums[maxQ[maxH]] > number)
            maxVal = nums[maxQ[maxH]];
        int minVal = number;
        if (minH < minT && nums[minQ[minH]] < number)
            minVal = nums[minQ[minH]];
        return maxVal - minVal <= limit;
    }

    void push(vector<int>& nums, int r) {
        while (maxH < maxT && nums[maxQ[maxT - 1]] <= nums[r]) maxT--;
        maxQ[maxT++] = r;
        while (minH < minT && nums[minQ[minT - 1]] >= nums[r]) minT--;
        minQ[minT++] = r;
    }

    void pop(int l) {
        if (maxH < maxT && maxQ[maxH] == l) maxH++;
        if (minH < minT && minQ[minH] == l) minH++;
    }
};
