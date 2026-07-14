// 乘积最大子数组
// 给你一个整数数组 nums
// 请你找出数组中乘积最大的非空连续子数组
// 并返回该子数组所对应的乘积
// 测试链接 : https://leetcode.cn/problems/maximum-product-subarray/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 用double防止中间结果溢出，思路不变
    int maxProduct(vector<int>& nums) {
        double ans = nums[0], minVal = nums[0], maxVal = nums[0], curmin, curmax;
        for (int i = 1; i < (int)nums.size(); i++) {
            curmin = min({(double)nums[i], minVal * nums[i], maxVal * nums[i]});
            curmax = max({(double)nums[i], minVal * nums[i], maxVal * nums[i]});
            minVal = curmin;
            maxVal = curmax;
            ans = max(ans, maxVal);
        }
        return (int)ans;
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<int> nums = {2, 3, -2, 4};
    cout << sol.maxProduct(nums) << endl;

    nums = {-2, 0, -1};
    cout << sol.maxProduct(nums) << endl;

    nums = {-2, 3, -4};
    cout << sol.maxProduct(nums) << endl;
    return 0;
}
