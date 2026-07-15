// 可以翻转1次的情况下子数组最大累加和
// 给定一个数组nums，
// 现在允许你随意选择数组连续一段进行翻转，也就是子数组逆序的调整
// 比如翻转[1,2,3,4,5,6]的[2~4]范围，得到的是[1,2,5,4,3,6]
// 返回必须随意翻转1次之后，子数组的最大累加和
// 对数器验证

#include<bits/stdc++.h>
using namespace std;

int sta[10010];

// 核心
// 反转后得到最大累加和，这个子数组累加和的区间一定又一部分是翻转得来的，很容易排除翻转区间都在子数组内或者子数组完全被包含在翻转区间内的可能。
// 0..i-1 i...n-1
// 用maxend得到前面的最大子数组累加和，这一部分用于翻转到i前面
// sta[i]表示必须以i开头的最大子数组累加和，这部分是没有翻转的。
// 枚举每一个i位置就能得到最终答案。

// 坑点
// 比如 [-1,-6,-5,4,-2,-3]
// 最大是5，由maxend得到，对应的是无有效翻转的情况（只翻转一个数字），要加一层判断

int f2(vector<int>& nums){
    int n = nums.size();
    sta[n - 1] = nums[n - 1];
    for (int i = n - 1; i >= 0;--i){
        sta[i] = nums[i] > nums[i] + sta[i + 1] ? nums[i] : nums[i] + sta[i + 1];
    }
    int ans = sta[0];
    int end = nums[0];
    int maxend = nums[0];
    for (int i = 1; i < n;++i){
        ans = max(ans, maxend + sta[i]);
        end = max(nums[i], nums[i] + end);
        maxend = max(maxend, end);
    }
    ans = max(ans, maxend);
    return ans;
}