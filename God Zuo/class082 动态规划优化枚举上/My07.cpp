// DI序列的有效排列
// 给定一个长度为n的字符串s，其中s[i]是:
// "D"意味着减少，"I"意味着增加
// 有效排列是对有n+1个在[0,n]范围内的整数的一个排列perm，使得对所有的i：
// 如果 s[i] == 'D'，那么 perm[i] > perm[i+1]
// 如果 s[i] == 'I'，那么 perm[i] < perm[i+1]
// 返回有效排列的perm的数量
// 因为答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/valid-permutations-for-di-sequence/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    int dp[205][205];
    const int MOD = 1e9 + 7;

    //一共n个数字 0...n-1
    //在没有使用的数字中，有less个小于i-1位置的数字
    //假设有四个小 3个大
    //  a b c d (i-1) e f g
    // D -> ans+=f(i+1,0)+f(i+1,1)+...f(i+1,3)
    // I -> ans+=f(i+1,4)+f(i+1,5)+f(i+1,6)

    int f(const string& s,int i,int less){
        int ans = 0;
        if(i==n){
            ans = 1;
        }else if(i==0 || s[i-1]=='D'){
            for (int nextless = 0; nextless < less; ++nextless){
                ans += f(s, i + 1, nextless);
                ans %= MOD;
            }
        }else{
            for (int nextless = less, k = 1; k <= n - i - less; ++k, ++nextless){
                ans += f(s, i + 1, nextless);
            }
        }
        return ans;
    }

    int numPermsDISequence(string s) {
        n = s.length()+1;
        return f(s, 0, s.length() + 1);
    }
};


class Solution {
public:
    int n;
    int dp[205][205];
    const int MOD = 1e9 + 7;

    int numPermsDISequence(string s) {
        n = s.length()+1;
        for (int less = 0; less <= n; ++less){
            dp[n][less] = 1;
        }
        for (int i = n - 1; i >= 0; --i){
            if(i==0|| s[i-1]=='D'){
                dp[i][1] = dp[i + 1][0];
                for (int less = 2; less <= n; ++less){
                    dp[i][less] = (dp[i][less - 1] + dp[i + 1][less - 1]) % MOD;
                }
            }else{
                dp[i][n - i - 1] = dp[i + 1][n - i - 1];
                for (int less = n - i - 2; less >= 0; --less){
                    dp[i][less] = (dp[i][less + 1] + dp[i + 1][less]) % MOD;
                }
            }
        }
        return dp[0][n];
    }
};