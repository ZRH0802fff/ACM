// 最小路径和
// 给定一个包含非负整数的 m x n 网格 grid
// 请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
// 说明：每次只能向下或者向右移动一步。
// 测试链接 : https://leetcode.cn/problems/minimum-path-sum/

#include <bits/stdc++.h>
using namespace std;

// m, n <= 200
const int MAXN = 201;
const int MAXM = 201;

int dp[MAXN][MAXM];
int dp1D[MAXM];

class Solution {
public:

	// 暴力递归
	int minPathSum1(vector<vector<int>>& grid) {
		return f1(grid, (int)grid.size() - 1, (int)grid[0].size() - 1);
	}

	// 从(0,0)到(i,j)最小路径和
	// 一定每次只能向右或者向下
	int f1(vector<vector<int>>& grid, int i, int j) {
		if (i == 0 && j == 0) {
			return grid[0][0];
		}
		int up = INT_MAX;
		int left = INT_MAX;
		if (i - 1 >= 0) {
			up = f1(grid, i - 1, j);
		}
		if (j - 1 >= 0) {
			left = f1(grid, i, j - 1);
		}
		return grid[i][j] + min(up, left);
	}

	// 记忆化搜索
	int minPathSum2(vector<vector<int>>& grid) {
		memset(dp, -1, sizeof(dp));
		return f2(grid, (int)grid.size() - 1, (int)grid[0].size() - 1);
	}

	int f2(vector<vector<int>>& grid, int i, int j) {
		if (dp[i][j] != -1) {
			return dp[i][j];
		}
		int ans;
		if (i == 0 && j == 0) {
			ans = grid[0][0];
		} else {
			int up = INT_MAX;
			int left = INT_MAX;
			if (i - 1 >= 0) {
				up = f2(grid, i - 1, j);
			}
			if (j - 1 >= 0) {
				left = f2(grid, i, j - 1);
			}
			ans = grid[i][j] + min(up, left);
		}
		dp[i][j] = ans;
		return ans;
	}

	// 严格位置依赖的动态规划
	int minPathSum3(vector<vector<int>>& grid) {
		int n = grid.size();
		int m = grid[0].size();
		dp[0][0] = grid[0][0];
		for (int i = 1; i < n; i++) {
			dp[i][0] = dp[i - 1][0] + grid[i][0];
		}
		for (int j = 1; j < m; j++) {
			dp[0][j] = dp[0][j - 1] + grid[0][j];
		}
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < m; j++) {
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[n - 1][m - 1];
	}

	// 严格位置依赖的动态规划 + 空间压缩技巧（Java 的 minPathSum4，作为 LeetCode 提交方法 minPathSum）
	int minPathSum(vector<vector<int>>& grid) {
		int n = grid.size();
		int m = grid[0].size();
		// 先让dp表，变成想象中的表的第0行的数据
		dp1D[0] = grid[0][0];
		for (int j = 1; j < m; j++) {
			dp1D[j] = dp1D[j - 1] + grid[0][j];
		}
		for (int i = 1; i < n; i++) {
			// i = 1，dp表变成想象中二维表的第1行的数据
			// i = 2，dp表变成想象中二维表的第2行的数据
			// ...
			// i = n-1，dp表变成想象中二维表的第n-1行的数据
			dp1D[0] += grid[i][0];
			for (int j = 1; j < m; j++) {
				dp1D[j] = min(dp1D[j - 1], dp1D[j]) + grid[i][j];
			}
		}
		return dp1D[m - 1];
	}

};

int main() {
	Solution sol;
	vector<vector<int>> grid = { {1, 3, 1}, {1, 5, 1}, {4, 2, 1} };
	cout << sol.minPathSum(grid) << endl; // 7
	return 0;
}
