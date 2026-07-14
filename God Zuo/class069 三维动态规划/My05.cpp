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

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int dp[35][35][35] = {};
    bool f(const string& s1,const string& s2 ,int l1,int l2,int len){
        if(len==1)
            return s1[l1] == s2[l2];
        if(dp[l1][l2][len]!=0)
            return dp[l1][l2][len] == 1;
        bool ans = false;
        for (int k = 1; k < len;++k){
            if(f(s1,s2,l1,l2,k) && f(s1,s2,l1+k,l2+k,len-k)){
                ans = true;
                break;
            }
        }
        if(!ans){
            for (int k = 1;k<len;++k){
                if (f(s1, s2, l1, l2 +len- k, k) && f(s1, s2, l1 + k, l2, len - k)) {
                    ans = true;
                    break;
                }
            }
        }
        dp[l1][l2][len] = ans ? 1 : -1;
        return ans;
    }

    bool isScramble(string s1, string s2){
        if(s1.length()!=s2.length())
            return false;
        int n = s1.length();
        for (int i = 0; i < n;++i){
            for (int j = 0; j < n;++j){
                for (int k = 0; k <= n;++k)
                    dp[i][j][k] = 0;
            }
        }
        return f(s1, s2, 0, 0, n);
    }
};