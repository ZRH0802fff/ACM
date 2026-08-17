#include<bits/stdc++.h>
using namespace std;

int n,ans;
int arr[410][2];
int dp[800010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>arr[i][0]>>arr[i][1];
    }

    memset(dp,-0x3f,sizeof(dp));
    dp[400000]=0;
    for(int i=1;i<=n;++i){
        if(arr[i][0]>=0){
            for(int j=800000;j>=arr[i][0];--j){
                dp[j]=max(dp[j],dp[j-arr[i][0]]+arr[i][1]);
            }
        }else{
            for(int j=0;j<=800000+arr[i][0];++j){
                dp[j]=max(dp[j],dp[j-arr[i][0]]+arr[i][1]);
            }
        }
    }

    for(int i=400000; i<=800000;++i){
        if(dp[i]>=0){
            ans=max(ans,i+dp[i]-400000);
        }
    }
    cout<<ans<<'\n';
    return 0;
}