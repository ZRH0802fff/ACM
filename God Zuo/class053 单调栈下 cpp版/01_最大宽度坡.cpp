// 最大宽度坡 — LeetCode 962
// nums 中，i < j 且 nums[i] <= nums[j]，求最大的 j - i

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
int stk[MAXN];
int r;

class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        r = 0;
        stk[r++] = 0;

        // 1. 从左往右，建立严格单调递减栈
        for (int i = 1; i < n; i++) {
            if (nums[stk[r - 1]] > nums[i]) {
                stk[r++] = i;
            }
        }

        // 2. 从右往左，寻找最大宽度坡
        int ans = 0;
        for (int j = n - 1; j >= 0; j--) {
            while (r > 0 && nums[stk[r - 1]] <= nums[j]) {
                int i = stk[--r];
                int width = j - i;
                if (width > ans) ans = width;
            }
        }
        return ans;
    }
};
