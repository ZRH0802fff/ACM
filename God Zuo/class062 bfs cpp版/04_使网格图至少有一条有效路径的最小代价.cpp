// 使网格图至少有一条有效路径的最小代价
// 给你一个 m * n 的网格图 grid 。 grid 中每个格子都有一个数字
// 对应着从该格子出发下一步走的方向。 grid[i][j] 中的数字可能为以下几种情况：
// 1 ，下一步往右走，也就是你会从 grid[i][j] 走到 grid[i][j + 1]
// 2 ，下一步往左走，也就是你会从 grid[i][j] 走到 grid[i][j - 1]
// 3 ，下一步往下走，也就是你会从 grid[i][j] 走到 grid[i + 1][j]
// 4 ，下一步往上走，也就是你会从 grid[i][j] 走到 grid[i - 1][j]
// 注意网格图中可能会有 无效数字 ，因为它们可能指向 grid 以外的区域
// 一开始，你会从最左上角的格子 (0,0) 出发
// 我们定义一条 有效路径 为从格子 (0,0) 出发，每一步都顺着数字对应方向走
// 最终在最右下角的格子 (m - 1, n - 1) 结束的路径
// 有效路径 不需要是最短路径
// 你可以花费1的代价修改一个格子中的数字，但每个格子中的数字 只能修改一次
// 请你返回让网格图至少有一条有效路径的最小代价
// 测试链接 : https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10001;

// 01bfs，双端队列（第一维是 m*n <= 1e4，全局够用）
int deque_[MAXN][2];
int h, t;

// 格子的数值 :
// 1 右
// 2 左
// 3 下
// 4 上
//            0      1         2          3         4
int move_[5][2] = { {}, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // distance 对应 Java 的 new int[m][n]，得到具体 m、n 后再开二维数组（VLA）
        int distance[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                distance[i][j] = INT_MAX;
            }
        }
        h = t = MAXN / 2;
        deque_[h][0] = 0;
        deque_[h][1] = 0;
        distance[0][0] = 0;
        while (h <= t) {
            int x = deque_[h][0];
            int y = deque_[h++][1];
            if (x == m - 1 && y == n - 1) {
                return distance[x][y];
            }
            for (int i = 1; i <= 4; i++) {
                int nx = x + move_[i][0];
                int ny = y + move_[i][1];
                int weight = grid[x][y] != i ? 1 : 0;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n
                        && distance[x][y] + weight < distance[nx][ny]) {
                    distance[nx][ny] = distance[x][y] + weight;
                    if (weight == 0) {
                        deque_[--h][0] = nx;
                        deque_[h][1] = ny;
                    } else {
                        deque_[++t][0] = nx;
                        deque_[t][1] = ny;
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = {{1,1,1,1},{2,2,2,2},{1,1,1,1},{2,2,2,2}};
    cout << sol.minCost(grid1) << " (expected: 3)" << endl;
    vector<vector<int>> grid2 = {{1,1,3},{3,2,2},{1,1,4}};
    cout << sol.minCost(grid2) << " (expected: 0)" << endl;
    return 0;
}
