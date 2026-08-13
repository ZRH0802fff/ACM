// 范围内的数字计数
// 给定两个正整数a和b，求在[a,b]范围上的所有整数中
// 1 <= a, b
// 某个数码d出现了多少次
// 测试链接 : https://leetcode.cn/problems/digit-count-in-range/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int digitsCount(int d, int a, int b) {
        return count(b, d) - count(a - 1, d);
    }

private:
    // 统计1~num范围上所有的数中，数码d出现了多少次
    // 注意是1~num范围，不是0~num范围
    int count(int num, int d) {
        int ans = 0;
        // left : 当前位左边的情况数
        // right : 当前位右边的情况数
        // 当前位的数字是cur
        for (int right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
            // 情况1：
            // d != 0
            // 1 ~ 30583 , d = 5
            // cur < d的情况
            // 个位cur=3 : 0000~3057 5
            // 个位上没有额外加
            //
            // cur > d的情况
            // 十位cur=8 : 000~304 5 0~9
            // 十位上额外加 : 305 5 0~9
            //
            // cur == d的情况
            // 百位cur=5 : 00~29 5 00~99
            // 百位上额外加 : 30 5 00~83
            // ...
            // 情况2：
            // d == 0
            // 1 ~ 30583 d = 0
            // cur > d的情况
            // 个位cur=3 : 0001~3057 0
            // 个位上额外加 : 3058 0
            //
            // cur > d的情况
            // 十位cur=8 : 001~304 0 0~9
            // 十位上额外加 : 305 0 0~9
            //
            // cur > d的情况
            // 百位cur=5 : 01~29 0 00~99
            // 百位上额外加 : 30 0 00~99
            //
            // cur == d的情况
            // 千位cur=0 : 1~2 0 000~099
            // 千位上额外加 : 3 0 000~583
            left = tmp / 10;
            cur = tmp % 10;
            if (d == 0) {
                left--;
            }
            ans += left * right;
            if (cur > d) {
                ans += right;
            } else if (cur == d) {
                ans += num % right + 1;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    cout << "d=1, a=1, b=13: " << sol.digitsCount(1, 1, 13) << " (expected 6)" << endl;
    cout << "d=3, a=1, b=45: " << sol.digitsCount(3, 1, 45) << " (expected 11)" << endl;
    return 0;
}
