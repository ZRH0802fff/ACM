// 最长数对链
// 给你一个由n个数对组成的数对数组pairs
// 其中 pairs[i] = [lefti, righti] 且 lefti < righti
// 现在，我们定义一种 跟随 关系，当且仅当 b < c 时
// 数对 p2 = [c, d] 才可以跟在 p1 = [a, b] 后面
// 我们用这种形式来构造 数对链
// 找出并返回能够形成的最长数对链的长度
// 测试链接 : https://leetcode.cn/problems/maximum-length-of-pair-chain/
// 核心: 法1=按开头排序+LIS分离技巧(查开头>=最左, 入结尾, 更小才更新); 法2=按结尾排序贪心
// 坑点: LIS法中 edp[find]=min(edp[find], pair[1]) 必须取min而非直接覆盖
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int edp[MAXN];

class Solution {
public:
    // >= num 的最左位置
    int bs(int len, int num) {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r) {
            m = (l + r) / 2;
            if (edp[m] >= num) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }

    // 方法1 : 排序开头 + edp数组
    int findLongestChain1(vector<vector<int>>& pairs) {
        int n = pairs.size();
        // 数对根据开始位置排序，从小到大
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        int len = 0;
        for (const auto& p : pairs) {
            int find = bs(len, p[0]);
            if (find == -1) {
                edp[len++] = p[1];
            } else {
                edp[find] = min(edp[find], p[1]);
            }
        }
        return len;
    }

    // 方法2 : 贪心，按照结尾排序
    int findLongestChain2(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int pre = INT_MIN, ans = 0;
        for (const auto& p : pairs) {
            if (pre < p[0]) {
                pre = p[1];
                ans++;
            }
        }
        return ans;
    }

    // LeetCode 提交用（贪心）
    int findLongestChain(vector<vector<int>>& pairs) {
        return findLongestChain2(pairs);
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<vector<int>> pairs = {{1, 2}, {2, 3}, {3, 4}};
    cout << "findLongestChain1: " << sol.findLongestChain1(pairs) << endl;
    cout << "findLongestChain2: " << sol.findLongestChain2(pairs) << endl;

    pairs = {{1, 2}, {7, 8}, {4, 5}};
    cout << "findLongestChain1: " << sol.findLongestChain1(pairs) << endl;
    cout << "findLongestChain2: " << sol.findLongestChain2(pairs) << endl;
    return 0;
}
