// 扰乱字符串
// 使用下面描述的算法可以扰乱字符串 s 得到字符串 t ：
// 步骤1 : 如果字符串的长度为 1 ，算法停止
// 步骤2 : 如果字符串的长度 > 1 ，执行下述步骤：
//        在一个随机下标处将字符串分割成两个非空的子字符串
//        已知字符串s，则可以将其分成两个子字符串x和y且满足s=x+y
//        可以决定是要 交换两个子字符串 还是要 保持这两个子字符串的顺序不变
//        即s可能是 s = x + y 或者 s = y + x
//        在x和y这两个子字符串上继续从步骤1开始递归执行此算法
// 给你两个 长度相等 的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串
// 如果是，返回true ；否则，返回false
// 测试链接 : https://leetcode.cn/problems/scramble-string/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 递归版本1（四参数）
    // s1[l1....r1] 与 s2[l2....r2] 是不是扰乱串的关系
    bool f1(const string& s1, const string& s2, int l1, int r1, int l2, int r2) {
        if (l1 == r1) {
            return s1[l1] == s2[l2];
        }
        // 不交错去讨论扰乱关系
        // s1[l1..i][i+1..r1] 对应 s2[l2..j][j+1..r2]
        for (int i = l1, j = l2; i < r1; i++, j++) {
            if (f1(s1, s2, l1, i, l2, j) && f1(s1, s2, i + 1, r1, j + 1, r2)) {
                return true;
            }
        }
        // 交错去讨论扰乱关系
        // s1[l1..i][i+1..r1] 对应 s2[j..r2][l2..j-1]
        for (int i = l1, j = r2; i < r1; i++, j--) {
            if (f1(s1, s2, l1, i, j, r2) && f1(s1, s2, i + 1, r1, l2, j - 1)) {
                return true;
            }
        }
        return false;
    }

    bool isScramble1(string s1, string s2) {
        int n = s1.length();
        return f1(s1, s2, 0, n - 1, 0, n - 1);
    }

    // 递归版本2（三参数：l1, l2, len）
    bool f2(const string& s1, const string& s2, int l1, int l2, int len) {
        if (len == 1) {
            return s1[l1] == s2[l2];
        }
        // s1[l1...l1+len-1]  s2[l2...l2+len-1]
        // 不交错
        for (int k = 1; k < len; k++) {
            if (f2(s1, s2, l1, l2, k) && f2(s1, s2, l1 + k, l2 + k, len - k)) {
                return true;
            }
        }
        // 交错
        for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++) {
            if (f2(s1, s2, l1, j, k) && f2(s1, s2, i, l2, len - k)) {
                return true;
            }
        }
        return false;
    }

    bool isScramble2(string s1, string s2) {
        int n = s1.length();
        return f2(s1, s2, 0, 0, n);
    }

    // 记忆化搜索
    // dp[l1][l2][len] : 0 -> 没展开过, -1 -> false, 1 -> true
    bool isScramble3(string s1, string s2) {
        int n = s1.length();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n + 1, 0)));
        return f3(s1, s2, 0, 0, n, dp);
    }

    bool f3(const string& s1, const string& s2, int l1, int l2, int len, vector<vector<vector<int>>>& dp) {
        if (len == 1) {
            return s1[l1] == s2[l2];
        }
        if (dp[l1][l2][len] != 0) {
            return dp[l1][l2][len] == 1;
        }
        bool ans = false;
        // 不交错
        for (int k = 1; k < len; k++) {
            if (f3(s1, s2, l1, l2, k, dp) && f3(s1, s2, l1 + k, l2 + k, len - k, dp)) {
                ans = true;
                break;
            }
        }
        // 交错
        if (!ans) {
            for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++) {
                if (f3(s1, s2, l1, j, k, dp) && f3(s1, s2, i, l2, len - k, dp)) {
                    ans = true;
                    break;
                }
            }
        }
        dp[l1][l2][len] = ans ? 1 : -1;
        return ans;
    }

    // 严格位置依赖的动态规划（LeetCode 提交用）
    bool isScramble(string s1, string s2) {
        int n = s1.length();
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));
        // len = 1
        for (int l1 = 0; l1 < n; l1++) {
            for (int l2 = 0; l2 < n; l2++) {
                dp[l1][l2][1] = s1[l1] == s2[l2];
            }
        }
        for (int len = 2; len <= n; len++) {
            for (int l1 = 0; l1 <= n - len; l1++) {
                for (int l2 = 0; l2 <= n - len; l2++) {
                    for (int k = 1; k < len; k++) {
                        if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k]) {
                            dp[l1][l2][len] = true;
                            break;
                        }
                    }
                    if (!dp[l1][l2][len]) {
                        for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++) {
                            if (dp[l1][j][k] && dp[i][l2][len - k]) {
                                dp[l1][l2][len] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};

// 测试代码
int main() {
    Solution sol;
    string s1 = "great", s2 = "rgeat";
    cout << boolalpha;
    cout << "isScramble1: " << sol.isScramble1(s1, s2) << endl;
    cout << "isScramble2: " << sol.isScramble2(s1, s2) << endl;
    cout << "isScramble3: " << sol.isScramble3(s1, s2) << endl;
    cout << "isScramble:  " << sol.isScramble(s1, s2) << endl;

    s1 = "abcde"; s2 = "caebd";
    cout << "isScramble1: " << sol.isScramble1(s1, s2) << endl;
    cout << "isScramble2: " << sol.isScramble2(s1, s2) << endl;
    cout << "isScramble3: " << sol.isScramble3(s1, s2) << endl;
    cout << "isScramble:  " << sol.isScramble(s1, s2) << endl;

    s1 = "a"; s2 = "a";
    cout << "isScramble:  " << sol.isScramble(s1, s2) << endl;
    return 0;
}
