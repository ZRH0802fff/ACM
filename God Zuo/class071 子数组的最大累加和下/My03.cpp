// 魔法卷轴
// 给定一个数组nums，其中可能有正、负、0
// 每个魔法卷轴可以把nums中连续的一段全变成0
// 你希望数组整体的累加和尽可能大
// 卷轴使不使用、使用多少随意，但一共只有2个魔法卷轴
// 请返回数组尽可能大的累加和
// 对数器验证

#include<bits/stdc++.h>
using namespace std;

int pdp[100005];
int sdp[100005];

// 核心点
// 用两次可以分为不用，用1次，用2次
// 不用就是直接数组求和
// 用一次:  pdp[i] 表示前i个数必须且只能用一次魔法，
//        分两种情况: 1.第i个数不用，dp[i-1]
//                    2.第i个数用，就等于前面最大的前缀和，最大前缀和后到i个数都抹为0
//        已经处理好了各种边界，其中dp[0]默认为0，确保一定使用；使用魔法的时候dp[i]为最大前缀和，冲掉了前面使用的魔法，确保了魔法只有一次。
// 用2次: 以i为界，前面0...i-1用一次,后面的i...n-1用一次，枚举每一个断开点i，就能得到用两次的最大值。
//
// 坑点
// 1.用2次魔法时，如果此时前面那一次的魔法刚好把nums[i-1]刷成了0，后面的又从i就开始刷，这样一连起来就成了一次魔法，但是这确实是用1次和2次魔法的最优解不影响最终答案。
// 2.pdp以及sdp边界一些讨论，涵盖在状态转移方程中
int f2(vector<int>& nums){
    int n = nums.size();
    if(n==0)
        return 0;
    int p1 = 0;
    for(int num:nums)
        p1 += num;
    int sum = nums[0];
    int pmax = max(0, nums[0]);
    for (int i = 1; i < n;++i){
        pdp[i] = max(pdp[i - 1] + nums[i], pmax);
        sum += nums[i];
        pmax = max(pmax, sum);
    }
    int p2 = pdp[n - 1];
    sdp[n - 1] = 0;
    sum = nums[n - 1];
    pmax = max(0, sum);
    for (int i = n - 2; i >= 0;--i){
        sdp[i] = max(sdp[i + 1] + nums[i], pmax);
        sum += nums[i];
        pmax = max(pmax, sum);
    }
    int p3 = INT_MIN;
    for (int i = 1; i < n;++i){
        p3 = max(p3, pdp[i - 1] + sdp[i]);
    }
    return max(p1, max(p2, p3));
}