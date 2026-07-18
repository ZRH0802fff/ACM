// 涂色 & 奇怪打印机
// 假设你有一条长度为5的木板，初始时没有涂过任何颜色
// 你希望把它的5个单位长度分别涂上红、绿、蓝、绿、红
// 用一个长度为5的字符串表示这个目标：RGBGR
// 每次你可以把一段连续的木板涂成一个给定的颜色，后涂的颜色覆盖先涂的颜色
// 例如第一次把木板涂成RRRRR
// 第二次涂成RGGGR
// 第三次涂成RGBGR，达到目标
// 返回尽量少的涂色次数
// 测试链接 : https://www.luogu.com.cn/problem/P4170
// 测试链接 : https://leetcode.cn/problems/strange-printer/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[105][105];

    int f(string& s,int l,int r){
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans = INT_MAX;
        if(l==r){
            ans = 1;
        }else if(l+1==r){
            ans = s[l] == s[r] ? 1 : 2;
        }else{
            if(s[l]==s[r]){
                ans = f(s, l, r - 1);
            }else{
                for (int m = l; m < r;++m){
                    ans = min(ans, f(s,l, m) + f(s,m + 1, r));
                }
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    int strangePrinter(string s) {
        int n = s.length();
        for (int i = 0; i < n;++i){
            for (int j = 0; j < n;++j){
                dp[i][j] = -1;
            }
        }
        return f(s, 0, n - 1);
    }
};