// 水资源分配优化
// 村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。
// 对于每个房子 i，我们有两种可选的供水方案：一种是直接在房子内建造水井
// 成本为 wells[i - 1] （注意 -1 ，因为 索引从0开始 ）
// 另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本，
// 其中每个 pipes[j] = [house1j, house2j, costj]
// 代表用管道将 house1j 和 house2j连接在一起的成本。连接是双向的。
// 请返回 为所有房子都供水的最低总成本
// 测试链接 : https://leetcode.cn/problems/optimize-water-distribution-in-a-village/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;

struct Edge {
    int u, v, w;
} edges[MAXN << 1];

int edgeCnt;

int father[MAXN];

void build(int n) {
    edgeCnt = 0;
    for (int i = 0; i <= n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 如果x和y，原本是一个集合，返回false
// 如果x和y，不是一个集合，合并之后后返回true
bool unionSet(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        return true;
    } else {
        return false;
    }
}

class Solution {
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        build(n);
        for (int i = 0; i < n; i++, edgeCnt++) {
            // wells : 100   30
            //         0(1)  1(2)
            edges[edgeCnt].u = 0;
            edges[edgeCnt].v = i + 1;
            edges[edgeCnt].w = wells[i];
        }
        for (int i = 0; i < (int)pipes.size(); i++, edgeCnt++) {
            edges[edgeCnt].u = pipes[i][0];
            edges[edgeCnt].v = pipes[i][1];
            edges[edgeCnt].w = pipes[i][2];
        }
        sort(edges, edges + edgeCnt, [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });
        int ans = 0;
        for (int i = 0; i < edgeCnt; i++) {
            if (unionSet(edges[i].u, edges[i].v)) {
                ans += edges[i].w;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    // 示例: n=3, wells=[1,2,2], pipes=[[1,2,1],[2,3,1]]
    vector<int> wells = {1, 2, 2};
    vector<vector<int>> pipes = {{1,2,1}, {2,3,1}};
    cout << "min cost: " << sol.minCostToSupplyWater(3, wells, pipes) << " (expected: 3)" << endl;
    return 0;
}
