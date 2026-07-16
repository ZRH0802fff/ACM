// 最长递增子序列和最长不下降子序列
// 给定一个整数数组nums
// 找到其中最长严格递增子序列长度、最长不下降子序列长度
// 测试链接 : https://leetcode.cn/problems/longest-increasing-subsequence/
// 核心: edp[i] = 长度为i+1的递增子序列的最小结尾, edp严格升序, 每步二分 >= num 最左
// 坑点: ① edp不能叫ends(std::ends冲突) ② edp最终状态不代表实际LIS ③ 不下降用 > 最左

#include<bits/stdc++.h>
using namespace std;

int ed[2510];

class Solution {
public:
    //找到>=num的最左位置，不存在返回-1
    int f1(int len ,int num){
        int l=0,r=len-1;
        int m,ans=-1;
        while(l<=r){
            m=(l+r)/2;
            if(ed[m]>=num){
                ans=m;
                r=m-1;
            }else{
                l=m+1;
            }
        }
        return ans;
    }

    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        int len=0;
        for(int i=0,find;i<n;++i){
            find=f1(len,nums[i]);
            if(find==-1) 
                ed[len++]=nums[i];
            else
                ed[find]=nums[i];
        }
        return len;
    }
};