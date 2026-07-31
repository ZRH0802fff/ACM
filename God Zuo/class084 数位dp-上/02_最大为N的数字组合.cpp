// 最大为N的数字组合
// 给定一个按 非递减顺序 排列的数字数组 digits
// 已知digits一定不包含'0'，可能包含'1' ~ '9'，且无重复字符
// 你可以用任意次数 digits[i] 来写的数字
// 例如，如果 digits = ['1','3','5']
// 我们可以写数字，如 '13', '551', 和 '1351315'
// 返回 可以生成的小于或等于给定整数 n 的正整数的个数
// 测试链接 : https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 10;
int dig[MAXM];   // digits 的 int 版本
int m;            // digits 的长度
int cnt[12];      // cnt[i] : 已知前缀比num小，剩下i位没有确定，一共有多少种数字排列

// offset是辅助变量，完全由len决定，只是为了方便提取num中某一位数字，不是关键变量
// 还剩下len位没有决定
// 如果之前的位已经确定比num小，那么free == 1，表示接下的数字可以自由选择
// 如果之前的位和num一样，那么free == 0，表示接下的数字不能大于num当前位的数字
// 如果之前的位没有使用过数字，fix == 0
// 如果之前的位已经使用过数字，fix == 1
// 返回最终<=num的可能性有多少种
int f1(int num, int offset, int len, int free, int fix) {
    if (len == 0) {
        return fix == 1 ? 1 : 0;
    }
    int ans = 0;
    // num在当前位的数字
    int cur = (num / offset) % 10;
    if (fix == 0) {
        // 之前从来没有选择过数字
        // 当前依然可以不要任何数字，累加后续的可能性
        ans += f1(num, offset / 10, len - 1, 1, 0);
    }
    if (free == 0) {
        // 不能自由选择的情况
        for (int idx = 0; idx < m; idx++) {
            int i = dig[idx];
            if (i < cur) {
                ans += f1(num, offset / 10, len - 1, 1, 1);
            } else if (i == cur) {
                ans += f1(num, offset / 10, len - 1, 0, 1);
            } else {
                // i > cur
                break;
            }
        }
    } else {
        // 可以自由选择的情况
        ans += m * f1(num, offset / 10, len - 1, 1, 1);
    }
    return ans;
}

// offset是辅助变量，由len确定，方便提取num中某一位数字
// 还剩下len位没有决定，之前的位和num一样
// 返回最终<=num的可能性有多少种
int f2(int num, int offset, int len) {
    if (len == 0) {
        // num自己
        return 1;
    }
    // cur是num当前位的数字
    int cur = (num / offset) % 10;
    int ans = 0;
    for (int idx = 0; idx < m; idx++) {
        int i = dig[idx];
        if (i < cur) {
            ans += cnt[len - 1];
        } else if (i == cur) {
            ans += f2(num, offset / 10, len - 1);
        } else {
            break;
        }
    }
    return ans;
}

class Solution {
public:
    int atMostNGivenDigitSet1(vector<string>& strs, int num) {
        int tmp = num / 10;
        int len = 1;
        int offset = 1;
        while (tmp > 0) {
            tmp /= 10;
            len++;
            offset *= 10;
        }
        m = strs.size();
        for (int i = 0; i < m; i++) {
            dig[i] = stoi(strs[i]);
        }
        return f1(num, offset, len, 0, 0);
    }

    int atMostNGivenDigitSet2(vector<string>& strs, int num) {
        m = strs.size();
        for (int i = 0; i < m; i++) {
            dig[i] = stoi(strs[i]);
        }
        int len = 1;
        int offset = 1;
        int tmp = num / 10;
        while (tmp > 0) {
            tmp /= 10;
            len++;
            offset *= 10;
        }
        // cnt[i] : 已知前缀比num小，剩下i位没有确定，请问前缀确定的情况下，一共有多少种数字排列
        // cnt[0] = 1，表示后续已经没有了，前缀的状况都已确定，那么就是1种
        // cnt[1] = m
        // cnt[2] = m * m
        // cnt[3] = m * m * m
        // ...
        cnt[0] = 1;
        int ans = 0;
        for (int i = m, k = 1; k < len; k++, i *= m) {
            cnt[k] = i;
            ans += i;
        }
        return ans + f2(num, offset, len);
    }

    // LeetCode 提交用主方法
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        return atMostNGivenDigitSet2(digits, n);
    }
};

int main() {
    Solution sol;
    vector<string> d1 = {"1", "3", "5", "7"};
    cout << "digits=[1,3,5,7], n=100: " << sol.atMostNGivenDigitSet(d1, 100) << endl;
    cout << "  method1: " << sol.atMostNGivenDigitSet1(d1, 100) << endl;
    cout << "  method2: " << sol.atMostNGivenDigitSet2(d1, 100) << endl;

    vector<string> d2 = {"1", "4", "9"};
    cout << "digits=[1,4,9], n=1000000000: " << sol.atMostNGivenDigitSet(d2, 1000000000) << endl;

    vector<string> d3 = {"7"};
    cout << "digits=[7], n=8: " << sol.atMostNGivenDigitSet(d3, 8) << endl;

    return 0;
}
