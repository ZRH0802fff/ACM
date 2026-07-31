// 买卖股票的最佳时机 IV
// 给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易
// 也就是说，你最多可以买 k 次，卖 k 次
// 注意：你不能同时参与多笔交易，你必须在再次购买前出售掉之前的股票
// 测试链接 : https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/

#include<bits/stdc++.h>
using namespace std;

int dp[105][1010];

class Solution {
public:

    int free(vector<int>& prices){
        int ans = 0;
        for (int i = 1; i < prices.size(); ++i){
            ans += max(prices[i] - prices[i - 1], 0);
        }
        return ans;
    }
    //dp[i][j] i笔交易时,前j天可以获得的最大利润
    //最后一笔不是j天卖出 -> dp[i-1][j]
    //是j天卖出  0..p..j 枚举p p买入j卖出 ->max(dp[i-1][p]+pr[j]-pr[p])
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(k>=n/2){
            return free(prices);
        }
        for (int i = 1; i <= k; ++i){
            for (int j = 1; j < n; ++j){
                dp[i][j] = dp[i - 1][j];
                for (int p = 0; p < j; ++p){
                    dp[i][j] = max(dp[i][j], dp[i - 1][p] + prices[j] - prices[i]);
                }
            }
        }
        return dp[k][n - 1];
    }
};


class Solution {
public:

    int free(vector<int>& prices){
        int ans = 0;
        for (int i = 1; i < prices.size(); ++i){
            ans += max(prices[i] - prices[i - 1], 0);
        }
        return ans;
    }
    //dp[i][j] i笔交易时,前j天可以获得的最大利润
    //最后一笔不是j天卖出 -> dp[i-1][j]
    //是j天卖出  0..p..j 枚举p p买入j卖出 ->max(dp[i-1][p]+pr[j]-pr[p])
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(k>=n/2){
            return free(prices);
        }
        for (int i = 1; i <= k; ++i){
            int best = dp[i - 1][0] - prices[0];
            for (int j = 1; j < n; ++j){
                dp[i][j] = max(dp[i][j - 1], best + prices[j]);
                best = max(best, dp[i - 1][j] - prices[j]);
            }
        }
        return dp[k][n - 1];
    }
};
