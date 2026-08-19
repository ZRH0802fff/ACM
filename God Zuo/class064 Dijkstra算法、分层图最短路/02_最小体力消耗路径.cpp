// 最小体力消耗路径
// 你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights
// 其中 heights[row][col] 表示格子 (row, col) 的高度
// 一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1)
// （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动
// 你想要找到耗费 体力 最小的一条路径
// 一条路径耗费的体力值是路径上，相邻格子之间高度差绝对值的最大值
// 请你返回从左上角走到右下角的最小 体力消耗值
// 测试链接 ：https://leetcode.cn/problems/path-with-minimum-effort/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int MAXM = 101;

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
    int minimumEffortPath(vector<vector<int>>& heights) {
        // (0,0)源点
        // -> (x,y)
        int n = heights.size();
        int m = heights[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                distance_[i][j] = INT_MAX;
            }
        }
        distance_[0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }
        heap = priority_queue<Record, vector<Record>, Cmp>();
        heap.push({ 0, 0, 0 });
        while (!heap.empty()) {
            Record rec = heap.top();
            heap.pop();
            int x = rec.x;
            int y = rec.y;
            int c = rec.c;
            if (visited[x][y]) {
                continue;
            }
            if (x == n - 1 && y == m - 1) {
                // 常见剪枝
                // 发现终点直接返回
                // 不用等都结束
                return c;
            }
            visited[x][y] = true;
            for (int i = 0; i < 4; i++) {
                int nx = x + move_[i];
                int ny = y + move_[i + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                    int nc = max(c, abs(heights[x][y] - heights[nx][ny]));
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
    vector<vector<int>> heights1 = { { 1, 2, 2 }, { 3, 8, 2 }, { 5, 3, 5 } };
    cout << sol.minimumEffortPath(heights1) << " (expected: 2)" << endl;
    vector<vector<int>> heights2 = { { 1, 2, 3 }, { 3, 8, 4 }, { 5, 3, 5 } };
    cout << sol.minimumEffortPath(heights2) << " (expected: 1)" << endl;
    return 0;
}
