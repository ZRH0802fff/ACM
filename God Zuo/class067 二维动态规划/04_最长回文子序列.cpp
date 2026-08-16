// 最长回文子序列
// 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度
// 测试链接 : https://leetcode.cn/problems/longest-palindromic-subsequence/

#include <bits/stdc++.h>
using namespace std;

// s.length() <= 1000
const int MAXN = 1001;

int dp[MAXN][MAXN];
int dp1D[MAXN];

class Solution {
public:

	// 最长回文子序列问题可以转化成最长公共子序列问题
	// 不过这里讲述区间动态规划的思路
	// 区间dp还会有单独的视频做详细讲述
	int longestPalindromeSubseq1(string str) {
		int n = str.length();
		return f1(str, 0, n - 1);
	}

	// s[l...r]最长回文子序列长度
	// l <= r
	int f1(string& s, int l, int r) {
		if (l == r) {
			return 1;
		}
		if (l + 1 == r) {
			return s[l] == s[r] ? 2 : 1;
		}
		if (s[l] == s[r]) {
			return 2 + f1(s, l + 1, r - 1);
		} else {
			return max(f1(s, l + 1, r), f1(s, l, r - 1));
		}
	}

	int longestPalindromeSubseq2(string str) {
		int n = str.length();
		memset(dp, 0, sizeof(dp));
		return f2(str, 0, n - 1);
	}

	int f2(string& s, int l, int r) {
		if (l == r) {
			return 1;
		}
		if (l + 1 == r) {
			return s[l] == s[r] ? 2 : 1;
		}
		if (dp[l][r] != 0) {
			return dp[l][r];
		}
		int ans;
		if (s[l] == s[r]) {
			ans = 2 + f2(s, l + 1, r - 1);
		} else {
			ans = max(f2(s, l + 1, r), f2(s, l, r - 1));
		}
		dp[l][r] = ans;
		return ans;
	}

	// 严格位置依赖的动态规划
	int longestPalindromeSubseq3(string str) {
		int n = str.length();
		memset(dp, 0, sizeof(dp));
		for (int l = n - 1; l >= 0; l--) {
			dp[l][l] = 1;
			if (l + 1 < n) {
				dp[l][l + 1] = str[l] == str[l + 1] ? 2 : 1;
			}
			for (int r = l + 2; r < n; r++) {
				if (str[l] == str[r]) {
					dp[l][r] = 2 + dp[l + 1][r - 1];
				} else {
					dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
				}
			}
		}
		return dp[0][n - 1];
	}

	// 严格位置依赖的动态规划 + 空间压缩（Java 的 longestPalindromeSubseq4，作为 LeetCode 提交方法 longestPalindromeSubseq）
	int longestPalindromeSubseq(string str) {
		int n = str.length();
		for (int l = n - 1, leftDown = 0, backup; l >= 0; l--) {
			// dp[l] : 想象中的dp[l][l]
			dp1D[l] = 1;
			if (l + 1 < n) {
				leftDown = dp1D[l + 1];
				// dp[l+1] : 想象中的dp[l][l+1]
				dp1D[l + 1] = str[l] == str[l + 1] ? 2 : 1;
			}
			for (int r = l + 2; r < n; r++) {
				backup = dp1D[r];
				if (str[l] == str[r]) {
					dp1D[r] = 2 + leftDown;
				} else {
					dp1D[r] = max(dp1D[r], dp1D[r - 1]);
				}
				leftDown = backup;
			}
		}
		return dp1D[n - 1];
	}

};

int main() {
	Solution sol;
	cout << sol.longestPalindromeSubseq("bbbab") << endl; // 4
	cout << sol.longestPalindromeSubseq("cbbd") << endl;  // 2
	return 0;
}
