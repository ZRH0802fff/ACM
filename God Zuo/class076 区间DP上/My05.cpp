// 戳气球
// 有 n 个气球，编号为0到n-1，每个气球上都标有一个数字，这些数字存在数组nums中
// 现在要求你戳破所有的气球。戳破第 i 个气球
// 你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币
// 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号
// 如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球
// 求所能获得硬币的最大数量
// 测试链接 : https://leetcode.cn/problems/burst-balloons/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[310][310];

    int f(int *arr, int l,int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans;
        if(l==r)
            ans = arr[l - 1] * arr[l] * arr[r + 1];
        else{
            ans=max(arr[l-1]*arr[l]*arr[r+1]+f(arr,l+1,r)
                   ,arr[l-1]*arr[r]*arr[r+1]+f(arr,l,r-1));
            for (int k = l + 1; k < r; ++k){
                ans = max(ans, arr[l - 1] * arr[k] * arr[r + 1] + f(arr, l, k - 1) + f(arr, k + 1, r));
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        int arr[n + 2];
        arr[0] = 1;
        arr[n + 1] = 1;
        for (int i = 1; i <= n; ++i)
            arr[i] = nums[i - 1];
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j)
                dp[i][j] = -1;
        }
        return f(arr, 1, n);
    }
};