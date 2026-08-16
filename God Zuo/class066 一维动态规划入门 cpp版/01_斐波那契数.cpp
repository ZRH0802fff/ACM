// 斐波那契数
// 斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列
// 该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。
// 也就是：F(0) = 0，F(1) = 1
// F(n) = F(n - 1) + F(n - 2)，其中 n > 1
// 给定 n ，请计算 F(n)
// 测试链接 : https://leetcode.cn/problems/fibonacci-number/
// 注意：最优解来自矩阵快速幂，时间复杂度可以做到O(log n)
// 后续课程一定会讲述！本节课不涉及！

#include <bits/stdc++.h>
using namespace std;

// n <= 30
const int MAXN = 31;

int dp[MAXN];

class Solution {
public:

	int fib1(int n) {
		return f1(n);
	}

	int f1(int i) {
		if (i == 0) {
			return 0;
		}
		if (i == 1) {
			return 1;
		}
		return f1(i - 1) + f1(i - 2);
	}

	int fib2(int n) {
		memset(dp, -1, sizeof(dp));
		return f2(n);
	}

	int f2(int i) {
		if (i == 0) {
			return 0;
		}
		if (i == 1) {
			return 1;
		}
		if (dp[i] != -1) {
			return dp[i];
		}
		int ans = f2(i - 1) + f2(i - 2);
		dp[i] = ans;
		return ans;
	}

	int fib3(int n) {
		if (n == 0) {
			return 0;
		}
		if (n == 1) {
			return 1;
		}
		memset(dp, 0, sizeof(dp));
		dp[1] = 1;
		for (int i = 2; i <= n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}

	// 空间压缩（Java 的 fib4，作为 LeetCode 提交方法 fib）
	int fib(int n) {
		if (n == 0) {
			return 0;
		}
		if (n == 1) {
			return 1;
		}
		int lastLast = 0, last = 1;
		for (int i = 2, cur; i <= n; i++) {
			cur = lastLast + last;
			lastLast = last;
			last = cur;
		}
		return last;
	}

};

int main() {
	Solution sol;
	cout << sol.fib(2) << endl;   // 1
	cout << sol.fib(3) << endl;   // 2
	cout << sol.fib(10) << endl;  // 55
	return 0;
}
