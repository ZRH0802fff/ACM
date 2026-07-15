// 俄罗斯套娃信封问题
// 给你一个二维整数数组envelopes ，其中envelopes[i]=[wi, hi]
// 表示第 i 个信封的宽度和高度
// 当另一个信封的宽度和高度都比这个信封大的时候
// 这个信封就可以放进另一个信封里，如同俄罗斯套娃一样
// 请计算 最多能有多少个信封能组成一组"俄罗斯套娃"信封
// 即可以把一个信封放到另一个信封里面，注意不允许旋转信封
// 测试链接 : https://leetcode.cn/problems/russian-doll-envelopes/
// 核心: 宽度升序+同宽高度降序排序, 然后对高度求LIS; 降序避免同宽信封被误套
// 坑点: 排序lambda中 a[0]==b[0] 必须高度降序, 否则同宽(2,4)(2,9)会错误形成长度2
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

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

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        // 排序策略: 宽度从小到大，宽度一样高度从大到小
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
        });
        int len = 0;
        for (int i = 0, find; i < n; i++) {
            find = bs(len, envelopes[i][1]);
            if (find == -1) {
                edp[len++] = envelopes[i][1];
            } else {
                edp[find] = envelopes[i][1];
            }
        }
        return len;
    }
};

// 测试代码
int main() {
    Solution sol;
    vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    cout << sol.maxEnvelopes(envelopes) << endl;

    envelopes = {{1, 1}, {1, 1}, {1, 1}};
    cout << sol.maxEnvelopes(envelopes) << endl;
    return 0;
}
