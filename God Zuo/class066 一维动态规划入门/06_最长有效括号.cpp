// 最长有效括号
// 给你一个只包含 '(' 和 ')' 的字符串
// 找出最长有效（格式正确且连续）括号子串的长度。
// 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/

#include <bits/stdc++.h>
using namespace std;

// s.length() <= 3 * 10^4
const int MAXN = 30001;

int dp[MAXN];

class Solution {
public:

	// 时间复杂度O(n)，n是str字符串的长度
	int longestValidParentheses(string str) {
		int n = str.length();
		// dp[0...n-1]
		// dp[i] : 子串必须以i位置的字符结尾的情况下，往左整体有效的最大长度
		memset(dp, 0, sizeof(dp));
		int ans = 0;
		for (int i = 1, p; i < n; i++) {
			if (str[i] == ')') {
				p = i - dp[i - 1] - 1;
				//  ?         )
				//  p         i
				if (p >= 0 && str[p] == '(') {
					dp[i] = dp[i - 1] + 2 + (p - 1 >= 0 ? dp[p - 1] : 0);
				}
			}
			ans = max(ans, dp[i]);
		}
		return ans;
	}

};

int main() {
	Solution sol;
	cout << sol.longestValidParentheses("(()") << endl;     // 2
	cout << sol.longestValidParentheses(")()())") << endl;  // 4
	return 0;
}
