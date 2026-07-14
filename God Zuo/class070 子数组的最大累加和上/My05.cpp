// 打家劫舍 IV
// 沿街有一排连续的房屋。每间房屋内都藏有一定的现金
// 现在有一位小偷计划从这些房屋中窃取现金
// 由于相邻的房屋装有相互连通的防盗系统，所以小偷不会窃取相邻的房屋
// 小偷的 窃取能力 定义为他在窃取过程中能从单间房屋中窃取的 最大金额
// 给你一个整数数组 nums 表示每间房屋存放的现金金额
// 另给你一个整数k，表示小偷需要窃取至少 k 间房屋
// 返回小偷需要的最小窃取能力值
// 测试链接 : https://leetcode.cn/problems/house-robber-iv/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:

    int check(vector<int> &nums,int n,int ab){
        if(n==1)
            return nums[0] <= ab ? 1 : 0;
        if(n==2)
            return (nums[0] <= ab || nums[1] <= ab) ? 1 : 0;
        int pre2 = nums[0] <= ab ? 1 : 0;
        int pre1 = (nums[0] <= ab || nums[1] <= ab) ? 1 : 0;
        for (int i = 2, cur; i < n;++i){
            cur = max(pre1, pre2 + (nums[i] <= ab ? 1 : 0));
            pre2 = pre1;
            pre1=cur;
        }
        return pre1;
    }

    int minCapability(vector<int> &nums, int k){
        int n = nums.size();
        int l = nums[0], r = nums[0];
        for (int i = 0; i < n;++i){
            l = nums[i] < l ? nums[i] : l;
            r = nums[i] > r ? nums[i] : r;
        }
        int m, ans = 0;
        while(l<=r){
            m = (l + r) / 2;
            if(check(nums,n,m)>=k){
                ans = m;
                r = m - 1;
            }else{
                l = m + 1;
            }
        }
        return ans;
    }
};