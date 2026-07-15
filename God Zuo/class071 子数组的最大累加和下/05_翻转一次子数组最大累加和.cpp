// 可以翻转1次的情况下子数组最大累加和
// 给定一个数组nums，
// 现在允许你随意选择数组连续一段进行翻转，也就是子数组逆序的调整
// 比如翻转[1,2,3,4,5,6]的[2~4]范围，得到的是[1,2,5,4,3,6]
// 返回必须随意翻转1次之后，子数组的最大累加和
// 对数器验证
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

// start[i] : 所有必须以i开头的子数组中，最大累加和是多少
int start[MAXN];

// 返回子数组最大累加和
int maxSubSum(vector<int>& nums) {
    int n = nums.size();
    int ans = nums[0];
    for (int i = 1, pre = nums[0]; i < n; i++) {
        pre = max(nums[i], pre + nums[i]);
        ans = max(ans, pre);
    }
    return ans;
}

// 暴力方法
int maxSumReverse1(vector<int>& nums) {
    int ans = INT_MIN;
    for (int l = 0; l < (int)nums.size(); l++) {
        for (int r = l; r < (int)nums.size(); r++) {
            reverse(nums.begin() + l, nums.begin() + r + 1);
            ans = max(ans, maxSubSum(nums));
            reverse(nums.begin() + l, nums.begin() + r + 1);
        }
    }
    return ans;
}

// 正式方法
// 时间复杂度O(n)
int maxSumReverse2(vector<int>& nums) {
    int n = nums.size();
    start[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        start[i] = max(nums[i], nums[i] + start[i + 1]);
    }
    int ans = start[0];
    //end -> 子数组必须以i-1结尾，最大累加和
    int end = nums[0];
    int maxEnd = nums[0];
    for (int i = 1; i < n; i++) {
        ans = max(ans, maxEnd + start[i]);
        end = max(nums[i], end + nums[i]);
        maxEnd = max(maxEnd, end);
    }
    ans = max(ans, maxEnd);
    return ans;
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
    int v = 200;
    int testTime = 20000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int len = rand() % n + 1;
        vector<int> arr = randomArray(len, v);
        int ans1 = maxSumReverse1(arr);
        int ans2 = maxSumReverse2(arr);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
