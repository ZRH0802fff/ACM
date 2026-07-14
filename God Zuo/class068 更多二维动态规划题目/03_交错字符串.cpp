// 交错字符串
// 给定三个字符串 s1、s2、s3
// 请帮忙验证s3是否由s1和s2交错组成
// 测试链接 : https://leetcode.cn/problems/interleaving-string/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 普通动态规划
    // dp[i][j]: s1[前缀长度为i]和s2[前缀长度为j]，能否交错组成出s3[前缀长度为i+j]
    bool isInterleave1(string str1, string str2, string str3) {
        int n = str1.length();
        int m = str2.length();
        if (n + m != (int)str3.length()) {
            return false;
        }
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
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
                dp[i][j] = (str1[i - 1] == str3[i + j - 1] && dp[i - 1][j])
                        || (str2[j - 1] == str3[i + j - 1] && dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }

    // 空间压缩（LeetCode 提交用）
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.length();
        int m = s2.length();
        if (n + m != (int)s3.length()) {
            return false;
        }
        vector<bool> dp(m + 1, false);
        dp[0] = true;
        for (int j = 1; j <= m; j++) {
            if (s2[j - 1] != s3[j - 1]) {
                break;
            }
            dp[j] = true;
        }
        for (int i = 1; i <= n; i++) {
            dp[0] = s1[i - 1] == s3[i - 1] && dp[0];
            for (int j = 1; j <= m; j++) {
                dp[j] = (s1[i - 1] == s3[i + j - 1] && dp[j])
                     || (s2[j - 1] == s3[i + j - 1] && dp[j - 1]);
            }
        }
        return dp[m];
    }
};

// 测试代码
int main() {
    Solution sol;
    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";
    cout << boolalpha;
    cout << "isInterleave1: " << sol.isInterleave1(s1, s2, s3) << endl;
    cout << "isInterleave:  " << sol.isInterleave(s1, s2, s3) << endl;

    s1 = "aabcc";
    s2 = "dbbca";
    s3 = "aadbbbaccc";
    cout << "isInterleave1: " << sol.isInterleave1(s1, s2, s3) << endl;
    cout << "isInterleave:  " << sol.isInterleave(s1, s2, s3) << endl;

    s1 = "";
    s2 = "";
    s3 = "";
    cout << "isInterleave1: " << sol.isInterleave1(s1, s2, s3) << endl;
    cout << "isInterleave:  " << sol.isInterleave(s1, s2, s3) << endl;
    return 0;
}
