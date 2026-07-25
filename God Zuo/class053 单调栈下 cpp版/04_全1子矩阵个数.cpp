// 统计全1子矩形个数 — LeetCode 1504
// 给定一个只含 0 和 1 的二维矩阵，统计其中全由 1 组成的子矩形数量

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 155;
int height[MAXN];
int stk[MAXN];
int r;

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int ans = 0;
        memset(height, 0, sizeof(height));

        for (int i = 0; i < n; i++) {
            // 1. 数组压缩：更新直方图高度
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) height[j] = 0;
                else height[j] += 1;
            }

            // 2. 单调栈计算当前直方图中全1子矩形数
            r = 0;
            for (int j = 0; j < m; j++) {
                while (r > 0 && height[stk[r - 1]] >= height[j]) {
                    int cur = stk[--r];
                    // 核心去重：相等时不结算，留到最后统一算
                    if (height[cur] > height[j]) {
                        int left = r > 0 ? stk[r - 1] : -1;
                        int len = j - left - 1;
                        int leftH = left != -1 ? height[left] : 0;
                        int bottom = leftH > height[j] ? leftH : height[j];
                        // 高度差 * 底边线段组合数
                        ans += (height[cur] - bottom) * len * (len + 1) / 2;
                    }
                }
                stk[r++] = j;
            }

            // 清算阶段
            while (r > 0) {
                int cur = stk[--r];
                int left = r > 0 ? stk[r - 1] : -1;
                int len = m - left - 1;
                int leftH = left != -1 ? height[left] : 0;
                ans += (height[cur] - leftH) * len * (len + 1) / 2;
            }
        }
        return ans;
    }
};
