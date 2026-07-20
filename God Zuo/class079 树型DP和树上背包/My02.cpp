// 相邻字符不同的最长路径
// 给你一棵 树（即一个连通、无向、无环图），根节点是节点 0
// 这棵树由编号从 0 到 n - 1 的 n 个节点组成
// 用下标从 0 开始、长度为 n 的数组 parent 来表示这棵树
// 其中 parent[i] 是节点 i 的父节点
// 由于节点 0 是根节点，所以 parent[0] == -1
// 另给你一个字符串 s ，长度也是 n ，其中 s[i] 表示分配给节点 i 的字符
// 请你找出路径上任意一对相邻节点都没有分配到相同字符的 最长路径
// 并返回该路径的长度
// 测试链接 : https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> graph[100010];

    pair<int,int>f(string& s ,int u){
        if(graph[u].empty())
            return {1, 1};
        int max1 = 0;
        int max2 = 0;
        int maxPath = 0;
        for(int v:graph[u]){
            pair<int, int> ff = f(s, v);
            maxPath = max(maxPath, ff.second);
            if(s[u]!=s[v]){
                if(ff.first>max1){
                    max2 = max1;
                    max1 = ff.first;
                }else if(ff.first>max2){
                    max2 = ff.first;
                }
            }
        }
        int maxpathfromhead = max1 + 1;
        maxPath = max(maxPath, max1 + max2 + 1);
        return {maxpathfromhead, maxPath};
    }

    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        for (int i = 0; i <= n;++i)
            graph[i].clear();
        for (int i = 1; i < n;++i){
            graph[parent[i]].push_back(i);
        }
        return f(s, 0).second;
    }
};