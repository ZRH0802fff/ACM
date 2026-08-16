// 矩阵中的最长递增路径
// 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度
// 对于每个单元格，你可以往上，下，左，右四个方向移动
// 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）
// 测试链接 : https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/

#include<bits/stdc++.h>
using namespace std;

int dp[205][205];
int n,m,ans;

class Solution {
public:
    int f(vector<vector<int>>& grid,int i,int j){
        if(dp[i][j]!=0) return dp[i][j];
        int ans=0;
        if (i>0 && grid[i][j]<grid[i-1][j]) ans=max(ans,f(grid,i-1,j));
        if (j>0 && grid[i][j]<grid[i][j-1]) ans=max(ans,f(grid,i,j-1));
        if (i<grid.size()-1 && grid[i][j]<grid[i+1][j]) ans=max(ans,f(grid,i+1,j));
        if (j<grid[0].size()-1 && grid[i][j]<grid[i][j+1]) ans=max(ans,f(grid,i,j+1));
        dp[i][j]=++ans;
        return ans;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        n=matrix.size();
        m=matrix[0].size();
        for(int i=0;i<n; ++i){
            for(int j=0;j<m ;++j){
                dp[i][j]=0;
            }
        }
        ans=0;
        for(int i=0;i<n; ++i){
            for(int j=0;j<m ;++j){
                ans=max(ans,f(matrix,i,j));
            }
        }
        return ans;
    }
};