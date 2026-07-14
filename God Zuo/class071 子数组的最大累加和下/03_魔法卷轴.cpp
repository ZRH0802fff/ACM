// 魔法卷轴
// 给定一个数组nums，其中可能有正、负、0
// 每个魔法卷轴可以把nums中连续的一段全变成0
// 你希望数组整体的累加和尽可能大
// 卷轴使不使用、使用多少随意，但一共只有2个魔法卷轴
// 请返回数组尽可能大的累加和
// 对数器验证
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

// prefix[i] : 0~i范围上一定要用1次卷轴的情况下，0~i范围上整体最大累加和多少
int pdp[MAXN];
// suffix[i] : i~n-1范围上一定要用1次卷轴的情况下，i~n-1范围上整体最大累加和多少
int sdp[MAXN];

// 暴力方法
int mustOneScroll(vector<int>& nums, int l, int r) {
    int ans = INT_MIN;
    for (int a = l; a <= r; a++) {
        for (int b = a; b <= r; b++) {
            int curAns = 0;
            for (int i = l; i < a; i++) {
                curAns += nums[i];
            }
            for (int i = b + 1; i <= r; i++) {
                curAns += nums[i];
            }
            ans = max(ans, curAns);
        }
    }
    return ans;
}

int maxSum1(vector<int>& nums) {
    int p1 = 0;
    for (int num : nums) {
        p1 += num;
    }
    int n = nums.size();
    int p2 = mustOneScroll(nums, 0, n - 1);
    int p3 = INT_MIN;
    for (int i = 1; i < n; i++) {
        p3 = max(p3, mustOneScroll(nums, 0, i - 1) + mustOneScroll(nums, i, n - 1));
    }
    return max(p1, max(p2, p3));
}

// 正式方法
// 时间复杂度O(n)
int maxSum2(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
        return 0;
    }
    // 情况1 : 完全不使用卷轴
    int p1 = 0;
    for (int num : nums) {
        p1 += num;
    }
    // 计算prefix
    int sum = nums[0];
    int maxPresum = max(0, nums[0]);
    for (int i = 1; i < n; i++) {
        pdp[i] = max(pdp[i - 1] + nums[i], maxPresum);
        sum += nums[i];
        maxPresum = max(maxPresum, sum);
    }
    // 情况二 : 必须用1次卷轴
    int p2 = pdp[n - 1];
    // 计算suffix
    sdp[n - 1] = 0;
    sum = nums[n - 1];
    maxPresum = max(0, sum);
    for (int i = n - 2; i >= 0; i--) {
        sdp[i] = max(nums[i] + sdp[i + 1], maxPresum);
        sum += nums[i];
        maxPresum = max(maxPresum, sum);
    }
    // 情况三 : 必须用2次卷轴
    int p3 = INT_MIN;
    for (int i = 1; i < n; i++) {
        p3 = max(p3, pdp[i - 1] + sdp[i]);
    }
    return max(p1, max(p2, p3));
}

// 生成随机数组
vector<int> randomArray(int n, int v) {
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = rand() % (v * 2 + 1) - v;
    }
    return ans;
}

// 对数器
int main() {
    srand(time(0));
    int n = 50;
    int v = 100;
    int testTime = 10000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int len = rand() % n;
        vector<int> nums = randomArray(len, v);
        int ans1 = maxSum1(nums);
        int ans2 = maxSum2(nums);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
