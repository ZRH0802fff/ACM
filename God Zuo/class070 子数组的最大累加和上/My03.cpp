// 环形数组的子数组最大累加和
// 给定一个数组nums，长度为n
// nums是一个环形数组，下标0和下标n-1是连在一起的
// 返回环形数组中，子数组最大累加和
// 测试链接 : https://leetcode.cn/problems/maximum-sum-circular-subarray/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int maxSubarraySumCircular(vector<int> &nums){
        int n = nums.size();
        int all = nums[0], maxsum = nums[0], minsum = nums[0],maxpre=nums[0],minpre=nums[0];
        for (int i = 1; i < n;++i){
            all += nums[i];
            maxpre = max(nums[i], nums[i] + maxpre);
            maxsum = maxpre > maxsum ? maxpre : maxsum;
            minpre = min(nums[i], minpre + nums[i]);
            minsum = minsum < minpre ? minsum : minpre;
            
        }
        return all == minsum ? maxsum : max(maxsum, all - minsum);
    }
};