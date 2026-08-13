// 最接近目标值的子序列和
// 给你一个整数数组 nums 和一个目标值 goal
// 你需要从 nums 中选出一个子序列，使子序列元素总和最接近 goal
// 也就是说，如果子序列元素和为 sum ，你需要 最小化绝对差 abs(sum - goal)
// 返回 abs(sum - goal) 可能的 最小值
// 注意，数组的子序列是通过移除原始数组中的某些元素（可能全部或无）而形成的数组。
// 数据量描述:
// 1 <= nums.length <= 40
// -10^7 <= nums[i] <= 10^7
// -10^9 <= goal <= 10^9
// 测试链接 : https://leetcode.cn/problems/closest-subsequence-sum/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1 << 20;

int lsum[MAXN];
int rsum[MAXN];
int fill_;

void collect(int nums[], int i, int e, int s, int sum[]) {
    if (i == e) {
        sum[fill_++] = s;
    } else {
        // nums[i.....]这一组，相同的数字有几个
        int j = i + 1;
        while (j < e && nums[j] == nums[i]) {
            j++;
        }
        // nums[ 1 1 1 1 1 2....
        //       i         j
        for (int k = 0; k <= j - i; k++) {
            // k = 0个
            // k = 1个
            // k = 2个
            collect(nums, j, e, s + k * nums[i], sum);
        }
    }
}

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        long long minSum = 0;
        long long maxSum = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0) {
                maxSum += nums[i];
            } else {
                minSum += nums[i];
            }
        }
        if (maxSum < goal) {
            return (int)abs(maxSum - goal);
        }
        if (minSum > goal) {
            return (int)abs(minSum - goal);
        }
        // 原始数组排序，为了后面递归的时候，还能剪枝
        // 常数优化
        sort(nums.begin(), nums.end());
        // 转为int数组
        static int arr[40];
        for (int i = 0; i < n; i++) {
            arr[i] = nums[i];
        }
        fill_ = 0;
        collect(arr, 0, n >> 1, 0, lsum);
        int lsize = fill_;
        fill_ = 0;
        collect(arr, n >> 1, n, 0, rsum);
        int rsize = fill_;
        sort(lsum, lsum + lsize);
        sort(rsum, rsum + rsize);
        int ans = abs(goal);
        for (int i = 0, j = rsize - 1; i < lsize; i++) {
            while (j > 0 && abs(goal - lsum[i] - rsum[j - 1]) <= abs(goal - lsum[i] - rsum[j])) {
                j--;
            }
            ans = min(ans, abs(goal - lsum[i] - rsum[j]));
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {5,-7,3,5};
    cout << sol.minAbsDifference(nums1, 6) << " (expected: 0)" << endl;
    vector<int> nums2 = {7,-9,15,-2,5};
    cout << sol.minAbsDifference(nums2, 5) << " (expected: 0)" << endl;
    vector<int> nums3 = {1,2,3};
    cout << sol.minAbsDifference(nums3, -7) << " (expected: 7)" << endl;
    return 0;
}
