// 水位上升的泳池中游泳
// 在一个 n x n 的整数矩阵 grid 中
// 每一个方格的值 grid[i][j] 表示位置 (i, j) 的平台高度
// 当开始下雨时，在时间为 t 时，水池中的水位为 t
// 你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台
// 假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的
// 当然，在你游泳的时候你必须待在坐标方格里面。
// 你从坐标方格的左上平台 (0，0) 出发
// 返回 你到达坐标方格的右下平台 (n-1, n-1) 所需的最少时间
// 测试链接 : https://leetcode.cn/problems/swim-in-rising-water/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51;
const int MAXM = 51;

// 0:上，1:右，2:下，3:左
int move_[] = { -1, 0, 1, 0, -1 };

int distance_[MAXN][MAXM];
bool visited[MAXN][MAXM];

// 小根堆的记录
// 0 : 格子的行
// 1 : 格子的列
// 2 : 源点到当前格子的代价
struct Record {
    int x, y, c;
};
// 按代价组织小根堆
struct Cmp {
    bool operator()(const Record& a, const Record& b) const {
        return a.c > b.c;
    }
};
priority_queue<Record, vector<Record>, Cmp> heap;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                distance_[i][j] = INT_MAX;
            }
        }
        distance_[0][0] = grid[0][0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }
        heap = priority_queue<Record, vector<Record>, Cmp>();
        heap.push({ 0, 0, grid[0][0] });
        while (!heap.empty()) {
            Record rec = heap.top();
            heap.pop();
            int x = rec.x;
            int y = rec.y;
            int c = rec.c;
            if (visited[x][y]) {
                continue;
            }
            visited[x][y] = true;
            if (x == n - 1 && y == m - 1) {
                // 常见剪枝
                // 发现终点直接返回
                // 不用等都结束
                return c;
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + move_[i];
                int ny = y + move_[i + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                    int nc = max(c, grid[nx][ny]);
                    if (nc < distance_[nx][ny]) {
                        distance_[nx][ny] = nc;
                        heap.push({ nx, ny, nc });
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = { { 0, 2 }, { 1, 3 } };
    cout << sol.swimInWater(grid1) << " (expected: 3)" << endl;
    vector<vector<int>> grid2 = { { 0, 1, 2, 3, 4 }, { 24, 23, 22, 21, 5 }, { 12, 13, 14, 15, 16 }, { 11, 17, 18, 19, 20 }, { 10, 9, 8, 7, 6 } };
    cout << sol.swimInWater(grid2) << " (expected: 16)" << endl;
    return 0;
}
