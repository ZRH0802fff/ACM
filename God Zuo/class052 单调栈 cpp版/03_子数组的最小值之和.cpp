// 子数组的最小值之和 — LeetCode 907
// 给定一个整数数组 arr，找到所有子数组的最小值之和
// 由于答案可能很大，返回答案对 1000000007 取模的结果

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;
const int MOD = 1000000007;
int stk[MAXN];
int r;

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long ans = 0;
        r = 0;

        // 遍历阶段
        for (int i = 0; i < n; i++) {
            // >= ：保证一侧严格小于，另一侧小于等于，避免重复计算
            while (r > 0 && arr[stk[r - 1]] >= arr[i]) {
                int cur = stk[--r];
                int left = r > 0 ? stk[r - 1] : -1;
                // (cur - left) * (i - cur) 种组合，每个子数组最小值都是 arr[cur]
                ans = (ans + (long long)(cur - left) * (i - cur) * arr[cur]) % MOD;
            }
            stk[r++] = i;
        }

        // 清算阶段：右侧没有更小的值
        while (r > 0) {
            int cur = stk[--r];
            int left = r > 0 ? stk[r - 1] : -1;
            ans = (ans + (long long)(cur - left) * (n - cur) * arr[cur]) % MOD;
        }

        return (int)ans;
    }
};
