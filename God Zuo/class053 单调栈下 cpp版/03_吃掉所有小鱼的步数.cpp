// 吃掉所有小鱼需要的最少步数 — LeetCode 2289
// 给定一个数组 nums，每一步中，如果 nums[i] > nums[i+1]，则 nums[i+1] 被移除
// 返回需要多少步才能使数组变为非递减（即不再发生移除）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
// 用两个全局数组模拟栈：val 存值，turns 存轮数
int valStk[MAXN], turnsStk[MAXN];
int r;

class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        r = 0;

        // 倒序遍历：从右向左处理
        for (int i = n - 1; i >= 0; i--) {
            int curTurns = 0;
            // 当前鱼能吃掉比自己小的栈顶鱼
            while (r > 0 && valStk[r - 1] < nums[i]) {
                r--;
                curTurns++; // 每吃一条，基础轮数+1
                // 被吃的鱼花了 turnsStk[r] 轮才吃掉别人，自己必须等消化完
                if (turnsStk[r] > curTurns) curTurns = turnsStk[r];
            }
            valStk[r] = nums[i];
            turnsStk[r] = curTurns;
            r++;
            if (curTurns > ans) ans = curTurns;
        }
        return ans;
    }
};
