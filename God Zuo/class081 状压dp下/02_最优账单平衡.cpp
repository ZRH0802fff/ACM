// 最优账单平衡
// 给你一个表示交易的数组 transactions
// 其中 transactions[i] = [fromi, toi, amounti]
// 表示 ID = fromi 的人给 ID = toi 的人共计 amounti
// 请你计算并返回还清所有债务的最小交易笔数
// 测试链接 : https://leetcode.cn/problems/optimal-account-balancing/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 13;
const int MAXS = 1 << MAXN;
int dp[MAXS]; 

class Solution {
public:
    // 题目说了人员编号的最大范围：0 ~ 12
    int minTransfers(vector<vector<int>>& transactions) {
        // 加工出来的debt数组中一定不含有0
        vector<int> debt = debts(transactions);
        int n = debt.size();
        memset(dp, -1, sizeof(dp));
        return n - f(debt, (1 << n) - 1, 0, n);
    }

    vector<int> debts(vector<vector<int>>& transactions) {
        int help[MAXN] = {};
        for (auto& tran : transactions) {
            help[tran[0]] -= tran[2];
            help[tran[1]] += tran[2];
        }
        int n = 0;
        for (int num : help) {
            if (num != 0) {
                n++;
            }
        }
        vector<int> debt(n);
        int index = 0;
        for (int num : help) {
            if (num != 0) {
                debt[index++] = num;
            }
        }
        return debt;
    }

    // set : 还剩哪些人的债务没解决
    // sum : 当前集合的债务和
    // 返回 : set这个集合最多能划分成多少组累加和为0的小集合
    int f(vector<int>& debt, int set, int sum, int n) {
        if (dp[set] != -1) {
            return dp[set];
        }
        int ans = 0;
        if ((set & (set - 1)) != 0) { // 集合中不只一个元素
            if (sum == 0) {
                for (int i = 0; i < n; i++) {
                    if ((set & (1 << i)) != 0) {
                        // 找到任何一个元素，去除这个元素
                        // 剩下的集合进行尝试，返回值 + 1
                        ans = f(debt, set ^ (1 << i), sum - debt[i], n) + 1;
                        // 然后不需要再尝试下一个元素了，因为答案一定是一样的
                        // 所以直接break
                        break;
                    }
                }
            } else {
                for (int i = 0; i < n; i++) {
                    if ((set & (1 << i)) != 0) {
                        ans = max(ans, f(debt, set ^ (1 << i), sum - debt[i], n));
                    }
                }
            }
        }
        dp[set] = ans;
        return ans;
    }
};
