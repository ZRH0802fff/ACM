// 移除盒子
// 给出一些不同颜色的盒子boxes，盒子的颜色由不同的正数表示
// 你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止
// 每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1）
// 这样一轮之后你将得到 k * k 个积分
// 返回你能获得的最大积分总和
// 测试链接 : https://leetcode.cn/problems/remove-boxes/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[105][105][105];

    int f(vector<int>& arr,int l,int r,int k){
        if(l>r)
            return 0;
        if(dp[l][r][k] > 0)
            return dp[l][r][k];
        int s = l;
        while(s+1<=r && arr[l]==arr[s+1])
            ++s;
        int cnt = k + s - l + 1;
        int ans = cnt * cnt + f(arr, s + 1, r, 0);
        for (int m = s + 2; m <= r;++m){
            if(arr[l]==arr[m] && arr[m-1]!=arr[m]){
                ans = max(ans, f(arr, s + 1, m - 1, 0) + f(arr, m, r, cnt));
            }
        }
        dp[l][r][k] = ans;
        return ans;
    }


    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        for (int i = 0; i <= n;++i){
            for (int j = 0; j <= n;++j){
                for (int k = 0;k<=n;++k){
                    dp[i][j][k] = 0;
                }
            }
        }
        return f(boxes, 0, n - 1, 0);
    }
};


