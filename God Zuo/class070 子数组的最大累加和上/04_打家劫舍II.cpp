// 环形数组中不能选相邻元素的最大累加和
// 给定一个数组nums，长度为n
// nums是一个环形数组，下标0和下标n-1是连在一起的
// 可以随意选择数字，但是不能选择相邻的数字
// 返回能得到的最大累加和
// 测试链接 : https://leetcode.cn/problems/house-robber-ii/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // nums[l....r]范围上，没有环形的概念
    // 返回 : 可以随意选择数字，但不能选择相邻数字的情况下，最大累加和
    int best(vector<int>& nums, int l, int r) {
        if (l > r) {
            return 0;
        }
        if (l == r) {
            return nums[l];
        }
        if (l + 1 == r) {
            return max(nums[l], nums[r]);
        }
        int prepre = nums[l];
        int pre = max(nums[l], nums[l + 1]);
        for (int i = l + 2, cur; i <= r; i++) {
            cur = max(pre, nums[i] + max(0, prepre));
            prepre = pre;
            pre = cur;
        }
        return pre;
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        return max(best(nums, 1, n - 1), nums[0] + best(nums, 2, n - 2));
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<int> nums = {2, 3, 2};
    cout << sol.rob(nums) << endl;

    nums = {1, 2, 3, 1};
    cout << sol.rob(nums) << endl;

    nums = {1, 2, 3};
    cout << sol.rob(nums) << endl;
    return 0;
}
