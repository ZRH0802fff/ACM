// 编辑距离
// 给你两个单词 word1 和 word2
// 请返回将 word1 转换成 word2 所使用的最少代价
// 你可以对一个单词进行如下三种操作：
// 插入一个字符，代价a
// 删除一个字符，代价b
// 替换一个字符，代价c
// 测试链接 : https://leetcode.cn/problems/edit-distance/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // LeetCode 入口：插入、删除、替换代价均为 1
    int minDistance(string word1, string word2) {
        return editDistance2(word1, word2, 1, 1, 1);
    }

    // 原初尝试版
    // a : str1中插入1个字符的代价
    // b : str1中删除1个字符的代价
    // c : str1中改变1个字符的代价
    // 返回从str1转化成str2的最低代价
    int editDistance1(string str1, string str2, int a, int b, int c) {
        int n = str1.length();
        int m = str2.length();
        // dp[i][j] : s1[前缀长度为i]想变成s2[前缀长度为j]，至少付出多少代价
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; j++) {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j - 1] + c, dp[i][j - 1] + a, dp[i - 1][j] + b});
                }
            }
        }
        return dp[n][m];
    }

    // 枚举小优化版
    int editDistance2(string str1, string str2, int a, int b, int c) {
        int n = str1.length();
        int m = str2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; j++) {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j] + b, dp[i][j - 1] + a, dp[i - 1][j - 1] + c});
                }
            }
        }
        return dp[n][m];
    }

    // 空间压缩
    int editDistance3(string str1, string str2, int a, int b, int c) {
        int n = str1.length();
        int m = str2.length();
        vector<int> dp(m + 1);
        for (int j = 1; j <= m; j++) {
            dp[j] = j * a;
        }
        for (int i = 1, leftUp, backUp; i <= n; i++) {
            leftUp = (i - 1) * b;
            dp[0] = i * b;
            for (int j = 1; j <= m; j++) {
                backUp = dp[j];
                if (str1[i - 1] == str2[j - 1]) {
                    dp[j] = leftUp;
                } else {
                    dp[j] = min({dp[j] + b, dp[j - 1] + a, leftUp + c});
                }
                leftUp = backUp;
            }
        }
        return dp[m];
    }
};

// 测试代码
int main() {
    Solution sol;
    string word1 = "horse";
    string word2 = "ros";
    cout << "minDistance: " << sol.minDistance(word1, word2) << endl;
    cout << "editDistance1: " << sol.editDistance1(word1, word2, 1, 1, 1) << endl;
    cout << "editDistance2: " << sol.editDistance2(word1, word2, 1, 1, 1) << endl;
    cout << "editDistance3: " << sol.editDistance3(word1, word2, 1, 1, 1) << endl;

    word1 = "intention";
    word2 = "execution";
    cout << "minDistance: " << sol.minDistance(word1, word2) << endl;
    cout << "editDistance2: " << sol.editDistance2(word1, word2, 1, 1, 1) << endl;
    cout << "editDistance3: " << sol.editDistance3(word1, word2, 1, 1, 1) << endl;
    return 0;
}
