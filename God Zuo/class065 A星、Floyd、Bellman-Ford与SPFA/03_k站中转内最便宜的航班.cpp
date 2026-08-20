// Bellman-Ford算法应用（不是模版）
// k站中转内最便宜的航班
// 有 n 个城市通过一些航班连接。给你一个数组 flights
// 其中 flights[i] = [fromi, toi, pricei]
// 表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。
// 现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到出一条最多经过 k 站中转的路线
// 使得从 src 到 dst 的 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1。
// 测试链接 : https://leetcode.cn/problems/cheapest-flights-within-k-stops/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;

int cur[MAXN];
int next_[MAXN];

class Solution {
public:
    // Bellman-Ford算法
    // 针对此题改写了松弛逻辑，课上讲了细节
    int findCheapestPrice(int n, vector<vector<int>>& flights, int start, int target, int k) {
        for (int i = 0; i < n; i++) {
            cur[i] = INT_MAX;
        }
        cur[start] = 0;
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j < n; j++) {
                next_[j] = cur[j];
            }
            for (auto& edge : flights) {
                // a -> b , w
                if (cur[edge[0]] != INT_MAX) {
                    next_[edge[1]] = min(next_[edge[1]], cur[edge[0]] + edge[2]);
                }
            }
            for (int j = 0; j < n; j++) {
                cur[j] = next_[j];
            }
        }
        return cur[target] == INT_MAX ? -1 : cur[target];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> flights1 = { { 0, 1, 100 }, { 1, 2, 100 }, { 2, 0, 100 }, { 1, 3, 600 }, { 2, 3, 200 } };
    cout << sol.findCheapestPrice(4, flights1, 0, 3, 1) << " (expected: 700)" << endl;
    vector<vector<int>> flights2 = { { 0, 1, 100 }, { 1, 2, 100 }, { 0, 2, 500 } };
    cout << sol.findCheapestPrice(3, flights2, 0, 2, 1) << " (expected: 200)" << endl;
    vector<vector<int>> flights3 = { { 0, 1, 100 }, { 1, 2, 100 }, { 0, 2, 500 } };
    cout << sol.findCheapestPrice(3, flights3, 0, 2, 0) << " (expected: 500)" << endl;
    return 0;
}
