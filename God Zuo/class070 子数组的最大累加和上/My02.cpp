// 数组中不能选相邻元素的最大累加和
// 给定一个数组，可以随意选择数字
// 但是不能选择相邻的数字，返回能得到的最大累加和
// 测试链接 : https://leetcode.cn/problems/house-robber/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int rob(vector<int> &nums){
        int n = nums.size();
        if(n==1)
            return nums[0];
        if(n==2)
            return max(nums[0], nums[1]);
        int pre2 = nums[0];
        int pre1 = nums[0] > nums[1] ? nums[0] : nums[1];
        int cur = 0;
        for (int i = 2; i < n;++i){
            cur = max(pre1, max(nums[i], pre2 + nums[i]));
            pre2 = pre1;
            pre1 = cur;
        }
        return pre1;
    }
};