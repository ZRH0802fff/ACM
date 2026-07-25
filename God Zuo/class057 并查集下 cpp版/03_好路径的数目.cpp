// 好路径的数目 — LeetCode 2421
// 好路径：起点和终点值相同，且路径上所有节点的值都 <= 起点值
// 按节点值从小到大处理边，维护每个连通分量中"最大值节点"的个数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;
int father[MAXN], maxcnt[MAXN];

class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        for (int i = 0; i < n; i++) father[i] = i, maxcnt[i] = 1;
        // 按边两端节点值的 max 从小到大排序
        sort(edges.begin(), edges.end(),
             [&](auto& a, auto& b) { return max(vals[a[0]], vals[a[1]]) < max(vals[b[0]], vals[b[1]]); });

        auto find = [&](int i) {
            while (i != father[i]) {
                father[i] = father[father[i]];
                i = father[i];
            }
            return i;
        };

        int ans = n; // 每个单独节点都是好路径
        for (auto& e : edges) {
            int fx = find(e[0]), fy = find(e[1]);
            if (fx == fy) continue;
            if (vals[fx] > vals[fy]) father[fy] = fx;
            else if (vals[fx] < vals[fy]) father[fx] = fy;
            else {
                // 值相等！两边最大值节点可以跨连通配对
                ans += maxcnt[fx] * maxcnt[fy];
                father[fy] = fx;
                maxcnt[fx] += maxcnt[fy];
            }
        }
        return ans;
    }
};
