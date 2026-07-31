// 划分为k个相等的子集
// 给定一个整数数组  nums 和一个正整数 k，
// 找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
// 测试链接 : https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[(1 << 17) + 10];
    int limit, sum, n;

    bool f(vector<int> nums,int status,int cur,int rest){
        if(rest==0)
            return status == 0;
        if(dp[status]!=0)
            return dp[status] == 1;
        bool ans = false;
        for (int i = 0; i < nums.size(); ++i){
            if((status & (1<<i))!=0 && cur+nums[i]<=limit){
                 if(cur+nums[i]==limit){
                    ans = f(nums, status ^ (1 << i), 0, rest - 1);
                 }else{
                     ans = f(nums, status ^ (1 << i), cur + nums[i], rest);
                 }
                 if(ans) break;
            }
        }
        dp[status] = ans ? 1 : -1;
        return ans;
    }

    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int num: nums) sum+=num;
        if(sum%k!=0) return false;
        n = nums.size();
        limit = sum / k;
        for (int i = 0; i < (1 << n); ++i)dp[i]=0;
        return f(nums, (1 << n)-1, 0, k);
    }
};