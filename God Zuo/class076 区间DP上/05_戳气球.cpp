// 戳气球
// 有 n 个气球，编号为0到n-1，每个气球上都标有一个数字，这些数字存在数组nums中
// 现在要求你戳破所有的气球。戳破第 i 个气球
// 你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币
// 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号
// 如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球
// 求所能获得硬币的最大数量
// 测试链接 : https://leetcode.cn/problems/burst-balloons/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
int arr[MAXN];
int dp[MAXN][MAXN];

class Solution {
public:
    // 记忆化搜索
    int maxCoins1(vector<int>& nums) {
        int n = nums.size();
        // a b c d e
        // 1 a b c d e 1
        arr[0] = 1;
        arr[n + 1] = 1;
        for (int i = 0; i < n; i++) {
            arr[i + 1] = nums[i];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                dp[i][j] = -1;
            }
        }
        return f(1, n);
    }

    // arr[l...r]这些气球决定一个顺序，获得最大得分返回！
    // 一定有 : arr[l-1]一定没爆！
    // 一定有 : arr[r+1]一定没爆！
    // 尝试每个气球最后打爆
    int f(int l, int r) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans;
        if (l == r) {
            ans = arr[l - 1] * arr[l] * arr[r + 1];
        } else {
            // l   ....r
            // l +1 +2 .. r
            ans = max(
                arr[l - 1] * arr[l] * arr[r + 1] + f(l + 1, r), // l位置的气球最后打爆
                arr[l - 1] * arr[r] * arr[r + 1] + f(l, r - 1)); // r位置的气球最后打爆
            for (int k = l + 1; k < r; k++) {
                // k位置的气球最后打爆
                // l...k-1  k  k+1...r
                ans = max(ans, arr[l - 1] * arr[k] * arr[r + 1] + f(l, k - 1) + f(k + 1, r));
            }
        }
        dp[l][r] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划
    int maxCoins2(vector<int>& nums) {
        int n = nums.size();
        memset(dp, 0, sizeof(dp));
        arr[0] = 1;
        arr[n + 1] = 1;
        for (int i = 0; i < n; i++) {
            arr[i + 1] = nums[i];
        }
        for (int i = 1; i <= n; i++) {
            dp[i][i] = arr[i - 1] * arr[i] * arr[i + 1];
        }
        for (int l = n, ans; l >= 1; l--) {
            for (int r = l + 1; r <= n; r++) {
                ans = max(arr[l - 1] * arr[l] * arr[r + 1] + dp[l + 1][r],
                          arr[l - 1] * arr[r] * arr[r + 1] + dp[l][r - 1]);
                for (int k = l + 1; k < r; k++) {
                    ans = max(ans, arr[l - 1] * arr[k] * arr[r + 1] + dp[l][k - 1] + dp[k + 1][r]);
                }
                dp[l][r] = ans;
            }
        }
        return dp[1][n];
    }
};

int main() {
    Solution sol;
    cout << "=== 戳气球 ===" << endl;

    vector<int> nums1 = {3, 1, 5, 8};
    cout << "nums = [3, 1, 5, 8], 预期: 167" << endl;
    cout << "记忆化: " << sol.maxCoins1(nums1) << endl;
    cout << "动态规划: " << sol.maxCoins2(nums1) << endl;
    cout << endl;

    vector<int> nums2 = {1, 5};
    cout << "nums = [1, 5], 预期: 10" << endl;
    cout << "记忆化: " << sol.maxCoins1(nums2) << endl;
    cout << "动态规划: " << sol.maxCoins2(nums2) << endl;

    return 0;
}
