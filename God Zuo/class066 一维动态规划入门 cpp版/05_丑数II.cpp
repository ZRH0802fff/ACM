// 丑数 II
// 给你一个整数 n ，请你找出并返回第 n 个 丑数
// 丑数 就是只包含质因数 2、3 或 5 的正整数
// 测试链接 : https://leetcode.cn/problems/ugly-number-ii/

#include <bits/stdc++.h>
using namespace std;

// n <= 1690
const int MAXN = 1691;

int dp[MAXN];

class Solution {
public:

	// 时间复杂度O(n)，n代表第n个丑数
	int nthUglyNumber(int n) {
		// dp 0 1 2 ...  n
		//      1 2 ...  ?
		dp[1] = 1;
		for (int i = 2, i2 = 1, i3 = 1, i5 = 1, a, b, c, cur; i <= n; i++) {
			a = dp[i2] * 2;
			b = dp[i3] * 3;
			c = dp[i5] * 5;
			cur = min(min(a, b), c);
			if (cur == a) {
				i2++;
			}
			if (cur == b) {
				i3++;
			}
			if (cur == c) {
				i5++;
			}
			dp[i] = cur;
		}
		return dp[n];
	}

};

int main() {
	Solution sol;
	cout << sol.nthUglyNumber(10) << endl; // 12
	cout << sol.nthUglyNumber(37) << endl; // 125
	return 0;
}
