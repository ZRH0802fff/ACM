// 到达首都的最少油耗
// 给你一棵 n 个节点的树（一个无向、连通、无环图）
// 每个节点表示一个城市，编号从 0 到 n - 1 ，且恰好有 n - 1 条路
// 0 是首都。给你一个二维整数数组 roads
// 其中 roads[i] = [ai, bi] ，表示城市 ai 和 bi 之间有一条 双向路
// 每个城市里有一个代表，他们都要去首都参加一个会议
// 每座城市里有一辆车。给你一个整数 seats 表示每辆车里面座位的数目
// 城市里的代表可以选择乘坐所在城市的车，或者乘坐其他城市的车
// 相邻城市之间一辆车的油耗是一升汽油
// 请你返回到达首都最少需要多少升汽油
// 测试链接 : https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> graph[MAXN];
int sz[MAXN];
long long cost[MAXN];

// 根据图，当前来到u，u的父节点是p
// 遍历完成后，请填好size[u]、cost[u]
void dfs(int seats, int u, int p) {
    sz[u] = 1;
    for (int v : graph[u]) {
        if (v != p) {
            dfs(seats, v, u);
            sz[u] += sz[v];
            cost[u] += cost[v];
            // a/b向上取整，可以写成(a+b-1)/b
            // (size[v]+seats-1) / seats = size[v] / seats 向上取整
            cost[u] += (sz[v] + seats - 1) / seats;
        }
    }
}

class Solution {
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size() + 1;
        for (int i = 0; i < n; i++) {
            graph[i].clear();
        }
        for (auto& r : roads) {
            graph[r[0]].push_back(r[1]);
            graph[r[1]].push_back(r[0]);
        }
        memset(sz, 0, sizeof(sz));
        memset(cost, 0, sizeof(cost));
        dfs(seats, 0, -1);
        return cost[0];
    }
};
