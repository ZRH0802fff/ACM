// 矩阵中和能被 K 整除的路径
// 给一个下标从0开始的 n * m 整数矩阵 grid 和一个整数 k
// 从起点(0,0)出发，每步只能往下或者往右，你想要到达终点(m-1, n-1)
// 请你返回路径和能被 k 整除的路径数目
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/paths-in-matrix-whose-sum-is-divisible-by-k/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int MOD = 1000000007;

    // 递归尝试
    // 当前来到(i,j)位置，最终一定要走到右下角(n-1,m-1)
    // 从(i,j)出发，最终一定要走到右下角(n-1,m-1)，有多少条路径，累加和%k的余数是r
    int f1(vector<vector<int>>& grid, int n, int m, int k, int i, int j, int r) {
        if (i == n - 1 && j == m - 1) {
            return grid[i][j] % k == r ? 1 : 0;
        }
        // 后续需要凑出来的余数need
        int need = (k + r - (grid[i][j] % k)) % k;
        int ans = 0;
        if (i + 1 < n) {
            ans = f1(grid, n, m, k, i + 1, j, need);
        }
        if (j + 1 < m) {
            ans = (ans + f1(grid, n, m, k, i, j + 1, need)) % MOD;
        }
        return ans;
    }

    int numberOfPaths1(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        return f1(grid, n, m, k, 0, 0, 0);
    }

    // 记忆化搜索
    int numberOfPaths2(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, -1)));
        return f2(grid, n, m, k, 0, 0, 0, dp);
    }

    int f2(vector<vector<int>>& grid, int n, int m, int k, int i, int j, int r, vector<vector<vector<int>>>& dp) {
        if (i == n - 1 && j == m - 1) {
            return grid[i][j] % k == r ? 1 : 0;
        }
        if (dp[i][j][r] != -1) {
            return dp[i][j][r];
        }
        int need = (k + r - grid[i][j] % k) % k;
        int ans = 0;
        if (i + 1 < n) {
            ans = f2(grid, n, m, k, i + 1, j, need, dp);
        }
        if (j + 1 < m) {
            ans = (ans + f2(grid, n, m, k, i, j + 1, need, dp)) % MOD;
        }
        dp[i][j][r] = ans;
        return ans;
    }

    // 动态规划（LeetCode 提交用）
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, 0)));
        dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;
        // 最后一列
        for (int i = n - 2; i >= 0; i--) {
            for (int r = 0; r < k; r++) {
                dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
            }
        }
        // 最后一行
        for (int j = m - 2; j >= 0; j--) {
            for (int r = 0; r < k; r++) {
                dp[n - 1][j][r] = dp[n - 1][j + 1][(k + r - grid[n - 1][j] % k) % k];
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            for (int j = m - 2; j >= 0; j--) {
                for (int r = 0; r < k; r++) {
                    int need = (k + r - grid[i][j] % k) % k;
                    dp[i][j][r] = dp[i + 1][j][need];
                    dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % MOD;
                }
            }
        }
        return dp[0][0][0];
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<vector<int>> grid = {{5, 2, 4}, {3, 0, 5}, {0, 7, 2}};
    int k = 3;
    cout << "numberOfPaths1: " << sol.numberOfPaths1(grid, k) << endl;
    cout << "numberOfPaths2: " << sol.numberOfPaths2(grid, k) << endl;
    cout << "numberOfPaths:  " << sol.numberOfPaths(grid, k) << endl;

    grid = {{0, 0}};
    k = 5;
    cout << "numberOfPaths:  " << sol.numberOfPaths(grid, k) << endl;
    return 0;
}
