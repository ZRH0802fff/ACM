// 解码方法
// 一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
// 要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）
// 例如，"11106" 可以映射为："AAJF"、"KJF"
// 注意，消息不能分组为(1 11 06)，因为 "06" 不能映射为 "F"
// 这是由于 "6" 和 "06" 在映射中并不等价
// 给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数
// 题目数据保证答案肯定是一个 32位 的整数
// 测试链接 : https://leetcode.cn/problems/decode-ways/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        int n=s.length();
        int dp[n+1];
        for(int i=0;i<n;++i) dp[i]=0;
        dp[n]=1;
        for(int i=n-1;i>=0; --i){
            if(s[i]=='0'){
                dp[i]=0;
            }else{
                dp[i]=dp[i+1];
                if(i+1<n && ((int)(s[i]-'0')*10+(int)(s[i+1]-'0')<=26)){
                    dp[i]+=dp[i+2];
                }
            }
        }
        return dp[0];
    }
};