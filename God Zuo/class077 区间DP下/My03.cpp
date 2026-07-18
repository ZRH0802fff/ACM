// 合唱队
// 具体描述情打开链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P3205

#include<bits/stdc++.h>
using namespace std;

const int MOD = 19650827;
int dp[1010][1010][2];
int nums[1010];
int n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> nums[i];
    for (int i = 0; i <= n;++i){
        for (int j = 0; j <= n;++j){
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
        }
    }
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] < nums[i + 1])
            {
                dp[i][i + 1][0] = 1;
                dp[i][i + 1][1] = 1;
            }
        }
    for (int l = n - 2; l >  0; --l) {
        for (int r = l + 2; r <= n;++r){
            if(nums[l]<nums[l+1]){
                dp[l][r][0] = (dp[l][r][0] + dp[l + 1][r][0]) % MOD;
            }
            if(nums[l]<nums[r]){
                dp[l][r][0] = (dp[l][r][0] + dp[l + 1][r][1]) % MOD;
            }
            if (nums[r] > nums[l]){
                dp[l][r][1] = (dp[l][r][1] + dp[l][r - 1][0]) % MOD;
            }
            if(nums[r]>nums[r-1]){
                dp[l][r][1] = (dp[l][r][1] + dp[l][r - 1][1]) % MOD;
            }
        }
    }
    cout << (dp[1][n][0] + dp[1][n][1]) % MOD << '\n';
    return 0;
}