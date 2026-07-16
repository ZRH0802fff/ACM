// 找出数组的第K大和
// 给定一个数组nums和正数k
// 可以选择数组的任何子序列并对其元素求和
// 希望找到第k大的子序列和，子序列和允许出现重复
// 空子序列的和视作0，数组中的值可正、可负、可0
// 测试链接 : https://leetcode.cn/problems/find-the-k-sum-of-an-array/
// 核心: 第k大和 = 所有正数和(sum) - 绝对值数组的第k小子序列和
//       转化后nums全变正数, 排序, 堆存(累加和,下标), 每次弹出扩展两个
// 坑点: ①空集是第1小(不是第0) ②弹出k-1次后堆顶就是第k小 ③sum用long long防溢出
//
// 转化逻辑如下:
// 1. 先把所有正数加起来，得到sum，这是nums第1大子序列和
// 2. nums第2大子序列和 = max(sum-最小的正数, sum+(选剩下非正数拼出最大的累加和))
// 3. nums第2大子序列和 = (sum - 最小的正数) 或 (sum - 选剩下的非正数字拼出最小的绝对值)
// 4. 原始数组记为nums，把每个数转成绝对值的数组记为a
// 5. nums第1大子序列和 = sum = sum - 0，其中0是a取空集的累加和，认为是a的第1小子序列和
// 6. nums第1大子序列和 = sum - a的第1小子序列和
// 7. nums第2大子序列和 = sum - a的第2小子序列和
// 8. nums第k大子序列和 = sum - a的第k小子序列和
// 9. 求a的第k小子序列和即可，注意，a的第1小子序列和，是空集的情况
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        int n = nums.size();
        long long sum = 0;
        // 所有正数求和，负数取绝对值
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                sum += nums[i];
            } else {
                nums[i] = -nums[i];
            }
        }
        sort(nums.begin(), nums.end());
        // 小根堆: (累加和, 最右下标)，空集(-1,0)是a的第1小子序列和
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;
        heap.push({0, -1});
        // 弹出前k-1小，堆顶就是第k小
        for (int i = 1; i < k; i++) {
            auto top = heap.top(); heap.pop();
            long long val = top.first;
            int idx = top.second;
            if (idx + 1 < n) {
                // 新增末尾：val + nums[idx+1]
                heap.push({val + nums[idx + 1], idx + 1});
                if (idx >= 0) {
                    // 替换末尾：val - nums[idx] + nums[idx+1]
                    heap.push({val - nums[idx] + nums[idx + 1], idx + 1});
                }
            }
        }
        // sum - a的第k小子序列和
        return sum - heap.top().first;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 4, -2};
    int k = 5;
    cout << sol.kSum(nums, k) << endl;

    nums = {1, -2, 3, 4, -10, 12};
    k = 16;
    cout << sol.kSum(nums, k) << endl;
    return 0;
}
