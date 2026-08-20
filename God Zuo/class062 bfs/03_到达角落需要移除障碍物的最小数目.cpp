// 到达角落需要移除障碍物的最小数目
// 给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n
// 每个单元格都是两个值之一：
// 0 表示一个 空 单元格，
// 1 表示一个可以移除的 障碍物
// 你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。
// 现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1)
// 返回需要移除的障碍物的最小数目
// 测试链接 : https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

// 01bfs，双端队列（第一维是 m*n <= 1e5，全局够用）
int deque_[MAXN][2];
int h, t;

int move_[] = { -1, 0, 1, 0, -1 };

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // distance 对应 Java 的 new int[m][n]：
        // m、n 单维最大 1e5，但 m*n <= 1e5，全局 int distance[MAXN][MAXN] 会爆内存
        // 所以得到具体 m、n 后再开二维数组（VLA）
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
            for (int i = 0; i < 4; i++) {
                int nx = x + move_[i], ny = y + move_[i + 1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        distance[x][y] + grid[nx][ny] < distance[nx][ny]) {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
                    if (grid[nx][ny] == 0) {
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
    vector<vector<int>> grid1 = {{0,1,1},{1,1,0},{1,1,0}};
    cout << sol.minimumObstacles(grid1) << " (expected: 2)" << endl;
    vector<vector<int>> grid2 = {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
    cout << sol.minimumObstacles(grid2) << " (expected: 0)" << endl;
    return 0;
}
