// 我能赢吗
// 给定两个整数n和m
// 两个玩家可以轮流从公共整数池中抽取从1到n的整数（不放回）
// 抽取的整数会累加起来（两个玩家都算）
// 谁在自己的回合让累加和 >= m，谁获胜
// 若先出手的玩家能稳赢则返回true，否则返回false
// 假设两位玩家游戏时都绝顶聪明，可以全盘为自己打算
// 测试链接 : https://leetcode.cn/problems/can-i-win/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[(1 << 21)+10];
    
    bool f(int n,int status,int rest){
        if(rest<=0){
            return false;
        }
        if(dp[status]!=0){
            return dp[status] == 1;
        }
        bool ans = false;
        for (int i = 1; i <= n; ++i){
            if((status& (1<<i))!=0 && !f(n,(status^(1<<i)),rest-i)){
                ans = true;
                break;
            }
        }
        dp[status] = ans ? 1 : -1;
        return ans;
    }
    
    bool canIWin(int n, int m) {
        if(m==0)
            return true;
        if(n*(n+1)/2<m)
            return false;
        for (int i = 0; i < (1<<(n+1)); ++i)
            dp[i] = 0;
        return f(n, (1 << (n + 1)) - 1, m);
    }
};