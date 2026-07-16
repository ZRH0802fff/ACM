// 最长数对链
// 给你一个由n个数对组成的数对数组pairs
// 其中 pairs[i] = [lefti, righti] 且 lefti < righti
// 现在，我们定义一种 跟随 关系，当且仅当 b < c 时
// 数对 p2 = [c, d] 才可以跟在 p1 = [a, b] 后面
// 我们用这种形式来构造 数对链
// 找出并返回能够形成的最长数对链的长度
// 测试链接 : https://leetcode.cn/problems/maximum-length-of-pair-chain/
// 核心: 法1=按开头排序+LIS分离技巧(查开头>=最左, 入结尾, 更小才更新); 法2=按结尾排序贪心
// 坑点: LIS法中 edp[find]=min(edp[find], pair[1]) 必须取min而非直接覆盖

#include<bits/stdc++.h>
using namespace std;

int ed[1010];

class Solution {
public:

    int f(int len,int num){
        int l=0,r=len-1,m,ans=-1;
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

    int findLongestChain(vector<vector<int>>& pairs) {
        int n=pairs.size();
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        int len=0;
        for(int i=0;i<n;++i){
            int find=f(len,pairs[i][0]);
            if(find==-1){
                ed[len++]=pairs[i][1];
            }else{
                ed[find]=min(ed[find],pairs[i][1]);
            }
        }
        return len;
    }
};