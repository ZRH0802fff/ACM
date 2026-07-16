// 目标和
// 给你一个非负整数数组 nums 和一个整数 target 。
// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数
// 可以构造一个表达式
// 例如nums=[2, 1]，可以在2之前添加'+' ，在1之前添加'-'
// 然后串联起来得到表达式 "+2-1" 。
// 返回可以通过上述方法构造的，运算结果等于 target 的不同表达式的数目
// 测试链接 : https://leetcode.cn/problems/target-sum/
// 核心: 转化为01背包: sum(A) = (target + sum)/2, 求子集累加和为t的方案数
//       奇偶性剪枝: sum<target || (target^sum)&1 直接返回0
// 坑点: ① 负数平移技巧: dp[i][j] -> dp[i][j+sum] ② 累加和可能很大, dp数组要开够


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[25][2010] = {};

    int findTargetSumWays(vector<int>& nums, int target) {
        int s = 0;
        for(int num:nums)
            s += num;
        int n = nums.size();
        int m = 2 * s + 1;
        for (int i = n - 1; i >= 0 ;--i){
            for (int j = -s; j <= s;++j){
                if(j+s+nums[i]<m){
                    dp[i][j + s] = dp[i + 1][j + nums[i] + s];
                }
            }
        }
    }
};


class Solution {
public:
    int dp[100010]={};
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(int n:nums)
            sum += n;
        if (sum < target || ((target ^ sum) & 1))
            return 0;
        int tsum = (target + sum) / 2;
        if(tsum<0)
            return 0;
        dp[0] = 1;
        for (int num: nums){
            for (int j = tsum; j >= num;--j){
                dp[j] += dp[j - num];
            }
        }
        return dp[tsum];
    }  
};