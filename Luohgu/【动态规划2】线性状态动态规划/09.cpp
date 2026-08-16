#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k,ans;
int dp[105][105][105];
int arr[105][105];


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    k=k<n?k:n;
    for(int i=0;i<=n;++i){
        for(int j=0;j<=n;++j){
            for(int l=0;l<=k;++l){
                dp[i][j][l]=-4e18;
            }
        }
    }
    dp[0][0][0]=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=i;++j){
            cin>>arr[i][j];
            for(int p=0;p<=k && p<=i;++p){
                dp[i][j][p] = max(dp[i - 1][j][p],dp[i - 1][j - 1][p]) + arr[i][j];
                if (p > 0) {
                    dp[i][j][p] = max(dp[i][j][p],max(dp[i - 1][j][p - 1],dp[i - 1][j - 1][p - 1]) + arr[i][j] * 3);
                }
            }
        }
    }
    
    ans=-4e18;
    for(int j=1;j<=n;++j){
        for(int l=0;l<=k;++l){
            ans=max(ans,dp[n][j][l]);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
