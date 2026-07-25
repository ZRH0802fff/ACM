// 柱状图中最大的矩形 — LeetCode 84
// 给定 n 个非负整数表示柱状图的高度，每个柱子宽度为 1
// 求柱状图中能勾勒出的最大矩形面积

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int stk[MAXN];
int r;

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        r = 0;

        for (int i = 0; i < n; i++) {
            while (r > 0 && height[stk[r - 1]] >= height[i]) {
                int cur = stk[--r];
                int left = r > 0 ? stk[r - 1] : -1;
                // 宽度 = i - left - 1（left 和 i 之间的区域）
                int area = height[cur] * (i - left - 1);
                if (area > ans) ans = area;
            }
            stk[r++] = i;
        }

        // 清算阶段
        while (r > 0) {
            int cur = stk[--r];
            int left = r > 0 ? stk[r - 1] : -1;
            int area = height[cur] * (n - left - 1);
            if (area > ans) ans = area;
        }

        return ans;
    }
};
