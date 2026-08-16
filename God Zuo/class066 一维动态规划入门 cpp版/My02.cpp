// 最低票价
// 在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
// 在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
// 每一项是一个从 1 到 365 的整数
// 火车票有 三种不同的销售方式
// 一张 为期1天 的通行证售价为 costs[0] 美元
// 一张 为期7天 的通行证售价为 costs[1] 美元
// 一张 为期30天 的通行证售价为 costs[2] 美元
// 通行证允许数天无限制的旅行
// 例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
// 那么我们可以连着旅行 7 天(第2~8天)
// 返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/

#include<bits/stdc++.h>
using namespace std;

int dp[370];
int arr[3]={1,7,30};
int n;

/*
f(i)完成表示days[i...]这些天的最少花费
状态转移：可以枚举每一个1，7，30的车票 ->cost[k]+f(j) j是该张车票不管用的第一个days
*/
class Solution {
public:
    int f1(vector<int>& days,vector<int>& costs,int i){
        if(i==days.size()) return 0;
        if(dp[i]!=INT_MAX) return dp[i];
        int ans=INT_MAX;
        for(int k=0,j=i;k<3;++k){
            while(j<days.size() && days[i]+arr[k]>days[j]){
                j++;
            }
            ans=min(ans,costs[k]+f1(days,costs,j));
        }
        dp[i]=ans;
        return ans;
    }

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        for(int i=0;i<=days.size(); ++i) dp[i]=INT_MAX;
        return f1(days,costs,0);
    }
};

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n=days.size();
        for(int i=0;i<=n; ++i) dp[i]=INT_MAX;
        dp[n]=0;
        for(int i=n-1;i>=0;--i){
            for(int k=0,j=i;k<3;++k){
                while(j<n && days[i]+arr[k]>days[j]) ++j;
                dp[i]=min(dp[i],costs[k]+dp[j]);
            }
        }
        return dp[0];
    }
};