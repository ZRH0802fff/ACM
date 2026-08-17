#include<bits/stdc++.h>
using namespace std;

int n,v;
int dp[105][105];
int arr[105][105];
int path[105];
int ans=INT_MIN;

void printDP(){
    //cout << "       ";
    for(int j = 1; j <= v; ++j){
        cout << setw(5) << j;
    }
    cout << '\n';

    for(int i = 1; i <= n; ++i){
        cout << setw(5) << i << " ";

        for(int j = 1; j <= v; ++j){
            cout << setw(5) << dp[i][j];
        }

        cout << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>v;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=v;++j){
            cin>>arr[i][j];
        }
    }

    for(int j=1;j<=v;++j){
        dp[1][j]=arr[1][j];
    }
    for(int i=2;i<=n;++i){
        for(int j=i;j<=v;++j){
            int pre=INT_MIN;
            for(int p=i-1;p<j;++p){
                pre=max(pre,dp[i-1][p]);
            }
            dp[i][j]=pre+arr[i][j];
        }
    }
    //printDP();
    int ls=0;
    for(int j=n;j<=v;++j){
        if(dp[n][j]>ans){
            ans=dp[n][j];
            ls=j;
        }
    }

    path[n]=ls;
    int cur=ans-arr[n][ls];
    for(int i=n-1,j=ls;i>=1;--i){
        while(j>=i && dp[i][j]!=cur) --j;
        path[i]=j;
        cur-=arr[i][j];
        j--;
    }

    cout<<ans<<'\n';
    for(int i=1;i<n;++i){
        cout<<path[i]<<' ';
    }
    cout<<path[n]<<'\n';
    return 0;
}