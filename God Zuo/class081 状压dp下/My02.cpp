// 最优账单平衡
// 给你一个表示交易的数组 transactions
// 其中 transactions[i] = [fromi, toi, amounti]
// 表示 ID = fromi 的人给 ID = toi 的人共计 amounti
// 请你计算并返回还清所有债务的最小交易笔数
// 测试链接 : https://leetcode.cn/problems/optimal-account-balancing/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[1 << 13];
    int n;

    int f(int debt[],int set,int sum){
        if(dp[set]!=-1) return dp[set];
        int ans = 0;
        if(set & (set-1)!=0){
            if(sum==0){
                for (int i = 0; i < n;++i){
                    if(set & (1<<i)!=0){
                        ans = f(debt, set ^ (1 << i), sum - debt[i]) + 1;
                        break;
                    }
                }
            }else{
                for (int i = 0; i < n; ++i){
                    if(set & (1<<i)!=0){
                        ans = max(ans, f(debt, set ^ (1 << i), sum - debt[i]));
                    }
                }
            }
        }
        dp[set] = ans;
        return ans;
    }

    int minTransfers(vector<vector<int>>& transactions) {
        int help[13];
        for(auto& t:transactions){
            help[t[0]] -= t[2];
            help[t[1]] += t[2];
        }
        for(int num:help){
            if(num!=0) ++n;
        }
        int debt[n];
        int idx = 0;
        for(int num:help){
            if(num != 0){
                debt[idx++] = num;
            }
        }
        for (int i = 0; i < (1<<n); ++i){
            dp[i] = -1;
        }
        return f(debt, (1 << n) - 1, 0);
    }
};
