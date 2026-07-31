// 至少有1位重复的数字个数
// 给定正整数n，返回在[1, n]范围内至少有1位重复数字的正整数个数
// 测试链接 : https://leetcode.cn/problems/numbers-with-repeated-digits/

#include <bits/stdc++.h>
using namespace std;

int cnt2[12];
// cnt2[i] :
// 一共长度为len，还剩i位没有确定，确定的前缀为len-i位，且确定的前缀不为空
// 0~9一共10个数字，没有选择的数字剩下10-(len-i)个
// 那么在后续的i位上，有多少种排列
// 比如：len = 4
// cnt2[4]不计算
// cnt2[3] = 9 * 8 * 7
// cnt2[2] = 8 * 7
// cnt2[1] = 7
// cnt2[0] = 1，表示前缀已确定，后续也没有了，那么就是1种排列，就是前缀的状况
// 再比如：len = 6
// cnt2[6]不计算
// cnt2[5] = 9 * 8 * 7 * 6 * 5
// cnt2[4] = 8 * 7 * 6 * 5
// cnt2[3] = 7 * 6 * 5
// cnt2[2] = 6 * 5
// cnt2[1] = 5
// cnt2[0] = 1，表示前缀已确定，后续也没有了，那么就是1种排列，就是前缀的状况
// 下面for循环就是求解cnt2的代码

// 之前已经确定了和num一样的前缀，且确定的部分一定不为空
// 还有len位没有确定
// 哪些数字已经选了，哪些数字没有选，用status表示
// 返回<=num且每一位数字都不一样的正整数有多少个
int g(int num, int len, int offset, int status) {
    if (len == 0) {
        // num自己
        return 1;
    }
    int ans = 0;
    // first是num当前位的数字
    int first = (num / offset) % 10;
    for (int cur = 0; cur < first; cur++) {
        if ((status & (1 << cur)) == 0) {
            ans += cnt2[len - 1];
        }
    }
    if ((status & (1 << first)) == 0) {
        ans += g(num, len - 1, offset / 10, status | (1 << first));
    }
    return ans;
}

int countSpecialNumbers(int n) {
    int len = 1;
    int offset = 1;
    int tmp = n / 10;
    while (tmp > 0) {
        len++;
        offset *= 10;
        tmp /= 10;
    }
    cnt2[0] = 1;
    for (int i = 1, k = 10 - len + 1; i < len; i++, k++) {
        cnt2[i] = cnt2[i - 1] * k;
    }
    int ans = 0;
    if (len >= 2) {
        ans = 9;
        for (int i = 2, a = 9, b = 9; i < len; i++, b--) {
            a *= b;
            ans += a;
        }
    }
    int first = n / offset;
    ans += (first - 1) * cnt2[len - 1];
    ans += g(n, len - 1, offset / 10, 1 << first);
    return ans;
}

class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        return n - countSpecialNumbers(n);
    }
};

int main() {
    Solution sol;
    cout << "n=20: " << sol.numDupDigitsAtMostN(20) << " (expected 1, only 11)" << endl;
    cout << "n=100: " << sol.numDupDigitsAtMostN(100) << " (expected 10)" << endl;
    cout << "n=1000: " << sol.numDupDigitsAtMostN(1000) << " (expected 262)" << endl;
    return 0;
}
