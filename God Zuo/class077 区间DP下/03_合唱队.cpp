// 合唱队
// 具体描述情打开链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P3205

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
const int MOD = 19650827;
int nums[MAXN];
int dp[MAXN][2];
int dp3d[MAXN][MAXN][2];
int n;

// 时间复杂度O(n^2)
// 严格位置依赖的动态规划
int compute1() {
    // 人的编号范围 : 1...n
    // dp3d[l][r][0] : 形成l...r的状况的方法数，同时要求l位置的数字是最后出现的
    // dp3d[l][r][1] : 形成l...r的状况的方法数，同时要求r位置的数字是最后出现的
    memset(dp3d, 0, sizeof(dp3d));
    for (int i = 1; i < n; i++) {
        if (nums[i] < nums[i + 1]) {
            dp3d[i][i + 1][0] = 1;
            dp3d[i][i + 1][1] = 1;
        }
    }
    for (int l = n - 2; l >= 1; l--) {
        for (int r = l + 2; r <= n; r++) {
            if (nums[l] < nums[l + 1]) {
                dp3d[l][r][0] = (dp3d[l][r][0] + dp3d[l + 1][r][0]) % MOD;
            }
            if (nums[l] < nums[r]) {
                dp3d[l][r][0] = (dp3d[l][r][0] + dp3d[l + 1][r][1]) % MOD;
            }
            if (nums[r] > nums[l]) {
                dp3d[l][r][1] = (dp3d[l][r][1] + dp3d[l][r - 1][0]) % MOD;
            }
            if (nums[r] > nums[r - 1]) {
                dp3d[l][r][1] = (dp3d[l][r][1] + dp3d[l][r - 1][1]) % MOD;
            }
        }
    }
    return (dp3d[1][n][0] + dp3d[1][n][1]) % MOD;
}

// 时间复杂度O(n^2)
// 空间压缩
int compute2() {
    memset(dp, 0, sizeof(dp));
    if (nums[n - 1] < nums[n]) {
        dp[n][0] = 1;
        dp[n][1] = 1;
    }
    for (int l = n - 2; l >= 1; l--) {
        if (nums[l] < nums[l + 1]) {
            dp[l + 1][0] = 1;
            dp[l + 1][1] = 1;
        } else {
            dp[l + 1][0] = 0;
            dp[l + 1][1] = 0;
        }
        for (int r = l + 2; r <= n; r++) {
            int a = 0;
            int b = 0;
            if (nums[l] < nums[l + 1]) {
                a = (a + dp[r][0]) % MOD;
            }
            if (nums[l] < nums[r]) {
                a = (a + dp[r][1]) % MOD;
            }
            if (nums[r] > nums[l]) {
                b = (b + dp[r - 1][0]) % MOD;
            }
            if (nums[r] > nums[r - 1]) {
                b = (b + dp[r - 1][1]) % MOD;
            }
            dp[r][0] = a;
            dp[r][1] = b;
        }
    }
    return (dp[n][0] + dp[n][1]) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> nums[i];
        }
        if (n == 1) {
            cout << 1 << endl;
        } else {
            cout << compute2() << endl;
        }
    }
    return 0;
}
