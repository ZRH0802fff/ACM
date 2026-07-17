// 预测赢家
// 给你一个整数数组 nums 。玩家 1 和玩家 2 基于这个数组设计了一个游戏
// 玩家 1 和玩家 2 轮流进行自己的回合，玩家 1 先手
// 开始时，两个玩家的初始分值都是 0
// 每一回合，玩家从数组的任意一端取一个数字
// 取到的数字将会从数组中移除，数组长度减1
// 玩家选中的数字将会加到他的得分上
// 当数组中没有剩余数字可取时游戏结束
// 如果玩家 1 能成为赢家，返回 true
// 如果两个玩家得分相等，同样认为玩家 1 是游戏的赢家，也返回 true
// 你可以假设每个玩家的玩法都会使他的分数最大化
// 测试链接 : https://leetcode.cn/problems/predict-the-winner/

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int dp[25][25];

    int f(vector<int>& nums,int l, int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans;
        if (l == r){
            ans = nums[l];
        }else if(l==r-1){
            ans = nums[l] > nums[r] ? nums[l] : nums[r];
        }else{
            int p1 = nums[l] + min(f(nums, l + 2, r), f(nums, l + 1, r - 1));
            int p2 = nums[r] + min(f(nums, l + 1, r - 1), f(nums, l, r - 2));
            ans = max(p1, p2);
        }
        dp[l][r] = ans;
        return ans;
    }

    bool predictTheWinner(vector<int>& nums) {
        int sum = 0;
        int n = nums.size();
        for(int n:nums)
            sum += n;
        for (int i = 0; i < n;++i){
            for (int j = 0; j < n;++j)
                dp[i][j] = -1;
        }
        int f1 = f(nums, 0, n - 1);
        int f2 = sum - f1;
        return f1 >= f2;
    }
};