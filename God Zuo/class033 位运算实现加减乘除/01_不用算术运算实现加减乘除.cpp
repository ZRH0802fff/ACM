// 不用任何算术运算，只用位运算实现加减乘除
// 代码实现中你找不到任何一个算术运算符
// 测试链接 : https://leetcode.cn/problems/divide-two-integers/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int divide(int a, int b) {
        if (a == INT_MIN && b == INT_MIN) {
            // a和b都是整数最小
            return 1;
        }
        if (a != INT_MIN && b != INT_MIN) {
            // a和b都不是整数最小，那么正常去除
            return div(a, b);
        }
        if (b == INT_MIN) {
            // a不是整数最小，b是整数最小
            return 0;
        }
        // a是整数最小，b是-1，返回整数最大，因为题目里明确这么说了
        if (b == neg(1)) {
            return INT_MAX;
        }
        // a是整数最小，b不是整数最小，b也不是-1
        a = add(a, b > 0 ? b : neg(b));
        int ans = div(a, b);
        int offset = b > 0 ? neg(1) : 1;
        return add(ans, offset);
    }

    // 必须保证a和b都不是整数最小值，返回a除以b的结果
    int div(int a, int b) {
        int x = a < 0 ? neg(a) : a;
        int y = b < 0 ? neg(b) : b;
        int ans = 0;
        for (int i = 30; i >= 0; i = minus(i, 1)) {
            if ((x >> i) >= y) {
                ans |= (1 << i);
                x = minus(x, y << i);
            }
        }
        return a < 0 ^ b < 0 ? neg(ans) : ans;
    }

    int add(int a, int b) {
        int ans = a;
        while (b != 0) {
            // ans : a和b无进位相加的结果
            ans = a ^ b;
            // b : a和b相加时的进位信息
            b = (a & b) << 1;
            a = ans;
        }
        return ans;
    }

    int minus(int a, int b) {
        return add(a, neg(b));
    }

    int neg(int n) {
        return add(~n, 1);
    }

    // 这种乘法后面有大用处，尤其是求(a的b次方 % m)的结果，也叫龟速乘
    int multiply(int a, int b) {
        int ans = 0;
        unsigned int ub = (unsigned int)b;
        while (ub != 0) {
            if ((ub & 1) != 0) {
                // 考察b当前最右的状态！
                ans = add(ans, a);
            }
            a <<= 1;
            ub >>= 1;
        }
        return ans;
    }
};
