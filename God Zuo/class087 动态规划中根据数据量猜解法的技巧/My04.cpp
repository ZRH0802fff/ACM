// 使数组严格递增的最小操作数
// 给你两个整数数组 arr1 和 arr2
// 返回使 arr1 严格递增所需要的最小操作数（可能为0）
// 每一步操作中，你可以分别从 arr1 和 arr2 中各选出一个索引
// 分别为 i 和 j，0 <= i < arr1.length 和 0 <= j < arr2.length
// 然后进行赋值运算 arr1[i] = arr2[j]
// 如果无法让 arr1 严格递增，请返回-1
// 1 <= arr1.length, arr2.length <= 2000
// 0 <= arr1[i], arr2[i] <= 10^9
// 测试链接 : https://leetcode.cn/problems/make-array-strictly-increasing/

#include<bits/stdc++.h>
using namespace std;

int dp[2010];
int n,m;

int bs(vector<int>& arr2,int size, int num){
    int l=0,r=size-1,m,ans=-1;
    while(l<=r){
        m=(l+r)/2;
        if(arr2[m]>num){
            ans=m;
            r=m-1;
        } else {
            l=m+1;
        }
    }
    return ans;
}

int f(vector<int>& arr1,vector<int>& arr2,int i){
    if(i==n) return 0;
    if(dp[i]!=-1) return dp[i];

    int ans=INT_MAX;
    int pre=(i==0)?INT_MIN:arr1[i-1];
    int find=bs(arr2,m,pre);
    for(int j=i,k=0,next;j<=n;++j,++k){
        if(j==n){
            ans=min(ans,k);
        }else{
            if(pre<arr1[j]){
                next=f(arr1,arr2,j+1);
                if(next!=INT_MAX){
                    ans=min(ans,k+next);
                }
            }
            if(find!=-1 && find<m){
                pre=arr2[find++];
            }else{
                break;
            }
        }
    }
    dp[i]=ans;
    return ans;
}

class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(),arr2.end());
        m=1;
        for(int i=1;i<(int)arr2.size();++i){
            if(arr2[i]!=arr2[m-1]){
                arr2[m++]=arr2[i];
            }
        }
        n=arr1.size();
        for(int i=0;i<=n;++i) dp[i]=-1;
        int ans=f(arr1,arr2,0);
        return ans==INT_MAX ? -1 : ans;

    }
};