// 非负数组前k个最小的子序列累加和
// 给定一个数组nums，含有n个数字，都是非负数
// 给定一个正数k，返回所有子序列中累加和最小的前k个累加和
// 子序列是包含空集的
// 1 <= n <= 10^5, 1 <= nums[i] <= 10^6, 1 <= k <= 10^5
// 注意这个数据量，用01背包的解法是不行的，时间复杂度太高了
// 对数器验证
// 核心: 排序后用小根堆维护(最右下标,累加和), 每次弹出后扩展两个: 替换末尾/新增末尾
// 坑点: ①数组必须先排序 ②堆中比较的是累加和 ③空集累加和0是第1小(ans[0])
#include <bits/stdc++.h>
using namespace std;

// 暴力方法
void f1(vector<int>& nums, int idx, int sum, vector<int>& ans) {
    if (idx == (int)nums.size()) {
        ans.push_back(sum);
    } else {
        f1(nums, idx + 1, sum, ans);
        f1(nums, idx + 1, sum + nums[idx], ans);
    }
}

vector<int> topKSum1(vector<int>& nums, int k) {
    vector<int> all;
    f1(nums, 0, 0, all);
    sort(all.begin(), all.end());
    return vector<int>(all.begin(), all.begin() + k);
}

// 01背包实现（不是最优，数据量大时不可用）
vector<int> topKSum2(vector<int>& nums, int k) {
    int sum = 0;
    for (int num : nums) sum += num;
    vector<int> dp(sum + 1, 0);
    dp[0] = 1;
    for (int num : nums) {
        for (int j = sum; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }
    vector<int> ans(k);
    int idx = 0;
    for (int j = 0; j <= sum && idx < k; j++) {
        for (int i = 0; i < dp[j] && idx < k; i++) {
            ans[idx++] = j;
        }
    }
    return ans;
}

// 正式方法：堆 O(n log n + k log k)
vector<int> topKSum3(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    // 小根堆: (累加和, 最右下标) — sum在前保证按sum排序
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;
    // ans[0] = 0（空集），堆里放以0号元素为结尾的
    vector<int> ans(k, 0);
    if (k == 1) return ans;
    heap.push({nums[0], 0});
    for (int i = 1; i < k; i++) {
        auto top = heap.top(); heap.pop();
        long long sum = top.first;
        int right = top.second;
        ans[i] = sum;
        if (right + 1 < (int)nums.size()) {
            // 替换末尾：去掉nums[right]，加上nums[right+1]
            heap.push({sum - nums[right] + nums[right + 1], right + 1});
            // 新增末尾：直接加上nums[right+1]
            heap.push({sum + nums[right + 1], right + 1});
        }
    }
    return ans;
}

vector<int> randomArray(int len, int val) {
    vector<int> ans(len);
    for (int i = 0; i < len; i++)
        ans[i] = rand() % val;
    return ans;
}

bool equals(vector<int>& a, vector<int>& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] != b[i]) return false;
    return true;
}

int main() {
    srand(time(0));
    int n = 15, v = 40, testTime = 5000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int len = rand() % n + 1;
        vector<int> nums = randomArray(len, v);
        int total = 1 << len;
        int k = rand() % (total - 1) + 1;
        vector<int> ans1 = topKSum1(nums, k);
        vector<int> ans2 = topKSum3(nums, k);
        if (!equals(ans1, ans2)) {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
