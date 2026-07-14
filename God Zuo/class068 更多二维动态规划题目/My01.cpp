// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/
#include<bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int n = s.length();
        int m = t.length();
        unsigned long long dp[1010][1010];
        for (int i = 0; i < 1010;++i){
            for (int j = 0; j < 1010; ++j)
                dp[i][j] = 0;
        }
            for (int i = 0; i < n + 1; ++i)
                dp[i][0] = 1;
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                dp[i][j] = dp[i - 1][j];
                if(s[i-1]==t[j-1])
                    dp[i][j] += dp[i - 1][j - 1];
            }
        }
        return dp[n][m];
    }
    int numDistinct2(string s, string t)
    {
        int n = s.length();
        int m = t.length();
        unsigned long long dp[1010][1010];
        for (int i = 0; i < 1010; ++i)
        {
            for (int j = 0; j < 1010; ++j)
                dp[i][j] = 0;
        }
        for (int i = 0; i < n + 1; ++i)
            dp[i][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if (s[i - 1] == t[j - 1])
                    dp[i][j] += dp[i - 1][j - 1];
            }
        }
        return dp[n][m];
    }
};