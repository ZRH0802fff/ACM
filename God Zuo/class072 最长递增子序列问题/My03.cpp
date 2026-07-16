// 使数组K递增的最少操作次数
// 给你一个下标从0开始包含n个正整数的数组arr，和一个正整数k
// 如果对于每个满足 k <= i <= n-1 的下标 i
// 都有 arr[i-k] <= arr[i] ，那么称 arr 是K递增的
// 每一次操作中，你可以选择一个下标i并将arr[i]改成任意正整数
// 请你返回对于给定的 k ，使数组变成K递增的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-operations-to-make-the-array-k-increasing/
// 核心: 按i%k分成k组, 各组独立; 每组 len - 最长不下降长度 = 最少修改次数
// 坑点: 是不下降不是严格递增, 二分用 > num最左(bs2); 每组独立累加即可

#include<bits/stdc++.h>
using namespace std;

int nums[100010];
int ed[100010];

class Solution {
public:

    int f(int len,int num){
        int l=0,r=len-1,m,ans=-1;
        while(l<=r){
            m=(l+r)/2;
            if(ed[m]>num){
                ans=m;
                r=m-1;
            }else{
                l=m+1;
            }
        }
        return ans;
    }

    int longsize(int size){
        int len=0;
        for(int i=0,find;i<size;++i){
            find=f(len,nums[i]);
            if(find==-1){
                ed[len++]=nums[i];
            }else{
                ed[find]=nums[i];
            }
        }
        return len;
    }

    int kIncreasing(vector<int>& arr, int k) {
        int n=arr.size();
        int ans=0;
        for(int i=0,size;i<k;++i){
            size=0;
            for(int j=i;j<n;j+=k){
                nums[size++]=arr[j];
            }
            ans+=size-longsize(size);
        }
        return ans;
    }
};