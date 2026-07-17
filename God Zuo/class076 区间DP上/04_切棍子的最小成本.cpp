// 切棍子的最小成本
// 有一根长度为n个单位的木棍，棍上从0到n标记了若干位置
// 给你一个整数数组cuts，其中cuts[i]表示你需要将棍子切开的位置
// 你可以按顺序完成切割，也可以根据需要更改切割的顺序
// 每次切割的成本都是当前要切割的棍子的长度，切棍子的总成本是历次切割成本的总和
// 对棍子进行切割将会把一根木棍分成两根较小的木棍
// 这两根木棍的长度和就是切割前木棍的长度
// 返回切棍子的最小总成本
// 测试链接 : https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int arr[MAXN];
int dp[MAXN][MAXN];

class Solution {
public:
    // 记忆化搜索
    int minCost1(int n, vector<int>& cuts) {
        int m = cuts.size();
        sort(cuts.begin(), cuts.end());
        arr[0] = 0;
        for (int i = 1; i <= m; i++) {
            arr[i] = cuts[i - 1];
        }
        arr[m + 1] = n;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = -1;
            }
        }
        return f(1, m);
    }

    // 切点[l....r]，决定一个顺序
    // 让切点都切完，总代价最小
    int f(int l, int r) {
        if (l > r) {
            return 0;
        }
        if (l == r) {
            return arr[r + 1] - arr[l - 1];
        }
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans = INT_MAX;
        for (int k = l; k <= r; k++) {
            ans = min(ans, f(l, k - 1) + f(k + 1, r));
        }
        ans += arr[r + 1] - arr[l - 1];
        dp[l][r] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划
    int minCost2(int n, vector<int>& cuts) {
        int m = cuts.size();
        memset(dp, 0, sizeof(dp));
        sort(cuts.begin(), cuts.end());
        arr[0] = 0;
        for (int i = 1; i <= m; i++) {
            arr[i] = cuts[i - 1];
        }
        arr[m + 1] = n;
        for (int i = 1; i <= m; i++) {
            dp[i][i] = arr[i + 1] - arr[i - 1];
        }
        for (int l = m - 1, next; l >= 1; l--) {
            for (int r = l + 1; r <= m; r++) {
                next = INT_MAX;
                for (int k = l; k <= r; k++) {
                    next = min(next, dp[l][k - 1] + dp[k + 1][r]);
                }
                dp[l][r] = arr[r + 1] - arr[l - 1] + next;
            }
        }
        return dp[1][m];
    }
};

int main() {
    Solution sol;
    cout << "=== 切棍子的最小成本 ===" << endl;

    vector<int> cuts1 = {1, 3, 4, 5};
    cout << "n = 7, cuts = [1, 3, 4, 5], 预期: 16" << endl;
    cout << "记忆化: " << sol.minCost1(7, cuts1) << endl;
    cout << "动态规划: " << sol.minCost2(7, cuts1) << endl;
    cout << endl;

    vector<int> cuts2 = {5, 6, 1, 4, 2};
    cout << "n = 9, cuts = [5, 6, 1, 4, 2], 预期: 22" << endl;
    cout << "记忆化: " << sol.minCost1(9, cuts2) << endl;
    cout << "动态规划: " << sol.minCost2(9, cuts2) << endl;

    return 0;
}
