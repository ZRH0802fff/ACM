// 一和零(多维费用背包)
// 给你一个二进制字符串数组 strs 和两个整数 m 和 n
// 请你找出并返回 strs 的最大子集的长度
// 该子集中 最多 有 m 个 0 和 n 个 1
// 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集
// 测试链接 : https://leetcode.cn/problems/ones-and-zeroes/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int zeros, ones;

    // 统计一个字符串中0和1的数量
    void zerosAndOnes(const string& str) {
        zeros = 0;
        ones = 0;
        for (char c : str) {
            if (c == '0') {
                zeros++;
            } else {
                ones++;
            }
        }
    }

    // 递归尝试
    // strs[i....]自由选择，希望零的数量不超过z、一的数量不超过o
    // 最多能选多少个字符串
    int f1(vector<string>& strs, int i, int z, int o) {
        if (i == (int)strs.size()) {
            return 0;
        }
        // 不使用当前的strs[i]字符串
        int p1 = f1(strs, i + 1, z, o);
        // 使用当前的strs[i]字符串
        int p2 = 0;
        zerosAndOnes(strs[i]);
        if (zeros <= z && ones <= o) {
            p2 = 1 + f1(strs, i + 1, z - zeros, o - ones);
        }
        return max(p1, p2);
    }

    int findMaxForm1(vector<string>& strs, int m, int n) {
        return f1(strs, 0, m, n);
    }

    // 记忆化搜索
    int findMaxForm2(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        return f2(strs, 0, m, n, dp);
    }

    int f2(vector<string>& strs, int i, int z, int o, vector<vector<vector<int>>>& dp) {
        if (i == (int)strs.size()) {
            return 0;
        }
        if (dp[i][z][o] != -1) {
            return dp[i][z][o];
        }
        int p1 = f2(strs, i + 1, z, o, dp);
        int p2 = 0;
        zerosAndOnes(strs[i]);
        if (zeros <= z && ones <= o) {
            p2 = 1 + f2(strs, i + 1, z - zeros, o - ones, dp);
        }
        int ans = max(p1, p2);
        dp[i][z][o] = ans;
        return ans;
    }

    // 三维动态规划
    int findMaxForm3(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        for (int i = len - 1; i >= 0; i--) {
            zerosAndOnes(strs[i]);
            for (int z = 0; z <= m; z++) {
                for (int o = 0; o <= n; o++) {
                    int p1 = dp[i + 1][z][o];
                    int p2 = 0;
                    if (zeros <= z && ones <= o) {
                        p2 = 1 + dp[i + 1][z - zeros][o - ones];
                    }
                    dp[i][z][o] = max(p1, p2);
                }
            }
        }
        return dp[0][m][n];
    }

    // 空间压缩（LeetCode 提交用）
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (const string& s : strs) {
            zerosAndOnes(s);
            for (int z = m; z >= zeros; z--) {
                for (int o = n; o >= ones; o--) {
                    dp[z][o] = max(dp[z][o], 1 + dp[z - zeros][o - ones]);
                }
            }
        }
        return dp[m][n];
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;
    cout << "findMaxForm1: " << sol.findMaxForm1(strs, m, n) << endl;
    cout << "findMaxForm2: " << sol.findMaxForm2(strs, m, n) << endl;
    cout << "findMaxForm3: " << sol.findMaxForm3(strs, m, n) << endl;
    cout << "findMaxForm:  " << sol.findMaxForm(strs, m, n) << endl;

    strs = {"10", "0", "1"};
    m = 1; n = 1;
    cout << "findMaxForm:  " << sol.findMaxForm(strs, m, n) << endl;
    return 0;
}
