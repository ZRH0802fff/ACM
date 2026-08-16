// 通配符匹配（和题目4高度相似，只是边界条件不同而已，而且更简单）
// 给你字符串s、字符串p
// s中一定不含有'?'、'*'字符，p中可能含有'?'、'*'字符
// '?' 表示可以变成任意字符，数量1个
// '*' 表示可以匹配任何字符串
// 请实现一个支持 '?' 和 '*' 的通配符匹配
// 返回p的整个字符串能不能匹配出s的整个字符串
// 测试链接 : https://leetcode.cn/problems/wildcard-matching/
// 核心: 与正则匹配类似但更简单; p[j]=='*'时两种选择: f(i+1,j) [*吃掉s[i]] || f(i,j+1) [*不匹配]
// 坑点: ①边界: s为空p有后缀时, 只有全*才能消掉 ②'?'匹配单个任意字符, '*'匹配任意序列
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 暴力递归
    // s[i....]能不能被p[j....]完全匹配出来
    bool f1(const string& s, const string& p, int i, int j) {
        if (i == (int)s.length()) {
            // s没了
            if (j == (int)p.length()) {
                return true;
            } else {
                // 如果p[j]是*，可以消掉，然后看看p[j+1....]是不是都能消掉
                return p[j] == '*' && f1(s, p, i, j + 1);
            }
        } else if (j == (int)p.length()) {
            // s有，p没了
            return false;
        } else {
            if (p[j] != '*') {
                // 如果p[j]不是*，那么当前的字符必须能匹配
                return (s[i] == p[j] || p[j] == '?') && f1(s, p, i + 1, j + 1);
            } else {
                // 如果p[j]是*
                // 选择1: 反正当前p[j]是*，必然可以搞定s[i]，继续 f(i+1, j)
                // 选择2: 虽然当前p[j]是*，但就是不让它搞定s[i]，继续 f(i, j+1)
                return f1(s, p, i + 1, j) || f1(s, p, i, j + 1);
            }
        }
    }

    bool isMatch1(string s, string p) {
        return f1(s, p, 0, 0);
    }

    // 记忆化搜索
    // dp[i][j] == 0 没算过, 1 算过true, 2 算过false
    bool isMatch2(string s, string p) {
        int n = s.length(), m = p.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        return f2(s, p, 0, 0, dp);
    }

    bool f2(const string& s, const string& p, int i, int j, vector<vector<int>>& dp) {
        if (dp[i][j] != 0) return dp[i][j] == 1;
        bool ans;
        if (i == (int)s.length()) {
            if (j == (int)p.length()) {
                ans = true;
            } else {
                ans = p[j] == '*' && f2(s, p, i, j + 1, dp);
            }
        } else if (j == (int)p.length()) {
            ans = false;
        } else {
            if (p[j] != '*') {
                ans = (s[i] == p[j] || p[j] == '?') && f2(s, p, i + 1, j + 1, dp);
            } else {
                ans = f2(s, p, i + 1, j, dp) || f2(s, p, i, j + 1, dp);
            }
        }
        dp[i][j] = ans ? 1 : 2;
        return ans;
    }

    // 严格位置依赖的动态规划
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[n][m] = true;
        // s为空时，p后缀只有全*才能匹配
        for (int j = m - 1; j >= 0 && p[j] == '*'; j--) {
            dp[n][j] = true;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (p[j] != '*') {
                    dp[i][j] = (s[i] == p[j] || p[j] == '?') && dp[i + 1][j + 1];
                } else {
                    dp[i][j] = dp[i + 1][j] || dp[i][j + 1];
                }
            }
        }
        return dp[0][0];
    }
};

int main() {
    Solution sol;
    cout << boolalpha;
    cout << sol.isMatch("aa", "a") << endl;       // false
    cout << sol.isMatch("aa", "*") << endl;       // true
    cout << sol.isMatch("cb", "?a") << endl;      // false
    cout << sol.isMatch("adceb", "*a*b") << endl; // true
    return 0;
}
