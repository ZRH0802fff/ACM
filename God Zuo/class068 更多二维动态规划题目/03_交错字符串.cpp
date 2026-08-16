// 交错字符串
// 给定三个字符串 s1、s2、s3
// 请帮忙验证s3是否由s1和s2交错组成
// 测试链接 : https://leetcode.cn/problems/interleaving-string/

#include <bits/stdc++.h>
using namespace std;

// s1、s2 的长度 <= 100，s3 的长度 <= 200
const int MAXN = 101;
const int MAXM = 101;

bool dp[MAXN][MAXM];
bool dp1D[MAXM];

class Solution {
public:

	// 已经展示太多次从递归到动态规划了
	// 直接写动态规划吧
	bool isInterleave1(string str1, string str2, string str3) {
		if (str1.length() + str2.length() != str3.length()) {
			return false;
		}
		int n = str1.length();
		int m = str2.length();
		memset(dp, false, sizeof(dp));
		// dp[i][j]:
		// s1[前缀长度为i]和s2[前缀长度为j]，能否交错组成出s3[前缀长度为i+j]
		dp[0][0] = true;
		for (int i = 1; i <= n; i++) {
			if (str1[i - 1] != str3[i - 1]) {
				break;
			}
			dp[i][0] = true;
		}
		for (int j = 1; j <= m; j++) {
			if (str2[j - 1] != str3[j - 1]) {
				break;
			}
			dp[0][j] = true;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp[i][j] = (str1[i - 1] == str3[i + j - 1] && dp[i - 1][j]) || (str2[j - 1] == str3[i + j - 1] && dp[i][j - 1]);
			}
		}
		return dp[n][m];
	}

	// 空间压缩（Java 的 isInterleave2，作为 LeetCode 提交方法 isInterleave）
	bool isInterleave(string str1, string str2, string str3) {
		if (str1.length() + str2.length() != str3.length()) {
			return false;
		}
		int n = str1.length();
		int m = str2.length();
		memset(dp1D, false, sizeof(dp1D));
		dp1D[0] = true;
		for (int j = 1; j <= m; j++) {
			if (str2[j - 1] != str3[j - 1]) {
				break;
			}
			dp1D[j] = true;
		}
		for (int i = 1; i <= n; i++) {
			dp1D[0] = str1[i - 1] == str3[i - 1] && dp1D[0];
			for (int j = 1; j <= m; j++) {
				dp1D[j] = (str1[i - 1] == str3[i + j - 1] && dp1D[j]) || (str2[j - 1] == str3[i + j - 1] && dp1D[j - 1]);
			}
		}
		return dp1D[m];
	}

};

int main() {
	Solution sol;
	cout << boolalpha;
	cout << sol.isInterleave1("aabcc", "dbbca", "aadbbcbcac") << endl; // true
	cout << sol.isInterleave("aabcc", "dbbca", "aadbbcbcac") << endl;  // true
	cout << sol.isInterleave1("aabcc", "dbbca", "aadbbbaccc") << endl; // false
	cout << sol.isInterleave("aabcc", "dbbca", "aadbbbaccc") << endl;  // false
	return 0;
}
