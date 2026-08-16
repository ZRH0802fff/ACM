// 正则表达式匹配
// 给你字符串s、字符串p
// s中一定不含有'.'、'*'字符，p中可能含有'.'、'*'字符
// '.' 表示可以变成任意字符，数量1个
// '*' 表示可以让 '*' 前面那个字符数量任意(甚至可以是0个)
// p中即便有'*'，一定不会出现以'*'开头的情况，也一定不会出现多个'*'相邻的情况(无意义)
// 请实现一个支持 '.' 和 '*' 的正则表达式匹配
// 返回p的整个字符串能不能匹配出s的整个字符串
// 测试链接 : https://leetcode.cn/problems/regular-expression-matching/
// 核心: 类似完全背包思想。p[j+1]=='*'时有两种选择:
//       选1(不让x*搞定s[i]): f(i, j+2)
//       选2(让x*搞定s[i]):  (s[i]==p[j]||p[j]=='.') && f(i+1, j)
// 坑点: ①p[j]一定不是'*'(题目保证) ②s为空p还有后缀时, 只有x*y*z*...模式才能消掉
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 暴力递归
    // s[i....]能不能被p[j....]完全匹配出来
    // p[j]这个字符，一定不是'*'
    bool f1(const string& s, const string& p, int i, int j) {
        if (i == (int)s.length()) {
            // s没了
            if (j == (int)p.length()) {
                // 如果p也没了，返回true
                return true;
            } else {
                // p还剩下一些后缀
                // 如果p[j+1]是*，那么p[j..j+1]可以消掉，然后看看p[j+2....]是不是都能消掉
                return j + 1 < (int)p.length() && p[j + 1] == '*' && f1(s, p, i, j + 2);
            }
        } else if (j == (int)p.length()) {
            // s有后缀, p没后缀了
            return false;
        } else {
            // s有后缀, p有后缀
            if (j + 1 == (int)p.length() || p[j + 1] != '*') {
                // 如果p[j+1]不是*，那么当前的字符必须能匹配
                // 同时，后续也必须匹配上
                return (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j + 1);
            } else {
                // 如果p[j+1]是* —— 完全背包思想！
                // 选择1: 当前p[j..j+1]是x*，不让它搞定s[i]，继续 f(i, j+2)
                bool p1 = f1(s, p, i, j + 2);
                // 选择2: 当前p[j..j+1]是x*，如果可以搞定s[i]，继续 f(i+1, j)
                // 如果可以搞定s[i] : (s[i] == p[j] || p[j] == '.')
                bool p2 = (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j);
                return p1 || p2;
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
                ans = j + 1 < (int)p.length() && p[j + 1] == '*' && f2(s, p, i, j + 2, dp);
            }
        } else if (j == (int)p.length()) {
            ans = false;
        } else {
            if (j + 1 == (int)p.length() || p[j + 1] != '*') {
                ans = (s[i] == p[j] || p[j] == '.') && f2(s, p, i + 1, j + 1, dp);
            } else {
                ans = f2(s, p, i, j + 2, dp)
                   || ((s[i] == p[j] || p[j] == '.') && f2(s, p, i + 1, j, dp));
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
        // 处理s为空时p的后缀: 只有 x*x*... 模式才能消掉
        for (int j = m - 1; j >= 0; j--) {
            dp[n][j] = j + 1 < m && p[j + 1] == '*' && dp[n][j + 2];
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (j + 1 == m || p[j + 1] != '*') {
                    dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j + 1];
                } else {
                    dp[i][j] = dp[i][j + 2] || ((s[i] == p[j] || p[j] == '.') && dp[i + 1][j]);
                }
            }
        }
        return dp[0][0];
    }
};

int main() {
    Solution sol;
    cout << boolalpha;
    cout << sol.isMatch("aa", "a") << endl;           // false
    cout << sol.isMatch("aa", "a*") << endl;          // true
    cout << sol.isMatch("ab", ".*") << endl;          // true
    cout << sol.isMatch("aab", "c*a*b") << endl;      // true
    cout << sol.isMatch("mississippi", "mis*is*p*.") << endl; // false
    return 0;
}
