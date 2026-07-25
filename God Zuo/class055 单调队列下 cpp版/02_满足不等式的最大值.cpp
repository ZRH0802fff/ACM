// 满足不等式的最大值 — LeetCode 1499
// 给定 points 和 k，求 max(y_j + y_i + |x_j - x_i|)，其中 x_j - x_i <= k
// 即求 max(y_j + x_j + (y_i - x_i))，维护 y_i - x_i 的单调递减队列

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int q[MAXN];
int h, t;

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        int n = points.size();
        h = t = 0;
        int ans = INT_MIN;

        for (int j = 0; j < n; j++) {
            int xj = points[j][0], yj = points[j][1];
            // 淘汰过期元素（x_j - x_i > k）
            while (h < t && points[q[h]][0] + k < xj) h++;
            // 收集答案：当前队头是合法且 y_i - x_i 最大的
            if (h < t) {
                int yi = points[q[h]][1], xi = points[q[h]][0];
                ans = max(ans, yj + xj + yi - xi);
            }
            // 维护队尾单调递减（按 y_i - x_i）
            int diff = yj - xj;
            while (h < t) {
                int ti = q[t - 1];
                if (points[ti][1] - points[ti][0] <= diff) t--;
                else break;
            }
            q[t++] = j;
        }
        return ans;
    }
};
