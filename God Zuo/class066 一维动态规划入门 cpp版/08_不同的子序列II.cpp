// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，答案对 1000000007 取模
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/

#include <bits/stdc++.h>
using namespace std;

// 只依赖 26 个字符的计数，不依赖字符串长度
int cnt[26];

class Solution {
public:

	// 时间复杂度O(n)，n是字符串s的长度
	int distinctSubseqII(string s) {
		int mod = 1000000007;
		memset(cnt, 0, sizeof(cnt));
		int all = 1, newAdd;
		for (char x : s) {
			newAdd = (all - cnt[x - 'a'] + mod) % mod;
			cnt[x - 'a'] = (cnt[x - 'a'] + newAdd) % mod;
			all = (all + newAdd) % mod;
		}
		return (all - 1 + mod) % mod;
	}

};

int main() {
	Solution sol;
	cout << sol.distinctSubseqII("abc") << endl; // 7
	cout << sol.distinctSubseqII("aba") << endl; // 6
	return 0;
}
