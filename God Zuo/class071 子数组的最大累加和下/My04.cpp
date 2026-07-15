// 三个无重叠子数组的最大和
// 给你一个整数数组 nums 和一个整数 k
// 找出三个长度为 k 、互不重叠、且全部数字和（3 * k 项）最大的子数组
// 并返回这三个子数组
// 以下标的数组形式返回结果，数组中的每一项分别指示每个子数组的起始位置
// 如果有多个结果，返回字典序最小的一个
// 测试链接 : https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/

//此题核心
//将三个无重复数组转化为 [0...i-1],[i,j],[j+1...n-1]上的最大子数组
//其中枚举[i..j](定长为k), 另外两个区间分别用prefix[i-1],suffix[j+1]来维持
//坑点
//字典序最小的维持方法
//prefix[i]在求后一位置的时候只有严格大于前一位置的sums才会更新来保证a最小
//suffix[i]在求前一位置的时候一旦大于等于后一位置的sums就会更新来保证c最小
//在枚举i,j时只有新的i,j严格大于之前的解才会更新maxsum来保证b最小


#include<bits/stdc++.h>
using namespace std;

// sums[i] : 以i开头并且长度为k的子数组的累加和
// prefix[i] : 0~i范围上所有长度为k的子数组中，拥有最大累加和的子数组的开头
// suffix[i] : i~n-1范围上所有长度为k的子数组中，拥有最大累加和的子数组的开头
const int MAXN = 20010;
int sums[MAXN];
int prefix[MAXN];
int suffix[MAXN];
int a, b, c, maxsum;


class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i <= n;++i){
            sums[i] = 0;
            prefix[i] = 0;
            suffix[i] = 0;
        }


        //sums
        for (int l = 0, r = 0, sum = 0; r < n; r++){
            sum += nums[r];
            if(r-l+1==k){
                sums[l] = sum;
                sum -= nums[l];
                l++;
            }
        }

        // prefix
        // k=3
        // p[0]: 0..0
        // p[1]: 0..1
        // p[2]: 0..2
        // p[3]: 1..3 PK 0..2
        for (int l = 1, r = k; r < n; l++, r++){
            // 0...l-1每一个开头与l开头的进行PK
            if(sums[l]>sums[prefix[r-1]]){
                prefix[r] = l;
            }else{
                prefix[r] = prefix[r - 1];
            }
        }

        //suffix
        //s[n-1]: n-1..n-1 -> 0
        //s[n-2]: n-2..n-1 -> 0
        //s[n-3]: n-3..n-1 -> n-k
        //s[n-4]: n-4..n-2 PK n-3..n-1 -> l from n-k-1 to 0 PK with s[l+1]
        suffix[n - k] = n - k;
        for (int l = n - k - 1; l >= 0; l--){
            if (sums[l] >= sums[suffix[l + 1]]){
                suffix[l] = l;
            }else{
                suffix[l] = suffix[l + 1];
            }
        }

        a = 0, b = 0, c = 0, maxsum = 0;
        for (int p, s, sum, i = k, j = 2 * k - 1; j < n - k; ++i, ++j){
            p = prefix[i - 1];
            s = suffix[j + 1];
            sum = sums[p] + sums[i] + sums[s];
            if(sum>maxsum){
                maxsum = sum;
                a = p;
                b = i;
                c = s;
            }
        }
        return {a, b, c};
    }
};


