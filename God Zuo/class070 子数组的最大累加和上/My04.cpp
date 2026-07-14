// 环形数组中不能选相邻元素的最大累加和
// 给定一个数组nums，长度为n
// nums是一个环形数组，下标0和下标n-1是连在一起的
// 可以随意选择数字，但是不能选择相邻的数字
// 返回能得到的最大累加和
// 测试链接 : https://leetcode.cn/problems/house-robber-ii/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int best(vector<int> &nums, int l, int r)
    {
        if (l > r)
            return 0;
        if (l == r)
            return nums[l];
        if (l + 1 == r)
            return max(nums[l], nums[r]);
        int pre2 = nums[l];
        int pre1 = max(nums[l], nums[l + 1]);
        for (int i = l + 2, cur = 0; i <= r; ++i)
        {
            cur = max(pre1, max(nums[i], pre2 + nums[i]));
            pre2 = pre1;
            pre1 = cur;
        }
        return pre1;
    }

    int rob(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        return max(best(nums, 1, n - 1), best(nums, 2, n - 2) + nums[0]);
    }
};