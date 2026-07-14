// 子序列累加和必须被7整除的最大累加和
// 给定一个非负数组nums，
// 可以任意选择数字组成子序列，但是子序列的累加和必须被7整除
// 返回最大累加和
// 对数器验证

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
int dp[MAXN][7];

// dp[i][j]表示nums[0...i-1]中有子序列累加和余j ->所求即为dp[n][0]
// 可能性有两种，一种是不要i-1个数，直接等于dp[i-1][j]
// 另一种是要i-1个数，为dp[i-1][need]+nums[i-1]
// 其中，need也要分两种情况：比如原来需要余4，nums[i-1]余3，则need=j-nums[i-1]%7,若是nums[i-1]余5，则need需要再加一个7，因此总结出need=(7+j-nums[i-1])%7
int f2(vector<int>& nums){
    int n = nums.size();
    dp[0][0] = 0;
    for (int j = 0; j < 7;++j){
        dp[0][j] = -1;
    }
    int x, cur, need;
    for (int i = 1; i < n;++i){
        x = nums[i - 1];
        cur = nums[i - 1] % 7;
        for (int j = 0; j < 7;++j){
            dp[i][j] = dp[i - 1][j];
            need = (7 + j - cur) % 7;
            if (dp[i - 1][need] != -1){
                dp[i][j] = max(dp[i][j], dp[i - 1][need] + x);
            }
        }
    }
    return dp[n][0];
}
