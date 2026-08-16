#include<bits/stdc++.h>
using namespace std;
#define int long long

string s;
int n,res;
int dp[42][100010];
int num[42][42];

signed main(){
    cin>>s>>res;
    n=s.length();
    memset(dp,0x3f,sizeof(dp));

    for(int i=1;i<=n;++i){
        for(int j=i;j<=n;++j){
            num[i][j]=num[i][j-1]*10+(s[j-1]-'0');
        }
    }
    dp[0][0]=-1;
    for(int i=1;i<=n;++i){
        for(int k=0;k<=res;++k){
            for(int j=i-1;j>=0 && num[j+1][i]<=res;--j){
                if(num[j+1][i]<=k){
                    dp[i][k]=min(dp[i][k],dp[j][k-num[j+1][i]]+1);
                }
            }
        }
    }

    if(dp[n][res]<45){
        cout<<dp[n][res]<<'\n';
    }else{
        cout<<-1<<'\n';
    }

    return 0;
}