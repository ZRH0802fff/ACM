// 不同的子序列
// 给你两个字符串s和t ，统计并返回在s的子序列中t出现的个数
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/

#include <bits/stdc++.h>
using namespace std;

// s、t 的长度 <= 1000
const int MAXN = 1001;
const int MAXM = 1001;

unsigned long long dp[MAXN][MAXM];
unsigned long long dp1D[MAXM];
int dpMod[MAXM];

class Solution {
public:

	// 已经展示太多次从递归到动态规划了
	// 直接写动态规划吧
	// 普通动态规划
	// dp[i][j] :
	// s[前缀长度为i]的所有子序列中，有多少个子序列等于t[前缀长度为j]
	int numDistinct1(string str, string target) {
		int n = str.length();
		int m = target.length();
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i <= n; i++) {
			dp[i][0] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp[i][j] = dp[i - 1][j];
				if (str[i - 1] == target[j - 1]) {
					dp[i][j] += dp[i - 1][j - 1];
				}
			}
		}
		return (int)dp[n][m];
	}

	// 空间压缩
	int numDistinct2(string str, string target) {
		int n = str.length();
		int m = target.length();
		memset(dp1D, 0, sizeof(dp1D));
		dp1D[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = m; j >= 1; j--) {
				if (str[i - 1] == target[j - 1]) {
					dp1D[j] += dp1D[j - 1];
				}
			}
		}
		return (int)dp1D[m];
	}

	// 本题说了要取模，所以增加取模的逻辑（Java 的 numDistinct3，作为 LeetCode 提交方法 numDistinct）
	int numDistinct(string str, string target) {
		int mod = 1000000007;
		int n = str.length();
		int m = target.length();
		memset(dpMod, 0, sizeof(dpMod));
		dpMod[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = m; j >= 1; j--) {
				if (str[i - 1] == target[j - 1]) {
					dpMod[j] = (dpMod[j] + dpMod[j - 1]) % mod;
				}
			}
		}
		return dpMod[m];
	}

};

int main() {
	Solution sol;
	cout << sol.numDistinct1("rabbbit", "rabbit") << endl; // 3
	cout << sol.numDistinct2("rabbbit", "rabbit") << endl; // 3
	cout << sol.numDistinct("rabbbit", "rabbit") << endl;  // 3
	cout << sol.numDistinct1("babgbag", "bag") << endl;    // 5
	cout << sol.numDistinct2("babgbag", "bag") << endl;    // 5
	cout << sol.numDistinct("babgbag", "bag") << endl;     // 5
	return 0;
}
