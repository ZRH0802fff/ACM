// 每个人戴不同帽子的方案数
// 总共有 n 个人和 40 种不同的帽子，帽子编号从 1 到 40
// 给你一个整数列表的列表 hats ，其中 hats[i] 是第 i 个人所有喜欢帽子的列表
// 请你给每个人安排一顶他喜欢的帽子，确保每个人戴的帽子跟别人都不一样，并返回方案数
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/number-of-ways-to-wear-different-hats-to-each-other

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int MOD = 1e9 + 7;
    int m, n;                  //m->帽子数 n->人数
    int hats[42];              //hats[i]表示第i号帽子能满足哪些人，用位存信息
    int dp[42][1 << 10];

    //i->来到第i个颜色的帽子
    //s->状态信息，没满足是0，满足是1
    int f(int i,int s){
        if(s==(1<<n)-1) return 1;
        if(i==m+1) return 0;
        if(dp[i][s]!=-1) return dp[i][s];
        int ans = f(i + 1, s);
        int cur = hats[i];
        int r1;                                //用于依次得到二进制状态下最右的1
        while(cur!=0){
            r1 = cur & -cur;
            if((s&r1)==0){
                ans = (ans + f(i + 1, s | r1)) % MOD;
            }
            cur ^= r1;
        }
        dp[i][s] = ans;
        return ans;
    }

    int numberWays(vector<vector<int>>& arr) {
        m = 0;
        for(auto& p:arr){
            for(int h:p){
                m = max(m, h);
            }
        }
        n = arr.size();
        for (int i = 0; i < 42; ++i){
            hats[i] = 0;
            for (int j = 0; j < (1 << n); ++j){
                dp[i][j] = -1;
            }
        }
        for (int pi = 0; pi < n; ++pi){
            for(int hat:arr[pi]){
                hats[hat] |= 1 << pi;
            }
        }
        return f(1, 0);
    }
};