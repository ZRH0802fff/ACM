// 贿赂怪兽
// 开始时你的能力是0，你的目标是从0号怪兽开始，通过所有的n只怪兽
// 如果你当前的能力小于i号怪兽的能力，则必须付出b[i]的钱贿赂这个怪兽
// 然后怪兽就会加入你，他的能力a[i]直接累加到你的能力上
// 如果你当前的能力大于等于i号怪兽的能力，你可以选择直接通过，且能力不会下降
// 但你依然可以选择贿赂这个怪兽，然后怪兽的能力直接累加到你的能力上
// 返回通过所有的怪兽，需要花的最小钱数
// 测试链接 : https://www.nowcoder.com/practice/736e12861f9746ab8ae064d4aae2d5a9
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

// 讲解本题的目的不仅仅是为了通过这个题，而是进行如下的思考:
// 假设a[i]数值的范围很大，但是b[i]数值的范围不大，该怎么做？
// 假设a[i]数值的范围不大，但是b[i]数值的范围很大，又该怎么做？

// 题目1在课程里没有给出明确的数据量（字幕里说"假设没有数据量"）
// 这里用字幕里的示例规模：n <= 1000，能力a[i] <= 10^4，钱b[i] <= 10
// 两种设定下，dp列的累加和（钱或能力）都不超过 1000 * 10 = 10^4
const int MAXN = 1001;
const int MAXM = 10001;

int a[MAXN];
int b[MAXN];
int dp2D[MAXN][MAXM]; // 二维表，compute1 / compute3 共用
int dp1D[MAXM];       // 一维表，compute2 / compute4 共用

// 假设a[i]数值的范围很大，但是b[i]数值的范围不大
// 时间复杂度O(n * 所有怪兽的钱数累加和)
int compute1(int n) {
    int m = 0;
    for (int i = 1; i <= n; i++) {
        m += b[i];
    }
    // dp[i][j] : 花的钱不能超过j，通过前i个怪兽，最大能力是多少
    // 如果dp[i][j] == INT_MIN
    // 表示花的钱不能超过j，无论如何都无法通过前i个怪兽
    for (int j = 0; j <= m; j++) {
        dp2D[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp2D[i][j] = INT_MIN;
            if (dp2D[i - 1][j] >= a[i]) {
                dp2D[i][j] = dp2D[i - 1][j];
            }
            if (j - b[i] >= 0 && dp2D[i - 1][j - b[i]] != INT_MIN) {
                dp2D[i][j] = max(dp2D[i][j], dp2D[i - 1][j - b[i]] + a[i]);
            }
        }
    }
    int ans = -1;
    for (int j = 0; j <= m; j++) {
        if (dp2D[n][j] != INT_MIN) {
            ans = j;
            break;
        }
    }
    return ans;
}

// 就是方法1的空间压缩版本
int compute2(int n) {
    int m = 0;
    for (int i = 1; i <= n; i++) {
        m += b[i];
    }
    for (int j = 0; j <= m; j++) {
        dp1D[j] = 0;
    }
    for (int i = 1, cur; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            cur = INT_MIN;
            if (dp1D[j] >= a[i]) {
                cur = dp1D[j];
            }
            if (j - b[i] >= 0 && dp1D[j - b[i]] != INT_MIN) {
                cur = max(cur, dp1D[j - b[i]] + a[i]);
            }
            dp1D[j] = cur;
        }
    }
    int ans = -1;
    for (int j = 0; j <= m; j++) {
        if (dp1D[j] != INT_MIN) {
            ans = j;
            break;
        }
    }
    return ans;
}

// 假设a[i]数值的范围不大，但是b[i]数值的范围很大
// 时间复杂度O(n * 所有怪兽的能力累加和)
int compute3(int n) {
    int m = 0;
    for (int i = 1; i <= n; i++) {
        m += a[i];
    }
    // dp[i][j] : 能力正好是j，并且确保能通过前i个怪兽，需要至少花多少钱
    // 如果dp[i][j] == INT_MAX
    // 表示能力正好是j，无论如何都无法通过前i个怪兽
    dp2D[0][0] = 0;
    for (int j = 1; j <= m; j++) {
        dp2D[0][j] = INT_MAX;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp2D[i][j] = INT_MAX;
            if (j >= a[i] && dp2D[i - 1][j] != INT_MAX) {
                dp2D[i][j] = dp2D[i - 1][j];
            }
            if (j - a[i] >= 0 && dp2D[i - 1][j - a[i]] != INT_MAX) {
                dp2D[i][j] = min(dp2D[i][j], dp2D[i - 1][j - a[i]] + b[i]);
            }
        }
    }
    int ans = INT_MAX;
    for (int j = 0; j <= m; j++) {
        ans = min(ans, dp2D[n][j]);
    }
    return ans == INT_MAX ? -1 : ans;
}

// 就是方法3的空间压缩版本
int compute4(int n) {
    int m = 0;
    for (int i = 1; i <= n; i++) {
        m += a[i];
    }
    dp1D[0] = 0;
    for (int j = 1; j <= m; j++) {
        dp1D[j] = INT_MAX;
    }
    for (int i = 1, cur; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            cur = INT_MAX;
            if (j >= a[i] && dp1D[j] != INT_MAX) {
                cur = dp1D[j];
            }
            if (j - a[i] >= 0 && dp1D[j - a[i]] != INT_MAX) {
                cur = min(cur, dp1D[j - a[i]] + b[i]);
            }
            dp1D[j] = cur;
        }
    }
    int ans = INT_MAX;
    for (int j = 0; j <= m; j++) {
        ans = min(ans, dp1D[j]);
    }
    return ans == INT_MAX ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i] >> b[i];
        }
        cout << compute1(n) << "\n";
    }
    return 0;
}
