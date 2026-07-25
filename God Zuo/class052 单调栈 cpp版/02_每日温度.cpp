// 每日温度 — LeetCode 739
// 给定一个整数数组 temperatures，表示每天的温度
// 返回数组 answer，其中 answer[i] 是指对于第 i 天，
// 下一个更高温度出现在几天后。如果之后都没有更高的温度，answer[i] = 0

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int stk[MAXN];
int r;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        r = 0;

        for (int i = 0; i < n; i++) {
            // 当前温度 > 栈顶温度 → 弹出并记录答案
            while (r > 0 && temperatures[stk[r - 1]] < temperatures[i]) {
                int cur = stk[--r];
                ans[cur] = i - cur;
            }
            stk[r++] = i;
        }
        // 栈内剩余的元素自动保持为 0（ans 初始化时已为 0）
        return ans;
    }
};
