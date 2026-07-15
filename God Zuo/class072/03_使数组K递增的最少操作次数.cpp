// 使数组K递增的最少操作次数
// 给你一个下标从0开始包含n个正整数的数组arr，和一个正整数k
// 如果对于每个满足 k <= i <= n-1 的下标 i
// 都有 arr[i-k] <= arr[i] ，那么称 arr 是K递增的
// 每一次操作中，你可以选择一个下标i并将arr[i]改成任意正整数
// 请你返回对于给定的 k ，使数组变成K递增的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-operations-to-make-the-array-k-increasing/
// 核心: 按i%k分成k组, 各组独立; 每组 len - 最长不下降长度 = 最少修改次数
// 坑点: 是不下降不是严格递增, 二分用 > num最左(bs2); 每组独立累加即可
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int nums[MAXN];
int edp[MAXN];

class Solution {
public:
    // > num 的最左位置（最长不下降子序列用）
    int bs(int len, int num) {
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

    // nums[0...size-1]中的最长不下降子序列长度
    int lengthOfNoDecreasing(int size) {
        int len = 0;
        for (int i = 0, find; i < size; i++) {
            find = bs(len, nums[i]);
            if (find == -1) {
                edp[len++] = nums[i];
            } else {
                edp[find] = nums[i];
            }
        }
        return len;
    }

    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size();
        int ans = 0;
        for (int i = 0, size; i < k; i++) {
            size = 0;
            // 把每一组的数字放入容器
            for (int j = i; j < n; j += k) {
                nums[size++] = arr[j];
            }
            // 当前组长度 - 最长不下降子序列长度 = 至少需要修改的个数
            ans += size - lengthOfNoDecreasing(size);
        }
        return ans;
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<int> arr = {5, 4, 3, 2, 1};
    int k = 1;
    cout << sol.kIncreasing(arr, k) << endl;

    arr = {4, 1, 5, 2, 6, 2};
    k = 2;
    cout << sol.kIncreasing(arr, k) << endl;

    arr = {4, 1, 5, 2, 6, 2};
    k = 3;
    cout << sol.kIncreasing(arr, k) << endl;
    return 0;
}
