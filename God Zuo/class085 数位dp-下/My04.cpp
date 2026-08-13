// 不含连续1的非负整数
// 给定一个正整数n，请你统计在[0, n]范围的非负整数中
// 有多少个整数的二进制表示中不存在连续的1
// 测试链接 : https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/

#include<bits/stdc++.h>
using namespace std;

//辅助数组，表示二进制如果有i位，所有二进制状态中不存在连续的1的状态有多少个

class Solution {
public:
    int cnt[31];
    /*
    从num的二进制高位开始，开到第i位，之前的位都和num一样
    返回<=num且不存在1的状态有多少个
    num 第i位如果是0，只能选1 -> 往下调递归
    num 第i位如果是1，可选择1和0 
                              选0 -> 直接加cnt[i],并加入判断：如果上一位也是1，直接返回
                              选1 -> 往下调递归
    */
    int f(int num,int i){
        if(i==-1) return 1;
        int ans=0;
        if((num&(1<<i))!=0){
            ans+=cnt[i];
            if((num & (1<<(i+1)))!=0) return ans;
        }
        ans+=f(num,i-1);
        return ans;
    }

    int findIntegers(int n) {
        cnt[0]=1;
        cnt[1]=2;
        for(int len=2;len<=30; ++len){
            cnt[len]=cnt[len-1]+cnt[len-2];
        }
        return f(n,30);
    }
};