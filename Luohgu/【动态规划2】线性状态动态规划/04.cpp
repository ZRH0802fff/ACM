/*
题面
    给定n长度数组，求有多少个子序列是等差序列，一个数本身也算
核心
    可变参数有两个，前i个数以及公差d，用dp[i][d]表示
    当两个数确认时，d就可以确认，那么内层循环枚举前面的数得公差比枚举公差更稳定
*/


#include<bits/stdc++.h>
using namespace std;

int n,ans;
int arr[1010];
int dp[1010][40010];
const int p = 20000;
const int MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    for (int i = 1; i <= n; ++i){
        ans++;
        for (int j = i - 1; j > 0; --j){
            int d = arr[i] - arr[j] + p;
            dp[i][d] += dp[j][d] + 1;
            dp[i][d] %= MOD;
            ans += dp[j][d] + 1;
            ans %= MOD;
        }
    }
    cout << ans << '\n';
    return 0;
}