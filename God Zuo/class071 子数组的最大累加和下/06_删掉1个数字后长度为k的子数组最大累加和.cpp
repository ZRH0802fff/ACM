// 删掉1个数字后长度为k的子数组最大累加和
// 给定一个数组nums，求必须删除一个数字后的新数组中
// 长度为k的子数组最大累加和，删除哪个数字随意
// 对数器验证
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

// 单调队列 : 维持窗口内最小值的更新结构
int window[MAXN];

// 暴力方法
vector<int> deleteIdx(vector<int>& nums, int index) {
    int len = nums.size() - 1;
    vector<int> ans(len);
    int i = 0;
    for (int j = 0; j < (int)nums.size(); j++) {
        if (j != index) {
            ans[i++] = nums[j];
        }
    }
    return ans;
}

// 长度为k的子数组最大累加和
int lenKmaxSum(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = INT_MIN;
    for (int i = 0; i <= n - k; i++) {
        int cur = 0;
        for (int j = i, cnt = 0; cnt < k; j++, cnt++) {
            cur += nums[j];
        }
        ans = max(ans, cur);
    }
    return ans;
}

// 暴力方法
int maxSum1(vector<int>& nums, int k) {
    int n = nums.size();
    if (n <= k) {
        return 0;
    }
    int ans = INT_MIN;
    for (int i = 0; i < n; i++) {
        vector<int> rest = deleteIdx(nums, i);
        ans = max(ans, lenKmaxSum(rest, k));
    }
    return ans;
}

// 正式方法
// 时间复杂度O(N)，单调队列维护窗口内最小值
int maxSum2(vector<int>& nums, int k) {
    int n = nums.size();
    if (n <= k) {
        return 0;
    }
    int l = 0, r = 0;
    long long sum = 0;
    int ans = INT_MIN;
    for (int i = 0; i < n; i++) {
        while (l < r && nums[window[r - 1]] >= nums[i]) {
            r--;
        }
        window[r++] = i;
        sum += nums[i];
        if (i >= k) {
            ans = max(ans, (int)(sum - nums[window[l]]));
            if (window[l] == i - k) {
                l++;
            }
            sum -= nums[i - k];
        }
    }
    return ans;
}

// 生成随机数组
vector<int> randomArray(int n, int v) {
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = rand() % (2 * v + 1) - v;
    }
    return ans;
}

// 对数器
int main() {
    srand(time(0));
    int n = 200;
    int v = 1000;
    int testTimes = 10000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++) {
        int len = rand() % n + 1;
        vector<int> nums = randomArray(len, v);
        int k = rand() % n + 1;
        int ans1 = maxSum1(nums, k);
        int ans2 = maxSum2(nums, k);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
