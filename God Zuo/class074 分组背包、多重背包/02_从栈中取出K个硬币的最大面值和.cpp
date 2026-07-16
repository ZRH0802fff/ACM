// 从栈中取出K个硬币的最大面值和
// 一张桌子上总共有 n 个硬币 栈 。每个栈有 正整数 个带面值的硬币
// 每一次操作中，你可以从任意一个栈的 顶部 取出 1 个硬币，从栈中移除它，并放入你的钱包里
// 给你一个列表 piles ，其中 piles[i] 是一个整数数组
// 分别表示第 i 个栈里 从顶到底 的硬币面值。同时给你一个正整数 k
// 请你返回在 恰好 进行 k 次操作的前提下，你钱包里硬币面值之和 最大为多少
// 测试链接 : https://leetcode.cn/problems/maximum-value-of-k-coins-from-piles/
// 核心: 每组(栈)只能从顶部取, 预处理前缀和; dp[i][j]=max(dp[i-1][j], dp[i-1][j-k]+preSum[k])
// 坑点: ①前缀和只需预处理到 min(栈大小, m) ②空间压缩时 j 倒序
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // piles是一组一组的硬币
    // m是容量，表示一定要进行m次操作
    // dp[i][j] : 1~i组上，一共拿走j个硬币的情况下，获得的最大价值
    // 1) 不要i组的硬币 : dp[i-1][j]
    // 2) i组里尝试每一种方案
    // 比如，i组里拿走前k个硬币的方案 : dp[i-1][j-k] + 从顶部开始前k个硬币的价值和
    // 枚举每一个k，选出最大值
    int maxValueOfCoins1(vector<vector<int>>& piles, int m) {
        int n = piles.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            // i从1组开始，但piles从下标0开始，所以取i-1
            vector<int>& team = piles[i - 1];
            int t = min((int)team.size(), m);
            // 预处理前缀和，为了加速计算
            vector<int> preSum(t + 1, 0);
            for (int j = 0, sum = 0; j < t; j++) {
                sum += team[j];
                preSum[j + 1] = sum;
            }
            // 更新动态规划表
            for (int j = 0; j <= m; j++) {
                // 当前组一个硬币也不拿的方案
                dp[i][j] = dp[i - 1][j];
                for (int k = 1; k <= min(t, j); k++) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + preSum[k]);
                }
            }
        }
        return dp[n][m];
    }

    // 空间压缩
    int maxValueOfCoins(vector<vector<int>>& piles, int m) {
        vector<int> dp(m + 1, 0);
        for (vector<int>& team : piles) {
            int t = min((int)team.size(), m);
            vector<int> preSum(t + 1, 0);
            for (int j = 0, sum = 0; j < t; j++) {
                sum += team[j];
                preSum[j + 1] = sum;
            }
            for (int j = m; j > 0; j--) {
                for (int k = 1; k <= min(t, j); k++) {
                    dp[j] = max(dp[j], dp[j - k] + preSum[k]);
                }
            }
        }
        return dp[m];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> piles = {{1, 100, 3}, {7, 8, 9}};
    int k = 2;
    cout << sol.maxValueOfCoins(piles, k) << endl;

    piles = {{100}, {100}, {100}, {100}, {100}, {100}, {1,1,1,1,1,1,700}};
    k = 7;
    cout << sol.maxValueOfCoins(piles, k) << endl;
    return 0;
}
