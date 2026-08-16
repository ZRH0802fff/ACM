// 最长公共子序列
// 给定两个字符串text1和text2
// 返回这两个字符串的最长 公共子序列 的长度
// 如果不存在公共子序列，返回0
// 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列
// 测试链接 : https://leetcode.cn/problems/longest-common-subsequence/

#include <bits/stdc++.h>
using namespace std;

// text1/text2 长度 <= 1000
const int MAXN = 1001;
const int MAXM = 1001;

int dp[MAXN][MAXM];
int dp1D[MAXM];

class Solution {
public:

	int longestCommonSubsequence1(string str1, string str2) {
		int n = str1.length();
		int m = str2.length();
		return f1(str1, str2, n - 1, m - 1);
	}

	// s1[0....i1]与s2[0....i2]最长公共子序列长度
	int f1(string& s1, string& s2, int i1, int i2) {
		if (i1 < 0 || i2 < 0) {
			return 0;
		}
		int p1 = f1(s1, s2, i1 - 1, i2 - 1);
		int p2 = f1(s1, s2, i1 - 1, i2);
		int p3 = f1(s1, s2, i1, i2 - 1);
		int p4 = s1[i1] == s2[i2] ? (p1 + 1) : 0;
		return max(max(p1, p2), max(p3, p4));
	}

	// 为了避免很多边界讨论
	// 很多时候往往不用下标来定义尝试，而是用长度来定义尝试
	// 因为长度最短是0，而下标越界的话讨论起来就比较麻烦
	int longestCommonSubsequence2(string str1, string str2) {
		int n = str1.length();
		int m = str2.length();
		return f2(str1, str2, n, m);
	}

	// s1[前缀长度为len1]对应s2[前缀长度为len2]
	// 最长公共子序列长度
	int f2(string& s1, string& s2, int len1, int len2) {
		if (len1 == 0 || len2 == 0) {
			return 0;
		}
		int ans;
		if (s1[len1 - 1] == s2[len2 - 1]) {
			ans = f2(s1, s2, len1 - 1, len2 - 1) + 1;
		} else {
			ans = max(f2(s1, s2, len1 - 1, len2), f2(s1, s2, len1, len2 - 1));
		}
		return ans;
	}

	// 记忆化搜索
	int longestCommonSubsequence3(string str1, string str2) {
		int n = str1.length();
		int m = str2.length();
		memset(dp, -1, sizeof(dp));
		return f3(str1, str2, n, m);
	}

	int f3(string& s1, string& s2, int len1, int len2) {
		if (len1 == 0 || len2 == 0) {
			return 0;
		}
		if (dp[len1][len2] != -1) {
			return dp[len1][len2];
		}
		int ans;
		if (s1[len1 - 1] == s2[len2 - 1]) {
			ans = f3(s1, s2, len1 - 1, len2 - 1) + 1;
		} else {
			ans = max(f3(s1, s2, len1 - 1, len2), f3(s1, s2, len1, len2 - 1));
		}
		dp[len1][len2] = ans;
		return ans;
	}

	// 严格位置依赖的动态规划
	int longestCommonSubsequence4(string str1, string str2) {
		int n = str1.length();
		int m = str2.length();
		memset(dp, 0, sizeof(dp));
		for (int len1 = 1; len1 <= n; len1++) {
			for (int len2 = 1; len2 <= m; len2++) {
				if (str1[len1 - 1] == str2[len2 - 1]) {
					dp[len1][len2] = 1 + dp[len1 - 1][len2 - 1];
				} else {
					dp[len1][len2] = max(dp[len1 - 1][len2], dp[len1][len2 - 1]);
				}
			}
		}
		return dp[n][m];
	}

	// 严格位置依赖的动态规划 + 空间压缩（Java 的 longestCommonSubsequence5，作为 LeetCode 提交方法 longestCommonSubsequence）
	int longestCommonSubsequence(string str1, string str2) {
		string s1, s2;
		if (str1.length() >= str2.length()) {
			s1 = str1;
			s2 = str2;
		} else {
			s1 = str2;
			s2 = str1;
		}
		int n = s1.length();
		int m = s2.length();
		memset(dp1D, 0, sizeof(dp1D));
		for (int len1 = 1; len1 <= n; len1++) {
			int leftUp = 0, backup;
			for (int len2 = 1; len2 <= m; len2++) {
				backup = dp1D[len2];
				if (s1[len1 - 1] == s2[len2 - 1]) {
					dp1D[len2] = 1 + leftUp;
				} else {
					dp1D[len2] = max(dp1D[len2], dp1D[len2 - 1]);
				}
				leftUp = backup;
			}
		}
		return dp1D[m];
	}

};

int main() {
	Solution sol;
	cout << sol.longestCommonSubsequence("abcde", "ace") << endl; // 3
	cout << sol.longestCommonSubsequence("abc", "def") << endl;   // 0
	return 0;
}
