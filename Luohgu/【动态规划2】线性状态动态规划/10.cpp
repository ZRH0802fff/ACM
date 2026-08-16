#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int dp[12][12][12];
int arr[12][12];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    int x,y,v;
    while(cin>>x>>y>>v){
        if(x==0 && y==0 && v==0) break;
        arr[x][y]=v;
    }
    for(int x1=1;x1<=n;++x1){
        for(int y1=1;y1<=n;++y1){
            for(int x2=1;x2<=n;++x2){
                int y2=x1+y1-x2;
                if(y2<1 || y2>n) continue;
                dp[x1][y1][x2]=max({dp[x1-1][y1][x2-1],dp[x1-1][y1][x2],dp[x1][y1-1][x2],dp[x1][y1-1][x2-1],dp[x1][y1-1][x2]});
                if(x1==x2 && y1==y2){
                    dp[x1][y1][x2]+=arr[x1][y1];
                }else{
                    dp[x1][y1][x2]+=arr[x1][y1]+arr[x2][y2];
                }
            }
        }
    }
    cout<<dp[n][n][n]<<'\n';
    return 0;
}