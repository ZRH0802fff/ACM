// 地图分析
// 你现在手里有一份大小为 n x n 的 网格 grid
// 上面的每个 单元格 都用 0 和 1 标记好了其中 0 代表海洋，1 代表陆地。
// 请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地单元格的距离是最大的
// 并返回该距离。如果网格上只有陆地或者海洋，请返回 -1。
// 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：
// (x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
// 测试链接 : https://leetcode.cn/problems/as-far-from-land-as-possible/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int MAXM = 101;

int queue_[MAXN * MAXM][2];
int l, r;
bool visited[MAXN][MAXM];

// 0:上，1:右，2:下，3:左
int move_[] = { -1, 0, 1, 0, -1 };
//              0  1  2  3   4
//                       i
// (x,y)  i来到0位置 : x + move[i], y + move[i+1] -> x - 1, y
// (x,y)  i来到1位置 : x + move[i], y + move[i+1] -> x, y + 1
// (x,y)  i来到2位置 : x + move[i], y + move[i+1] -> x + 1, y
// (x,y)  i来到3位置 : x + move[i], y + move[i+1] -> x, y - 1

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        l = r = 0;
        int n = grid.size();
        int m = grid[0].size();
        int seas = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    visited[i][j] = true;
                    queue_[r][0] = i;
                    queue_[r++][1] = j;
                } else {
                    visited[i][j] = false;
                    seas++;
                }
            }
        }
        if (seas == 0 || seas == n * m) {
            return -1;
        }
        int level = 0;
        while (l < r) {
            level++;
            int size = r - l;
            for (int k = 0, x, y, nx, ny; k < size; k++) {
                x = queue_[l][0];
                y = queue_[l++][1];
                for (int i = 0; i < 4; i++) {
                    // 上、右、下、左
                    nx = x + move_[i];
                    ny = y + move_[i + 1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        queue_[r][0] = nx;
                        queue_[r++][1] = ny;
                    }
                }
            }
        }
        return level - 1;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = {{1,0,1},{0,0,0},{1,0,1}};
    cout << sol.maxDistance(grid1) << " (expected: 2)" << endl;
    vector<vector<int>> grid2 = {{1,0,0},{0,0,0},{0,0,0}};
    cout << sol.maxDistance(grid2) << " (expected: 4)" << endl;
    return 0;
}
