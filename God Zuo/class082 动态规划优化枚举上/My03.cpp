// 买卖股票的最佳时机 III
// 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易
// 注意：你不能同时参与多笔交易，你必须在再次购买前出售掉之前的股票
// 测试链接 : https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii

#include<bits/stdc++.h>
using namespace std;

int dp1[100010];
int dp2[100010];
int n,ans;
class Solution {
public:
    
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        for(int i = 0; i <= n; i++) {
            dp1[i] = 0;
            dp2[i] = 0;
        }
        //dp1[i] -> 0..i范围上交易一次，最大利润是多少
        for (int i = 1, minVal = prices[0]; i < n; ++i){
            minVal = min(minVal, prices[i]);
            dp1[i] = max(dp1[i - 1], prices[i] - minVal);
        }

        //dp2[i] 0..i范围上发生两次交易，并且第二次交易在i时刻卖出，求最大利润
        ans = 0;
        for (int i = 1; i < n;++i){
            for (int j = 0; j <= i; ++j){
                dp2[i] = max(dp2[i], dp1[j] + prices[i] - prices[j]);
            }
            ans = max(ans, dp2[i]);
        }
        return ans;
    }
};


class Solution {
public:
    int dp1[100010];
    int dp2[100010];
    int best[100010];
    int n, ans;
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        for(int i = 0; i <= n; i++) {
            dp1[i] = 0;
            best[i] = 0;
            dp2[i] = 0;
        }
        for (int i = 1, minVal = prices[0]; i < n; ++i){
            minVal = min(minVal, prices[i]);
            dp1[i] = max(dp1[i - 1], prices[i] - minVal);
        }
        best[0] = -prices[0];
        //best[i] -> 0..i 上最大的 dp1[i]-prices[i]
        for (int i = 1; i < n; ++i){
            best[i] = max(best[i - 1], dp1[i] - prices[i]);
        }
        ans = 0;
        for (int i = 1; i < n; ++i){
            dp2[i] = best[i] + prices[i];
            ans = max(ans, dp2[i]);
        }
        return ans;
    }
};