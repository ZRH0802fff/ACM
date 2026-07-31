// 规划兼职工作
// 你打算利用空闲时间来做兼职工作赚些零花钱，这里有n份兼职工作
// 每份工作预计从startTime[i]开始、endTime[i]结束，报酬为profit[i]
// 返回可以获得的最大报酬
// 注意，时间上出现重叠的 2 份工作不能同时进行
// 如果你选择的工作在时间X结束，那么你可以立刻进行在时间X开始的下一份工作
// 测试链接 : https://leetcode.cn/problems/maximum-profit-in-job-scheduling/

#include <bits/stdc++.h>
using namespace std;

struct Job{
    int sta, ed, pr;
} p[50010];

int dp[50010];
int n;

class Solution{
public:
    int find(int n,int num){
        int l = 0, r = n, m, ans = 0;
        while(l<=r){
            m = (l + r) / 2;
            if(p[m].ed <=num){
                ans = m;
                l = m + 1;
            }else{
                r = m - 1;
            }
        }
        return ans;
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        n = startTime.size();
        for (int i = 0; i < n; ++i){
            p[i].sta = startTime[i];
            p[i].ed = endTime[i];
            p[i].pr = profit[i];
        }
        sort(p, p + n, [](const Job &a, const Job &b)
             { return a.ed < b.ed; });
        dp[0] = p[0].pr;
        for (int i = 1; i < n; ++i){
            int sta = p[i].sta;
            dp[i] = p[i].pr;
            if(p[0].ed<=sta){
                dp[i] += dp[find(i - 1, sta)];
            }
            dp[i] = max(dp[i - 1], dp[i]);
        }
        return dp[n - 1];
    }
};