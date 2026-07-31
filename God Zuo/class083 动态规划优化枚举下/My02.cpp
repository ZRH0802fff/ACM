// K个逆序对数组
// 逆序对的定义如下：
// 对于数组nums的第i个和第j个元素
// 如果满足0<=i<j<nums.length 且 nums[i]>nums[j]，则为一个逆序对
// 给你两个整数n和k，找出所有包含从1到n的数字
// 且恰好拥有k个逆序对的不同的数组的个数
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/k-inverse-pairs-array/

#include<bits/stdc++.h>
using namespace std;

int MOD = 1e9 + 7;
int dp[1005][1005];

class Solution {
public:
    // dp[i][j]表示 1,2,3...i 这些数中又j个逆序对的排列数
    int kInversePairs(int n, int k) {
        for (int i = 0; i <= n; ++i){
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i){
            int wd = 1;
            for(int j = 1; j <= k; ++j){
                if(i>j){
                    wd += dp[i - 1][j];
                    wd %= MOD;
                }else{
                    wd = ((wd + dp[i - 1][j]) % MOD - dp[i - 1][j - i] + MOD) % MOD;
                }
                dp[i][j] = wd;
            }
        }
        return dp[n][k];
    }
};