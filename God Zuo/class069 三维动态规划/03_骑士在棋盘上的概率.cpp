// 骑士在棋盘上的概率
// n * n的国际象棋棋盘上，一个骑士从单元格(row, col)开始，并尝试进行 k 次移动
// 行和列从0开始，所以左上单元格是 (0,0)，右下单元格是 (n-1, n-1)
// 象棋骑士有8种可能的走法。每次移动在基本方向上是两个单元格，然后在正交方向上是一个单元格
// 每次骑士要移动时，它都会随机从8种可能的移动中选择一种，然后移动到那里
// 骑士继续移动，直到它走了 k 步或离开了棋盘
// 返回 骑士在棋盘停止移动后仍留在棋盘上的概率
// 测试链接 : https://leetcode.cn/problems/knight-probability-in-chessboard/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 记忆化搜索
    // 从(i,j)出发还有k步要走，返回最后在棋盘上的概率
    double f(int n, int i, int j, int k, vector<vector<vector<double>>>& dp) {
        if (i < 0 || i >= n || j < 0 || j >= n) {
            return 0;
        }
        if (dp[i][j][k] != -1) {
            return dp[i][j][k];
        }
        double ans = 0;
        if (k == 0) {
            ans = 1;
        } else {
            ans += (f(n, i - 2, j + 1, k - 1, dp) / 8);
            ans += (f(n, i - 1, j + 2, k - 1, dp) / 8);
            ans += (f(n, i + 1, j + 2, k - 1, dp) / 8);
            ans += (f(n, i + 2, j + 1, k - 1, dp) / 8);
            ans += (f(n, i + 2, j - 1, k - 1, dp) / 8);
            ans += (f(n, i + 1, j - 2, k - 1, dp) / 8);
            ans += (f(n, i - 1, j - 2, k - 1, dp) / 8);
            ans += (f(n, i - 2, j - 1, k - 1, dp) / 8);
        }
        dp[i][j][k] = ans;
        return ans;
    }

    double knightProbability(int n, int k, int row, int column) {
        vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(k + 1, -1)));
        return f(n, row, column, k, dp);
    }
};

// 测试代码
int main() {
    Solution sol;
    int n = 3, k = 2, row = 0, col = 0;
    cout << fixed << setprecision(6);
    cout << "knightProbability: " << sol.knightProbability(n, k, row, col) << endl;

    n = 1; k = 0; row = 0; col = 0;
    cout << "knightProbability: " << sol.knightProbability(n, k, row, col) << endl;
    return 0;
}
