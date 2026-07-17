// 让字符串成为回文串的最少插入次数
// 给你一个字符串 s
// 每一次操作你都可以在字符串的任意位置插入任意字符
// 请你返回让s成为回文串的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
int dp[MAXN][MAXN];
int dp1D[MAXN];

class Solution {
public:
    // 暴力尝试
    int minInsertions1(string str) {
        int n = str.length();
        return f1(str, 0, n - 1);
    }

    // s[l....r]这个范围上的字符串，整体都变成回文串
    // 返回至少插入几个字符
    int f1(string& s, int l, int r) {
        // l <= r
        if (l == r) {
            return 0;
        }
        if (l + 1 == r) {
            return s[l] == s[r] ? 0 : 1;
        }
        // l...r不只两个字符
        if (s[l] == s[r]) {
            return f1(s, l + 1, r - 1);
        } else {
            return min(f1(s, l, r - 1), f1(s, l + 1, r)) + 1;
        }
    }

    // 记忆化搜索
    int minInsertions2(string str) {
        int n = str.length();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                dp[i][j] = -1;
            }
        }
        return f2(str, 0, n - 1);
    }

    int f2(string& s, int l, int r) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans;
        if (l == r) {
            ans = 0;
        } else if (l + 1 == r) {
            ans = s[l] == s[l + 1] ? 0 : 1;
        } else {
            if (s[l] == s[r]) {
                ans = f2(s, l + 1, r - 1);
            } else {
                ans = min(f2(s, l, r - 1), f2(s, l + 1, r)) + 1;
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划
    int minInsertions3(string str) {
        int n = str.length();
        memset(dp, 0, sizeof(dp));
        for (int l = 0; l < n - 1; l++) {
            dp[l][l + 1] = str[l] == str[l + 1] ? 0 : 1;
        }
        for (int l = n - 3; l >= 0; l--) {
            for (int r = l + 2; r < n; r++) {
                if (str[l] == str[r]) {
                    dp[l][r] = dp[l + 1][r - 1];
                } else {
                    dp[l][r] = min(dp[l][r - 1], dp[l + 1][r]) + 1;
                }
            }
        }
        return dp[0][n - 1];
    }

    // 空间压缩
    // 本题有关空间压缩的实现，可以参考讲解067，题目4，最长回文子序列问题的讲解
    // 这两个题空间压缩写法高度相似
    // 因为之前的课多次讲过空间压缩的内容，所以这里不再赘述
    int minInsertions4(string str) {
        int n = str.length();
        memset(dp1D, 0, sizeof(dp1D));
        if (n < 2) {
            return 0;
        }
        dp1D[n - 1] = str[n - 2] == str[n - 1] ? 0 : 1;
        for (int l = n - 3, leftDown, backUp; l >= 0; l--) {
            leftDown = dp1D[l + 1];
            dp1D[l + 1] = str[l] == str[l + 1] ? 0 : 1;
            for (int r = l + 2; r < n; r++) {
                backUp = dp1D[r];
                if (str[l] == str[r]) {
                    dp1D[r] = leftDown;
                } else {
                    dp1D[r] = min(dp1D[r - 1], dp1D[r]) + 1;
                }
                leftDown = backUp;
            }
        }
        return dp1D[n - 1];
    }
};

int main() {
    Solution sol;
    // 测试用例
    cout << "=== 让字符串成为回文串的最少插入次数 ===" << endl;
    string s1 = "zzazz";
    cout << "s = \"zzazz\", 预期: 0" << endl;
    cout << "暴力: " << sol.minInsertions1(s1) << endl;
    cout << "记忆化: " << sol.minInsertions2(s1) << endl;
    cout << "动态规划: " << sol.minInsertions3(s1) << endl;
    cout << "空间压缩: " << sol.minInsertions4(s1) << endl;
    cout << endl;

    string s2 = "mbadm";
    cout << "s = \"mbadm\", 预期: 2" << endl;
    cout << "暴力: " << sol.minInsertions1(s2) << endl;
    cout << "记忆化: " << sol.minInsertions2(s2) << endl;
    cout << "动态规划: " << sol.minInsertions3(s2) << endl;
    cout << "空间压缩: " << sol.minInsertions4(s2) << endl;
    cout << endl;

    string s3 = "leetcode";
    cout << "s = \"leetcode\", 预期: 5" << endl;
    cout << "暴力: " << sol.minInsertions1(s3) << endl;
    cout << "记忆化: " << sol.minInsertions2(s3) << endl;
    cout << "动态规划: " << sol.minInsertions3(s3) << endl;
    cout << "空间压缩: " << sol.minInsertions4(s3) << endl;

    return 0;
}
