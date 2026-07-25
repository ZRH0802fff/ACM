// 岛屿数量 — LeetCode 200
// 并查集解法：二维转一维，路径减半

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 90005;
int father[MAXN];

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int sets = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == '1') sets++;
        for (int i = 0; i < n * m; i++) father[i] = i;

        auto find = [&](int i) {
            while (i != father[i]) {
                father[i] = father[father[i]]; // 路径减半
                i = father[i];
            }
            return i;
        };

        auto unionSet = [&](int r1, int c1, int r2, int c2) {
            if (grid[r1][c1] != '1' || grid[r2][c2] != '1') return;
            int fx = find(r1 * m + c1), fy = find(r2 * m + c2);
            if (fx != fy) { father[fx] = fy; sets--; }
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    if (j > 0) unionSet(i, j, i, j - 1);
                    if (i > 0) unionSet(i, j, i - 1, j);
                }
            }
        }
        return sets;
    }
};
