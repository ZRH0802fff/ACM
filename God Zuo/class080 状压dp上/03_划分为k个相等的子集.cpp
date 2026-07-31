// 划分为k个相等的子集
// 给定一个整数数组  nums 和一个正整数 k，
// 找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
// 测试链接 : https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1 << 17;
int dp[MAXN];

class Solution {
public:
    // 状压dp的解法
    // 这是最正式的解
    bool canPartitionKSubsets1(vector<int>& nums, int k) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum % k != 0) {
            return false;
        }
        int n = nums.size();
        memset(dp, 0, sizeof(dp));
        return f1(nums, sum / k, (1 << n) - 1, 0, k);
    }

    // 就是题目2的递归函数
    // limit : 每条边规定的长度
    // status : 表示哪些数字还可以选
    // cur : 当前要解决的这条边已经形成的长度
    // rest : 一共还有几条边没有解决
    bool f1(vector<int>& nums, int limit, int status, int cur, int rest) {
        if (rest == 0) {
            return status == 0;
        }
        if (dp[status] != 0) {
            return dp[status] == 1;
        }
        bool ans = false;
        for (int i = 0; i < (int)nums.size(); i++) {
            if ((status & (1 << i)) != 0 && cur + nums[i] <= limit) {
                if (cur + nums[i] == limit) {
                    ans = f1(nums, limit, status ^ (1 << i), 0, rest - 1);
                } else {
                    ans = f1(nums, limit, status ^ (1 << i), cur + nums[i], rest);
                }
                if (ans) {
                    break;
                }
            }
        }
        dp[status] = ans ? 1 : -1;
        return ans;
    }

    // 纯暴力的递归（不做任何动态规划），利用良好的剪枝策略，可以做到非常好的效率
    // 但这并不是正式的解，如果数据设计的很苛刻，是通过不了的
    bool canPartitionKSubsets2(vector<int>& nums, int k) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum % k != 0) {
            return false;
        }
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> group(k, 0);
        return f2(group, sum / k, nums, n - 1);
    }

    // group里面是各个集合已经有的累加和
    // 随着递归的展开，group里的累加和会变化
    // 所以这是一个带路径的递归，而且路径信息比较复杂(group数组)
    // 无法改成动态规划，但是利用剪枝策略可以通过
    // group[0....index]这些数字，填入每个集合，一定要都使用
    // 每个集合的累加和一定都要是target，返回能不能做到
    bool f2(vector<int>& group, int target, vector<int>& nums, int index) {
        if (index < 0) {
            return true;
        }
        int num = nums[index];
        int len = group.size();
        for (int i = 0; i < len; i++) {
            if (group[i] + num <= target) {
                // 当前数字num放进i号集合
                group[i] += num;
                if (f2(group, target, nums, index - 1)) {
                    return true;
                }
                // 递归完成后将路径还原
                group[i] -= num;
                while (i + 1 < (int)group.size() && group[i] == group[i + 1]) {
                    i++;
                }
            }
        }
        return false;
    }
};
