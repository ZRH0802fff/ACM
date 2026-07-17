// 让字符串成为回文串的最少插入次数
// 给你一个字符串 s
// 每一次操作你都可以在字符串的任意位置插入任意字符
// 请你返回让s成为回文串的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[505][505];

    int f1(string& s,int l,int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans = 0;
        if(l==r){
            ans = 0;
        }else if(l+1==r){
            ans = s[l] == s[r] ? 0 : 1;
        }else{
            if(s[l]==s[r]){
                ans = f1(s, l + 1, r - 1);
            }else{
                ans = min(f1(s, l + 1, r), f1(s, l, r - 1)) + 1;
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    int minInsertions(string s) {
        int n = s.length();
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j)
                dp[i][j] = -1;
        }
        return f1(s, 0, n - 1);
    }
};



class Solution {
public:
    int dp[505][505];

    int minInsertions(string s) {
        int n = s.length();
        for (int i = 0; i < n;++i)
            dp[i][i] = 0;
        for (int l = 0; l < n - 1;++l)
            dp[l][l + 1] = s[l] == s[l + 1] ? 0 : 1;
        for (int l = n - 3; l >= 0;--l){
            for (int r = l + 2; r < n;++r){
                if(s[l]==s[r]){
                    dp[l][r] = dp[l + 1][r - 1];
                }else{
                    dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1;
                }
            }
        }
        return dp[0][n - 1];
    }
};