// 解码方法
// 一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
// 要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）
// 例如，"11106" 可以映射为："AAJF"、"KJF"
// 注意，消息不能分组为(1 11 06)，因为 "06" 不能映射为 "F"
// 这是由于 "6" 和 "06" 在映射中并不等价
// 给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数
// 题目数据保证答案肯定是一个 32位 的整数
// 测试链接 : https://leetcode.cn/problems/decode-ways/

#include <bits/stdc++.h>
using namespace std;

// s.length() <= 100
const int MAXN = 101;

int dp[MAXN];

class Solution {
public:

	// 暴力尝试
	int numDecodings1(string s) {
		return f1(s, 0);
	}

	// s : 数字字符串
	// s[i....]有多少种有效的转化方案
	int f1(string& s, int i) {
		if (i == s.length()) {
			return 1;
		}
		int ans;
		if (s[i] == '0') {
			ans = 0;
		} else {
			ans = f1(s, i + 1);
			if (i + 1 < s.length() && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
				ans += f1(s, i + 2);
			}
		}
		return ans;
	}

	// 暴力尝试改记忆化搜索
	int numDecodings2(string s) {
		memset(dp, -1, sizeof(dp));
		return f2(s, 0);
	}

	int f2(string& s, int i) {
		if (i == s.length()) {
			return 1;
		}
		if (dp[i] != -1) {
			return dp[i];
		}
		int ans;
		if (s[i] == '0') {
			ans = 0;
		} else {
			ans = f2(s, i + 1);
			if (i + 1 < s.length() && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
				ans += f2(s, i + 2);
			}
		}
		dp[i] = ans;
		return ans;
	}

	// 严格位置依赖的动态规划
	int numDecodings3(string str) {
		int n = str.length();
		memset(dp, 0, sizeof(dp));
		dp[n] = 1;
		for (int i = n - 1; i >= 0; i--) {
			if (str[i] == '0') {
				dp[i] = 0;
			} else {
				dp[i] = dp[i + 1];
				if (i + 1 < n && ((str[i] - '0') * 10 + str[i + 1] - '0') <= 26) {
					dp[i] += dp[i + 2];
				}
			}
		}
		return dp[0];
	}

	// 严格位置依赖的动态规划 + 空间压缩（Java 的 numDecodings4，作为 LeetCode 提交方法 numDecodings）
	int numDecodings(string s) {
		// dp[i+1]
		int next = 1;
		// dp[i+2]
		int nextNext = 0;
		for (int i = s.length() - 1, cur; i >= 0; i--) {
			if (s[i] == '0') {
				cur = 0;
			} else {
				cur = next;
				if (i + 1 < s.length() && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
					cur += nextNext;
				}
			}
			nextNext = next;
			next = cur;
		}
		return next;
	}

};

int main() {
	Solution sol;
	cout << sol.numDecodings("12") << endl;    // 2
	cout << sol.numDecodings("226") << endl;   // 3
	cout << sol.numDecodings("06") << endl;    // 0
	return 0;
}
