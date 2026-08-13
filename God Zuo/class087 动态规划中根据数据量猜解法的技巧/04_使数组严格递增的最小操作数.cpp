// 使数组严格递增的最小操作数
// 给你两个整数数组 arr1 和 arr2
// 返回使 arr1 严格递增所需要的最小操作数（可能为0）
// 每一步操作中，你可以分别从 arr1 和 arr2 中各选出一个索引
// 分别为 i 和 j，0 <= i < arr1.length 和 0 <= j < arr2.length
// 然后进行赋值运算 arr1[i] = arr2[j]
// 如果无法让 arr1 严格递增，请返回-1
// 1 <= arr1.length, arr2.length <= 2000
// 0 <= arr1[i], arr2[i] <= 10^9
// 测试链接 : https://leetcode.cn/problems/make-array-strictly-increasing/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2001; // arr1.length <= 2000
int dp[MAXN];

// arr2[0..size-1]范围上是严格递增的
// 找到这个范围上>num的最左位置
// 不存在返回-1
int bs(vector<int>& arr2, int size, int num) {
    int l = 0, r = size - 1, m;
    int ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (arr2[m] > num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

// arr1长度为n，arr2有效部分长度为m
// arr2有效部分可以替换arr1中的数字
// arr1[0..i-1]已经严格递增且arr1[i-1]一定没有替换
// 返回让arr1整体都严格递增，arr1[i...]范围上还需要几次替换
// 如果做不到，返回无穷大
int f1(vector<int>& arr1, vector<int>& arr2, int n, int m, int i) {
    if (i == n) {
        return 0;
    }
    if (dp[i] != -1) {
        return dp[i];
    }
    // ans : 遍历所有的分支，所得到的最少的操作次数
    int ans = INT_MAX;
    // pre : 前一位的数字
    int pre = i == 0 ? INT_MIN : arr1[i - 1];
    // find : arr2有效长度m的范围上，找到刚比pre大的位置
    int find = bs(arr2, m, pre);
    // 枚举arr1[i...]范围上，第一个不需要替换的位置j
    for (int j = i, k = 0, next; j <= n; j++, k++) {
        if (j == n) {
            ans = min(ans, k);
        } else {
            // pre : 被arr2替换的前一位数字
            if (pre < arr1[j]) {
                next = f1(arr1, arr2, n, m, j + 1);
                if (next != INT_MAX) {
                    ans = min(ans, k + next);
                }
            }
            if (find != -1 && find < m) {
                pre = arr2[find++];
            } else {
                break;
            }
        }
    }
    dp[i] = ans;
    return ans;
}

class Solution {
public:
    // 记忆化搜索
    int makeArrayIncreasing1(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        int m = 1;
        for (int i = 1; i < (int)arr2.size(); i++) {
            if (arr2[i] != arr2[m - 1]) {
                arr2[m++] = arr2[i];
            }
        }
        int n = arr1.size();
        memset(dp, -1, sizeof(dp));
        int ans = f1(arr1, arr2, n, m, 0);
        return ans == INT_MAX ? -1 : ans;
    }

    // 严格位置依赖的动态规划
    // 和方法1的思路没有区别
    // 甚至填写dp表的逻辑都保持一致
    int makeArrayIncreasing2(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        int m = 1;
        for (int i = 1; i < (int)arr2.size(); i++) {
            if (arr2[i] != arr2[m - 1]) {
                arr2[m++] = arr2[i];
            }
        }
        int n = arr1.size();
        dp[n] = 0;
        for (int i = n - 1, ans, pre, find; i >= 0; i--) {
            ans = INT_MAX;
            pre = i == 0 ? INT_MIN : arr1[i - 1];
            find = bs(arr2, m, pre);
            for (int j = i, k = 0, next; j <= n; j++, k++) {
                if (j == n) {
                    ans = min(ans, k);
                } else {
                    if (pre < arr1[j]) {
                        next = dp[j + 1];
                        if (next != INT_MAX) {
                            ans = min(ans, k + next);
                        }
                    }
                    if (find != -1 && find < m) {
                        pre = arr2[find++];
                    } else {
                        break;
                    }
                }
            }
            dp[i] = ans;
        }
        return dp[0] == INT_MAX ? -1 : dp[0];
    }

    // LeetCode 提交用主方法
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        return makeArrayIncreasing2(arr1, arr2);
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 5, 3, 6, 7};
    vector<int> arr2 = {1, 3, 2, 4};
    cout << sol.makeArrayIncreasing(arr1, arr2) << " (expected 1)" << "\n";
    vector<int> arr1b = {1, 5, 3, 6, 7};
    vector<int> arr2b = {4, 3, 1};
    cout << sol.makeArrayIncreasing(arr1b, arr2b) << " (expected 2)" << "\n";
    return 0;
}
