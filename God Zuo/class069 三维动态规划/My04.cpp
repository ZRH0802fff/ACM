// 测试链接 : https://leetcode.cn/problems/paths-in-matrix-whose-sum-is-divisible-by-k/
#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    const int MOD = 1000000007;
    vector<vector<vector<int>>> dp;
    int f(vector<vector<int>> &grid, int n, int m, int k, int i, int j, int r){
        if(i==n-1 && j==m-1)
            return grid[i][j] % k == r ? 1 : 0;
        if(dp[i][j][r]!=-1)
            return dp[i][j][r];
        int need = (k + r - (grid[i][j] % k)) % k;
        int ans = 0;
        if(i+1<n)
            ans = f(grid, n, m, k, i + 1, j, need)%MOD;
        if(j+1<m)
            ans = (ans+f(grid, n, m, k, i, j + 1, need))%MOD;
        dp[i][j][r] = ans;
        return ans;
    }

    int numberOfPaths(vector<vector<int>> &grid, int k){
        int n = grid.size();
        int m = grid[0].size();
        dp.assign(n, vector<vector<int>>(m, vector<int>(k, -1)));
        return f(grid, n, m, k, 0, 0, 0);
    }
};

class Solution
{
public:
    const int MOD = 1000000007;
    vector<vector<vector<int>>> dp;
    
    int numberOfPaths(vector<vector<int>> &grid, int k){
        int n = grid.size();
        int m = grid[0].size();
        dp.assign(n, vector<vector<int>>(m, vector<int>(k, 0)));
        dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;
        for (int i = n - 2; i >= 0;--i){
            for (int r = 0; r < k;++r){
                dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
            }
        }
        for (int j = m - 2; j >= 0; j--)
        {
            for (int r = 0; r < k; r++)
            {
                dp[n - 1][j][r] = dp[n - 1][j + 1][(k + r - grid[n - 1][j] % k) % k];
            }
        }
        for (int i = n - 2; i >= 0;--i){
            for (int j = m - 2; j >= 0;--j){
                for (int r = 0; r < k;++r){
                    int need = (k + r - grid[i][j] % k) % k;
                    dp[i][j][r] = dp[i + 1][j][need];
                    dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % MOD;
                }
            }
        }
        return dp[0][0][0];
    }    
};