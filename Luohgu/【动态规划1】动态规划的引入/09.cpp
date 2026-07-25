#include <bits/stdc++.h>
using namespace std;

int n,ans;
int nums[200010];
int dp[200010]; //表示必须以i结尾的最优

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> nums[i];
    dp[1] = nums[1];
    ans = dp[1];
    for (int i = 2; i <= n; ++i){
        dp[i] = max(nums[i], dp[i - 1] + nums[i]);
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}

/*
题意：
    求一个数组的最长子区间(s必须连续)
核心转化：
    dp[i]表示必须以i结尾情况下的最长子区间
    所以说dp[i]=max(nums[i],nums[i]+dp[i-1])
坑点：
    ans若起初赋值为0 当序列都是负数是答案都会是0
    把ans赋值为nums[1]即可避免
*/