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

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool f1(const string &s, const string &p, int i, int j) {
        if (i == (int)s.length()){
            if(j==(int)p.length())
                return true;
            else
                return j + 1 < (int)p.length() && p[j + 1] == '*' && f1(s, p, i, j + 2);
        }else if(j==(int)p.length()){
            return false;
        }else{
            if(j+1==(int)p.length() || p[j+1]!='*'){
                return (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j+1);
            }else{
                bool p1 = f1(s, p, i, j+2);
                bool p2 = (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j);
                return p1 || p2;
            }
        }
    } 

    bool isMatch(string s, string p) {
        return f1(s, p, 0, 0);
    }
};



class Solution {
public:
    int dp[25][25];

    bool f1(const string &s, const string &p, int i, int j) {
        if(dp[i][j]!=0)
            return dp[i][j]==1;
        bool ans;
        if (i == (int)s.length()){
            if(j==(int)p.length())
                ans= true;
            else
                ans= j + 1 < (int)p.length() && p[j + 1] == '*' && f1(s, p, i, j + 2);
        }else if(j==(int)p.length()){
            ans= false;
        }else{
            if(j+1==(int)p.length() || p[j+1]!='*'){
                ans= (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j+1);
            }else{
                bool p1 = f1(s, p, i, j+2);
                bool p2 = (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j);
                ans= p1 || p2;
            }
        }
        dp[i][j] = ans ? 1 : 2;
        return ans;
    }

    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        for (int i = 0; i <= n;++i){
            for (int j = 0; j <= m;++j)
                dp[i][j] = 0;
        }
        return f1(s, p, 0, 0);
    }
};