// 最大矩形 — LeetCode 85
// 给定一个仅包含 0 和 1 的二维矩阵，找出只包含 1 的最大矩形，并返回其面积
// 转化为：以每一行为底的直方图最大矩形问题（LeetCode 84）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
int height[MAXN];
int stk[MAXN];
int r;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size();
        int m = matrix[0].size();
        int ans = 0;

        // height 数组全局复用
        memset(height, 0, sizeof(height));

        for (int i = 0; i < n; i++) {
            // 1. 加工出以 i 行为底的直方图高度
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == '0') {
                    height[j] = 0;
                } else {
                    height[j] += 1;
                }
            }

            // 2. 单调栈计算当前直方图的最大矩形面积
            r = 0;
            for (int j = 0; j < m; j++) {
                while (r > 0 && height[stk[r - 1]] >= height[j]) {
                    int cur = stk[--r];
                    int left = r > 0 ? stk[r - 1] : -1;
                    int area = height[cur] * (j - left - 1);
                    if (area > ans) ans = area;
                }
                stk[r++] = j;
            }

            // 清算留在栈中的元素
            while (r > 0) {
                int cur = stk[--r];
                int left = r > 0 ? stk[r - 1] : -1;
                int area = height[cur] * (m - left - 1);
                if (area > ans) ans = area;
            }
        }

        return ans;
    }
};
