// 不同的子序列
// 给你两个字符串s和t ，统计并返回在s的子序列中t出现的个数
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 普通动态规划
    // dp[i][j] : s[前缀长度为i]的所有子序列中，有多少个子序列等于t[前缀长度为j]
    int numDistinct1(string str, string target) {
        int n = str.length();
        int m = target.length();
        vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));
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
        vector<unsigned long long> dp(m + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (str[i - 1] == target[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        return (int)dp[m];
    }

    // 取模版本（LeetCode 提交用）
    int numDistinct(string s, string t) {
        const int MOD = 1000000007;
        int n = s.length();
        int m = t.length();
        vector<int> dp(m + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] = (dp[j] + dp[j - 1]) % MOD;
                }
            }
        }
        return dp[m];
    }
};

// 测试代码
int main() {
    Solution sol;
    string s = "rabbbit";
    string t = "rabbit";
    cout << "numDistinct1: " << sol.numDistinct1(s, t) << endl;
    cout << "numDistinct2: " << sol.numDistinct2(s, t) << endl;
    cout << "numDistinct (mod): " << sol.numDistinct(s, t) << endl;

    s = "babgbag";
    t = "bag";
    cout << "numDistinct1: " << sol.numDistinct1(s, t) << endl;
    cout << "numDistinct2: " << sol.numDistinct2(s, t) << endl;
    cout << "numDistinct (mod): " << sol.numDistinct(s, t) << endl;
    return 0;
}
