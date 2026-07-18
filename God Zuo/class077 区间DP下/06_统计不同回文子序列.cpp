// 统计不同回文子序列
// 给你一个字符串s，返回s中不同的非空回文子序列个数
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/count-different-palindromic-subsequences/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MOD = 1000000007;
int last[256];
int leftIdx[MAXN], rightIdx[MAXN];
long long dp[MAXN][MAXN];

class Solution {
public:
    // 时间复杂度O(n^2)
    int countPalindromicSubsequences(string str) {
        int n = str.length();
        // left[i] : i位置的左边和s[i]字符相等且最近的位置在哪，不存在就是-1
        memset(last, -1, sizeof(last));
        for (int i = 0; i < n; i++) {
            leftIdx[i] = last[str[i]];
            last[str[i]] = i;
        }
        // right[i] : i位置的右边和s[i]字符相等且最近的位置在哪，不存在就是n
        for (int i = 0; i < 256; i++) last[i] = n;
        for (int i = n - 1; i >= 0; i--) {
            rightIdx[i] = last[str[i]];
            last[str[i]] = i;
        }
        // dp[i][j] : i...j范围上有多少不同的回文子序列
        // 如果i>j，那么认为是无效范围dp[i][j] = 0
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int i = n - 2, l, r; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (str[i] != str[j]) {
                    // a ..... b
                    // i       j
                    // 因为要取模，所以只要发生减操作就+mod，讲解041同余原理
                    dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1] + MOD;
                } else {
                    // str[i] == str[j]
                    // a......a
                    // i      j
                    l = rightIdx[i];
                    r = leftIdx[j];
                    if (l > r) {
                        // i...j的内部没有s[i]字符
                        // a....a
                        // i    j
                        // (i+1..j-1) + a(i+1..j-1)a + a + aa
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 2;
                    } else if (l == r) {
                        // i...j的内部有一个s[i]字符
                        // a.....a......a
                        // i     lr     j
                        // (i+1..j-1) + a(i+1..j-1)a + aa
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 1;
                    } else {
                        // i...j的内部不只一个s[i]字符
                        // a...a....这内部可能还有a但是不重要....a...a
                        // i   l                             r   j
                        // 因为要取模，所以只要发生减操作就+mod，讲解041同余原理
                        dp[i][j] = dp[i + 1][j - 1] * 2 - dp[l + 1][r - 1] + MOD;
                    }
                }
                dp[i][j] %= MOD;
            }
        }
        return (int)dp[0][n - 1];
    }
};

int main() {
    Solution sol;
    cout << "=== 统计不同回文子序列 ===" << endl;

    string s1 = "a";
    cout << "s = \"a\", 预期: 1" << endl;
    cout << "结果: " << sol.countPalindromicSubsequences(s1) << endl;
    cout << endl;

    string s2 = "bccb";
    cout << "s = \"bccb\", 预期: 6" << endl;
    cout << "结果: " << sol.countPalindromicSubsequences(s2) << endl;
    cout << endl;

    string s3 = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba";
    cout << "s = \"abcd...\", 预期: 104860361" << endl;
    cout << "结果: " << sol.countPalindromicSubsequences(s3) << endl;

    return 0;
}
