// 打家劫舍 IV
// 沿街有一排连续的房屋。每间房屋内都藏有一定的现金
// 现在有一位小偷计划从这些房屋中窃取现金
// 由于相邻的房屋装有相互连通的防盗系统，所以小偷不会窃取相邻的房屋
// 小偷的 窃取能力 定义为他在窃取过程中能从单间房屋中窃取的 最大金额
// 给你一个整数数组 nums 表示每间房屋存放的现金金额
// 另给你一个整数k，表示小偷需要窃取至少 k 间房屋
// 返回小偷需要的最小窃取能力值
// 测试链接 : https://leetcode.cn/problems/house-robber-iv/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 贪心：能力为ability时，最多能偷多少间（不能相邻）
    int mostRob(vector<int>& nums, int n, int ability) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] <= ability) {
                ans++;
                i++; // 跳过相邻
            }
        }
        return ans;
    }

    int minCapability(vector<int>& nums, int k) {
        int n = nums.size();
        int l = nums[0], r = nums[0];
        for (int i = 1; i < n; i++) {
            l = min(l, nums[i]);
            r = max(r, nums[i]);
        }
        int m, ans = 0;
        while (l <= r) {
            m = (l + r) / 2;
            if (mostRob(nums, n, m) >= k) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<int> nums = {2, 3, 5, 9};
    int k = 2;
    cout << sol.minCapability(nums, k) << endl;

    nums = {2, 7, 9, 3, 1};
    k = 2;
    cout << sol.minCapability(nums, k) << endl;
    return 0;
}
