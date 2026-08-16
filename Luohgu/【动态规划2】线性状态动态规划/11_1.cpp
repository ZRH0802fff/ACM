#include<bits/stdc++.h>
using namespace std;

int n,ans;
int up[105];
int down[105];
int zarr[105];
int darr[105];
int edp[105];

int bs1(int len,int num){
    int l=0,r=len-1,m,ans=-1;
    while(l<=r){
        m=(l+r)/2;
        if(edp[m]>=num){
            ans=m;
            r=m-1;
        }else{
            l=m+1;
        }
    }
    return ans;
}

int lis(int sta,int ed){
    int len=0;
    for(int i=sta,find;i<=ed;++i){
        find=bs1(len,zarr[i]);
        if(find==-1){
            edp[len++]=zarr[i];
        }else{
            edp[find]=zarr[i];
        }
    }
    return len;
}

int flis(int sta,int ed){
    int len=0;
    for(int i=sta,find;i<=ed;++i){
        find=bs1(len,darr[i]);
        if(find==-1){
            edp[len++]=darr[i];
        }else{
            edp[find]=darr[i];
        }
    }
    return len;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>zarr[i];
        darr[n-1-i]=zarr[i];
    }
    for(int i=0;i<n;++i){
        up[i]=lis(0,i);
    }
    for(int i=0;i<=n;++i){
        edp[i]=0;
    }
    for(int i=0;i<n;++i){
        down[n-i-1]=flis(0,i);
    }
    for(int i=0;i<n;++i){
        ans=max(ans,up[i]+down[i]-1);
    }
    cout<<n-ans<<'\n';
    return 0;
}