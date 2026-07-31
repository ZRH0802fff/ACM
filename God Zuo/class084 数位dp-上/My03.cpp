// 统计整数数目
// 给你两个数字字符串 num1 和 num2 ，以及两个整数max_sum和min_sum
// 如果一个整数 x 满足以下条件，我们称它是一个好整数
// num1 <= x <= num2
// min_sum <= digit_sum(x) <= max_sum
// 请你返回好整数的数目
// 答案可能很大，答案对 1000000007 取模
// 注意，digit_sum(x)表示x各位数字之和
// 测试链接 : https://leetcode.cn/problems/count-of-integers/

#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int minsum, maxsum, len;
string num;
int dp[23][405][2];

void bulid(){
    memset(dp, -1, sizeof(dp));
}

int f(int i,int sum,int free){
    if(sum>maxsum) return 0;
    if(sum+(len-i)*9<minsum) return 0;
    if(i==len) return 1;
    if(dp[i][sum][free]!=-1) return dp[i][sum][free];
    int cur = (int)(num[i] - '0');
    int ans = 0;
    if(free==0){
        for (int p = 0; p < cur; ++p){
            ans += f(i + 1, sum + p, 1);
            ans %= MOD;
        }
        ans += f(i + 1, sum + cur, 0);
        ans %= MOD;
    }else{
        for (int p = 0; p <= 9; ++p){
            ans += f(i + 1, sum + p, 1);
            ans %= MOD;
        }
    }
    dp[i][sum][free] = ans;
    return ans;
}

bool check(){
    int sum = 0;
    for(char ch: num){
        sum += ch - '0';
    }
    return sum >= minsum && sum <= maxsum;
}

class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        minsum = min_sum;
        maxsum = max_sum;

        num = num2;
        len = num2.length();
        bulid();
        int ans = f(0, 0, 0);

        num = num1;
        len = num2.length();
        bulid();
        ans = (ans - f(0, 0, 0) + MOD) % MOD;

        if(check()){
            ans++;
            ans %= MOD;
        }
        return ans;
    }
};