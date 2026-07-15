// 最长递增子序列和最长不下降子序列
// 给定一个整数数组nums
// 找到其中最长严格递增子序列长度、最长不下降子序列长度
// 测试链接 : https://leetcode.cn/problems/longest-increasing-subsequence/
// 核心: edp[i] = 长度为i+1的递增子序列的最小结尾, edp严格升序, 每步二分 >= num 最左
// 坑点: ① edp不能叫ends(std::ends冲突) ② edp最终状态不代表实际LIS ③ 不下降用 > 最左
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2505;

// edp[0...len-1]是有效区，有效区内的数字一定严格升序
int edp[MAXN];

class Solution {
public:
    // 普通动态规划 O(n²)
    int lengthOfLIS1(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    // >= num 的最左位置（严格递增用），不存在返回-1
    int bs1(int len, int num) {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r) {
            m = (l + r) / 2;
            if (edp[m] >= num) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }

    // > num 的最左位置（不下降用），不存在返回-1
    int bs2(int len, int num) {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r) {
            m = (l + r) / 2;
            if (edp[m] > num) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }

    // 最优解 O(n log n)，严格递增
    int lengthOfLIS2(vector<int>& nums) {
        int n = nums.size();
        int len = 0;
        for (int i = 0, find; i < n; i++) {
            find = bs1(len, nums[i]);
            if (find == -1) {
                edp[len++] = nums[i];
            } else {
                edp[find] = nums[i];
            }
        }
        return len;
    }

    // LeetCode 提交用
    int lengthOfLIS(vector<int>& nums) {
        return lengthOfLIS2(nums);
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "lengthOfLIS1: " << sol.lengthOfLIS1(nums) << endl;
    cout << "lengthOfLIS2: " << sol.lengthOfLIS2(nums) << endl;

    nums = {0, 1, 0, 3, 2, 3};
    cout << "lengthOfLIS1: " << sol.lengthOfLIS1(nums) << endl;
    cout << "lengthOfLIS2: " << sol.lengthOfLIS2(nums) << endl;

    nums = {7, 7, 7, 7};
    cout << "lengthOfLIS1: " << sol.lengthOfLIS1(nums) << endl;
    cout << "lengthOfLIS2: " << sol.lengthOfLIS2(nums) << endl;
    return 0;
}
