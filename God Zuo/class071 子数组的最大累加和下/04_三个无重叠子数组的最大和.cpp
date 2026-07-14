// 三个无重叠子数组的最大和
// 给你一个整数数组 nums 和一个整数 k
// 找出三个长度为 k 、互不重叠、且全部数字和（3 * k 项）最大的子数组
// 并返回这三个子数组
// 以下标的数组形式返回结果，数组中的每一项分别指示每个子数组的起始位置
// 如果有多个结果，返回字典序最小的一个
// 测试链接 : https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

// sums[i] : 以i开头并且长度为k的子数组的累加和
int sums[MAXN];
// prefix[i] : 0~i范围上所有长度为k的子数组中，拥有最大累加和的子数组的开头
int prefix[MAXN];
// suffix[i] : i~n-1范围上所有长度为k的子数组中，拥有最大累加和的子数组的开头
int suffix[MAXN];

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        // 计算sums
        for (int l = 0, r = 0, sum = 0; r < n; r++) {
            sum += nums[r];
            if (r - l + 1 == k) {
                sums[l] = sum;
                sum -= nums[l];
                l++;
            }
        }
        // 计算prefix
        for (int l = 1, r = k; r < n; l++, r++) {
            if (sums[l] > sums[prefix[r - 1]]) {
                prefix[r] = l;
            } else {
                prefix[r] = prefix[r - 1];
            }
        }
        // 计算suffix
        suffix[n - k] = n - k;
        for (int l = n - k - 1; l >= 0; l--) {
            if (sums[l] >= sums[suffix[l + 1]]) {
                suffix[l] = l;
            } else {
                suffix[l] = suffix[l + 1];
            }
        }
        int a = 0, b = 0, c = 0, maxSum = 0;
        for (int p, s, i = k, j = 2 * k - 1, sum; j < n - k; i++, j++) {
            p = prefix[i - 1];
            s = suffix[j + 1];
            sum = sums[p] + sums[i] + sums[s];
            if (sum > maxSum) {
                maxSum = sum;
                a = p;
                b = i;
                c = s;
            }
        }
        return {a, b, c};
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<int> nums = {1, 2, 1, 2, 6, 7, 5, 1};
    int k = 2;
    vector<int> res = sol.maxSumOfThreeSubarrays(nums, k);
    cout << "[" << res[0] << ", " << res[1] << ", " << res[2] << "]" << endl;

    nums = {1, 2, 1, 2, 1, 2, 1, 2, 1};
    k = 2;
    res = sol.maxSumOfThreeSubarrays(nums, k);
    cout << "[" << res[0] << ", " << res[1] << ", " << res[2] << "]" << endl;
    return 0;
}
