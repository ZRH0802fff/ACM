#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2){
        int n1 = text1.length();
        int n2 = text2.length();
        vector<vector<int>> dp(n1 + 1, vector<int>(n1 + 1, 0));
        for (int len1 = 1; len1 <= n1;++len1){
            for (int len2 = 1; len2 <= n2;++len2){
                if(text1[len1-1]==text2[len2-1]){
                    dp[len1][len2] = dp[len1 - 1][len2 - 1] + 1;
                }else{
                    dp[len1][len2] = max(dp[len1 - 1][len2], dp[len1][len2 - 1]);
                }
            }
        }
        return dp[n1][n2];
    }
};

struct TestCase
{
    string t1;
    string t2;
    int expected;
    string description;
};

int main()
{
    Solution solver;

    // 准备 5 个典型测试用例
    vector<TestCase> testCases = {
        {"abcde", "ace", 3, "普通用例 (LCS 为 \"ace\")"},
        {"abc", "abc", 3, "完全相同 (LCS 为 \"abc\")"},
        {"abc", "def", 0, "完全不同 (LCS 为 0)"},
        {"", "abc", 0, "存在空字符串 (LCS 为 0)"},
        {"a", "bcefa", 1, "长度差异大且匹配点在两端 (LCS 为 \"a\")"}};

    cout << "========= 最长公共子序列（LCS）测试开始 =========" << endl;

    int passed = 0;
    for (int i = 0; i < testCases.size(); ++i)
    {
        auto &tc = testCases[i];
        int result = solver.longestCommonSubsequence(tc.t1, tc.t2);

        cout << "测试用例 " << i + 1 << " [" << tc.description << "]:" << endl;
        cout << "  输入: text1 = \"" << tc.t1 << "\", text2 = \"" << tc.t2 << "\"" << endl;
        cout << "  预期输出: " << tc.expected << " | 实际输出: " << result << endl;

        if (result == tc.expected)
        {
            cout << "  结果: [ PASS ]" << endl;
            passed++;
        }
        else
        {
            cout << "  结果: [ FAIL ] " << endl;
        }
        cout << "------------------------------------------------" << endl;
    }

    cout << "测试结束: 总共 " << testCases.size() << " 个用例，通过 " << passed << " 个。" << endl;

    return 0;
}