// 二维接雨水
// 给你一个 m * n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度
// 请计算图中形状最多能接多少体积的雨水。
// 测试链接 : https://leetcode.cn/problems/trapping-rain-water-ii/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 201;
const int MAXM = 201;

int move_[] = { -1, 0, 1, 0, -1 };

// 手写小根堆 (行, 列, 水线)
int heapSize;
int heap[MAXN * MAXM][3];

void push(int r, int c, int w) {
    int i = heapSize++;
    heap[i][0] = r;
    heap[i][1] = c;
    heap[i][2] = w;
    while (heap[i][2] < heap[(i - 1) / 2][2]) {
        swap(heap[i][0], heap[(i - 1) / 2][0]);
        swap(heap[i][1], heap[(i - 1) / 2][1]);
        swap(heap[i][2], heap[(i - 1) / 2][2]);
        i = (i - 1) / 2;
    }
}

void pop(int& r, int& c, int& w) {
    r = heap[0][0];
    c = heap[0][1];
    w = heap[0][2];
    heap[0][0] = heap[--heapSize][0];
    heap[0][1] = heap[heapSize][1];
    heap[0][2] = heap[heapSize][2];
    int i = 0;
    int l = 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][2] < heap[l][2] ? l + 1 : l;
        best = heap[best][2] < heap[i][2] ? best : i;
        if (best == i) break;
        swap(heap[best][0], heap[i][0]);
        swap(heap[best][1], heap[i][1]);
        swap(heap[best][2], heap[i][2]);
        i = best;
        l = i * 2 + 1;
    }
}

bool heapEmpty() {
    return heapSize == 0;
}

class Solution {
public:
    int trapRainWater(vector<vector<int>>& height) {
        int n = height.size();
        int m = height[0].size();
        // 0 : 行
        // 1 : 列
        // 2 : 水线
        heapSize = 0;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    // 边界
                    push(i, j, height[i][j]);
                    visited[i][j] = true;
                }
            }
        }
        int ans = 0;
        while (!heapEmpty()) {
            int r, c, w;
            pop(r, c, w);
            ans += w - height[r][c];
            for (int i = 0, nr, nc; i < 4; i++) {
                nr = r + move_[i];
                nc = c + move_[i + 1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc]) {
                    push(nr, nc, max(height[nr][nc], w));
                    visited[nr][nc] = true;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> height1 = {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
    cout << sol.trapRainWater(height1) << " (expected: 4)" << endl;
    vector<vector<int>> height2 = {{3,3,3,3,3},{3,2,2,2,3},{3,2,1,2,3},{3,2,2,2,3},{3,3,3,3,3}};
    cout << sol.trapRainWater(height2) << " (expected: 10)" << endl;
    return 0;
}
