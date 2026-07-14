// 测试链接 : https://leetcode.cn/problems/interleaving-string/
#include<bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        if(s1.length()+s2.length()!=s3.length())
            return false;
        bool dp[110][110];
        int n = s1.length();
        int m = s2.length();
        for (int i = 0; i <= n;++i){
            for (int j = 0; j <= m;++j){
                dp[i][j] = false;
            }
        }
            dp[0][0] = true;
        for (int j = 1; j <= m; ++j){
            if (s2[j-1]!=s3[j-1])
                break;
            dp[0][j] = true;
        }
        for (int i = 1; i <= n; ++i){
            if(s1[i - 1] != s3[i - 1])
                break;
            dp[i][0] = true;
        }
        for (int i = 1; i <= n;++i){
            for (int j = 1; j <= m;++j){
                dp[i][j] = (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) || (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }
};