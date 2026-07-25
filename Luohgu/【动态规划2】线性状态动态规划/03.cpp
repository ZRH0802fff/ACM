#include<bits/stdc++.h>
using namespace std;

int n, l, r, ans=INT_MIN;
int arr[200010];
int dp[200010];
int q[200010];
int h, t;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> l >> r;
    for (int i = 0; i <= n;++i)
        cin >> arr[i];
    for (int i = 1; i <= n; ++i){
        dp[i] = INT_MIN;
    }
    h = t = 0;
    for (int i = l; i <= n; ++i){
        int cur = i - l;
        while(h<t && dp[q[t-1]]<=dp[cur]) --t;
        q[t++] = cur;
        while(h<t && q[h]< i-r) ++h;
        if(h<t){
            dp[i] = dp[q[h]] + arr[i];
        }
    }
    for (int i = n - r + 1; i <= n; ++i){
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}