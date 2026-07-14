// 盈利计划(多维费用背包)
// 集团里有 n 名员工，他们可以完成各种各样的工作创造利润
// 第 i 种工作会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与
// 如果成员参与了其中一项工作，就不能参与另一项工作
// 工作的任何至少产生 minProfit 利润的子集称为 盈利计划
// 并且工作的成员总数最多为 n
// 有多少种计划可以选择？因为答案很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/profitable-schemes/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int MOD = 1000000007;

    // 递归尝试
    // i : 来到i号工作
    // r : 员工额度还有r人，如果r<=0说明已经没法再选择工作了
    // s : 利润还有s才能达标，如果s<=0说明之前的选择已经让利润达标了
    // 返回 : i.... r、s，有多少种方案
    int f1(vector<int>& g, vector<int>& p, int i, int r, int s) {
        if (r <= 0) {
            return s <= 0 ? 1 : 0;
        }
        if (i == (int)g.size()) {
            return s <= 0 ? 1 : 0;
        }
        int p1 = f1(g, p, i + 1, r, s);
        int p2 = 0;
        if (g[i] <= r) {
            p2 = f1(g, p, i + 1, r - g[i], s - p[i]);
        }
        return p1 + p2;
    }

    int profitableSchemes1(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        return f1(group, profit, 0, n, minProfit);
    }

    // 记忆化搜索
    int profitableSchemes2(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n + 1, vector<int>(minProfit + 1, -1)));
        return f2(group, profit, 0, n, minProfit, dp);
    }

    int f2(vector<int>& g, vector<int>& p, int i, int r, int s, vector<vector<vector<int>>>& dp) {
        if (r <= 0) {
            return s == 0 ? 1 : 0;
        }
        if (i == (int)g.size()) {
            return s == 0 ? 1 : 0;
        }
        if (dp[i][r][s] != -1) {
            return dp[i][r][s];
        }
        int p1 = f2(g, p, i + 1, r, s, dp);
        int p2 = 0;
        if (g[i] <= r) {
            p2 = f2(g, p, i + 1, r - g[i], max(0, s - p[i]), dp);
        }
        int ans = (p1 + p2) % MOD;
        dp[i][r][s] = ans;
        return ans;
    }

    // 空间压缩版动态规划（LeetCode 提交用）
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
        for (int r = 0; r <= n; r++) {
            dp[r][0] = 1;
        }
        int m = group.size();
        for (int i = m - 1; i >= 0; i--) {
            for (int r = n; r >= 0; r--) {
                for (int s = minProfit; s >= 0; s--) {
                    int p1 = dp[r][s];
                    int p2 = group[i] <= r ? dp[r - group[i]][max(0, s - profit[i])] : 0;
                    dp[r][s] = (p1 + p2) % MOD;
                }
            }
        }
        return dp[n][minProfit];
    }
};

// 测试代码
int main() {
    Solution sol;
    int n = 5, minProfit = 3;
    vector<int> group = {2, 2};
    vector<int> profit = {2, 3};
    cout << "profitableSchemes1: " << sol.profitableSchemes1(n, minProfit, group, profit) << endl;
    cout << "profitableSchemes2: " << sol.profitableSchemes2(n, minProfit, group, profit) << endl;
    cout << "profitableSchemes:  " << sol.profitableSchemes(n, minProfit, group, profit) << endl;

    n = 10; minProfit = 5;
    group = {2, 3, 5};
    profit = {6, 7, 8};
    cout << "profitableSchemes:  " << sol.profitableSchemes(n, minProfit, group, profit) << endl;
    return 0;
}
