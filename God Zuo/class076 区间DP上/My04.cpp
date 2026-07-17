// 切棍子的最小成本
// 有一根长度为n个单位的木棍，棍上从0到n标记了若干位置
// 给你一个整数数组cuts，其中cuts[i]表示你需要将棍子切开的位置
// 你可以按顺序完成切割，也可以根据需要更改切割的顺序
// 每次切割的成本都是当前要切割的棍子的长度，切棍子的总成本是历次切割成本的总和
// 对棍子进行切割将会把一根木棍分成两根较小的木棍
// 这两根木棍的长度和就是切割前木棍的长度
// 返回切棍子的最小总成本
// 测试链接 : https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int dp[105][105];

    int f(int* arr,int l,int r){
        if(l>r)
            return 0;
        if(l==r)
            return arr[r + 1] - arr[l - 1];
        if(dp[l][r]!=-1)
            return dp[l][r];
        int ans = INT_MAX;
        for (int k = l; k <= r;++k){
            ans = min(ans, f(arr,l, k - 1) + f(arr,k + 1, r));
        }
        ans += arr[r + 1] - arr[l - 1];
        dp[l][r] = ans;
        return ans;
    }

    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        sort(cuts.begin(), cuts.end());
        int arr[m + 2];
        arr[0] = 0;
        for (int i = 1; i <= m; ++i){
            arr[i] = cuts[i - 1];
        }
        arr[m + 1] = n;
        for (int i = 0; i <= m;++i){
            for (int j = 0; j <= m;++j)
                dp[i][j] = -1;
        }
        return f(arr, 1, m);
    }
}; 