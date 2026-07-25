// 和至少为K的最短子数组 — LeetCode 862
// 前缀和 + 单调队列（递增）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
long long pref[MAXN];
int q[MAXN];
int h, t;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + nums[i];

        h = t = 0;
        int ans = INT_MAX;

        for (int i = 0; i <= n; i++) {
            // 队头结算：当前前缀和 - 队头前缀和 >= k
            while (h < t && pref[i] - pref[q[h]] >= k) {
                int len = i - q[h];
                if (len < ans) ans = len;
                h++; // 队头弹出，因为后续就算满足也更长
            }
            // 队尾维护单调递增：队尾 >= 当前，队尾出队
            while (h < t && pref[q[t - 1]] >= pref[i]) t--;
            q[t++] = i;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
