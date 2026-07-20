// 从树中删除边的最小分数
// 存在一棵无向连通树，树中有编号从0到n-1的n个节点，以及n-1条边
// 给你一个下标从0开始的整数数组nums长度为n，其中nums[i]表示第i个节点的值
// 另给你一个二维整数数组edges长度为n-1
// 其中 edges[i] = [ai, bi] 表示树中存在一条位于节点 ai 和 bi 之间的边
// 删除树中两条不同的边以形成三个连通组件，对于一种删除边方案，定义如下步骤以计算其分数：
// 分别获取三个组件每个组件中所有节点值的异或值
// 最大 异或值和 最小 异或值的 差值 就是这种删除边方案的分数
// 返回可能的最小分数
// 测试链接 : https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int n,dfncnt;
    vector<int> graph[1010];
    int dfn[1010];
    int sz[101];
    int xorVal[1010];

    void bulid(int n){
        dfncnt = 0;
        for (int i = 0; i <= n;++i){
            graph[i].clear();
            dfn[i] = 0;
        }
    }

    void dfs(vector<int>& nums,int u){
        int i = ++dfncnt;
        dfn[u] = i;
        xorVal[i] = nums[u];
        sz[i] = 1;
        for(int v: graph[u]){
            if(dfn[v]==0){
                dfs(nums,v);
                xorVal[i] ^= xorVal[dfn[v]];
                sz[i] += sz[dfn[v]];
            }
        }
    }

    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        n = nums.size();
        bulid(n);
        for(auto& ed:edges){
            graph[ed[0]].push_back(ed[1]);
            graph[ed[1]].push_back(ed[0]);
        }
        dfs(nums, 0);
        int m = edges.size();
        int ans = INT_MAX;
        for (int i = 0,a,b,pre,pos,sum1,sum2,sum3; i < m;++i){
            a = max(dfn[edges[i][0]], dfn[edges[i][1]]);
            for (int j = i + 1; j < m; ++j){
                b = max(dfn[edges[j][0]], dfn[edges[j][1]]);
                if(a<b){
                    pre = a;
                    pos = b;
                }else{
                    pre = b;
                    pos = a;
                }
                sum1 = xorVal[pos];
                if(pos<pre+sz[pre]){
                    sum2 = xorVal[pre] ^ xorVal[pos];
                    sum3 = xorVal[1] ^ xorVal[pre];
                }else{
                    sum2 = xorVal[pre];
                    sum3 = xorVal[1] ^ sum1 ^ sum2;
                }
                ans = min(ans, max({sum1, sum2, sum3}) - min({sum1, sum2, sum3}));
            }
        }
        return ans;
    }
};