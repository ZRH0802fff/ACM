// 矩阵中的最长递增路径
// 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度
// 对于每个单元格，你可以往上，下，左，右四个方向移动
// 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）
// 测试链接 : https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/

#include <bits/stdc++.h>
using namespace std;

// m, n <= 200
const int MAXN = 201;
const int MAXM = 201;

int dp[MAXN][MAXM];

class Solution {
public:

	int longestIncreasingPath1(vector<vector<int>>& grid) {
		int ans = 0;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				ans = max(ans, f1(grid, i, j));
			}
		}
		return ans;
	}

	// 从(i,j)出发，能走出来多长的递增路径，返回最长长度
	int f1(vector<vector<int>>& grid, int i, int j) {
		int next = 0;
		if (i > 0 && grid[i][j] < grid[i - 1][j]) {
			next = max(next, f1(grid, i - 1, j));
		}
		if (i + 1 < (int)grid.size() && grid[i][j] < grid[i + 1][j]) {
			next = max(next, f1(grid, i + 1, j));
		}
		if (j > 0 && grid[i][j] < grid[i][j - 1]) {
			next = max(next, f1(grid, i, j - 1));
		}
		if (j + 1 < (int)grid[0].size() && grid[i][j] < grid[i][j + 1]) {
			next = max(next, f1(grid, i, j + 1));
		}
		return next + 1;
	}

	// 记忆化搜索（Java 的 longestIncreasingPath2，作为 LeetCode 提交方法 longestIncreasingPath）
	int longestIncreasingPath(vector<vector<int>>& grid) {
		memset(dp, 0, sizeof(dp));
		int ans = 0;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				ans = max(ans, f2(grid, i, j));
			}
		}
		return ans;
	}

	int f2(vector<vector<int>>& grid, int i, int j) {
		if (dp[i][j] != 0) {
			return dp[i][j];
		}
		int next = 0;
		if (i > 0 && grid[i][j] < grid[i - 1][j]) {
			next = max(next, f2(grid, i - 1, j));
		}
		if (i + 1 < (int)grid.size() && grid[i][j] < grid[i + 1][j]) {
			next = max(next, f2(grid, i + 1, j));
		}
		if (j > 0 && grid[i][j] < grid[i][j - 1]) {
			next = max(next, f2(grid, i, j - 1));
		}
		if (j + 1 < (int)grid[0].size() && grid[i][j] < grid[i][j + 1]) {
			next = max(next, f2(grid, i, j + 1));
		}
		dp[i][j] = next + 1;
		return next + 1;
	}

};

int main() {
	Solution sol;
	vector<vector<int>> grid = { {9, 9, 4}, {6, 6, 8}, {2, 1, 1} };
	cout << sol.longestIncreasingPath(grid) << endl; // 4
	return 0;
}
