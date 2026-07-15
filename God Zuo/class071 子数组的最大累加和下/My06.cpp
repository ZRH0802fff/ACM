// 删掉1个数字后长度为k的子数组最大累加和
// 给定一个数组nums，求必须删除一个数字后的新数组中
// 长度为k的子数组最大累加和，删除哪个数字随意
// 对数器验证

#include<bits/stdc++.h>
using namespace std;

int wd[10010];

int f2(vector<int>& nums,int k){
    int n = nums.size();
    if(n<=k){
        return 0;
    }
    int l = 0, r = 0;
    long long sum = 0;
    int ans = INT_MIN;
    for (int i = 0; i < n;++i){
        while(l<r && nums[wd[r-1]]>=nums[i])
            --r;
        wd[r++] = i;
        sum += nums[i];
    }
}