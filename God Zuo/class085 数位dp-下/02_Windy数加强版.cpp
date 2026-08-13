 // windy数，加强版
// 课上没有讲这个文件，这是windy数的加强版测试
// 需要改成long类型，除此之外和课上讲的完全一样
// 测试链接 : https://www.luogu.com.cn/problem/P13085
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 21;

long long dp[MAXLEN][11][2];

void build(int len) {
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= 10; j++) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
}

// offset完全由len决定，为了方便提取num中某一位数字（上节课内容）
// 从num的高位开始，还剩下len位没有决定
// 前一位的数字是pre，如果pre == 10，表示从来没有选择过数字
// 如果之前的位已经确定比num小，那么free == 1，表示接下的数字可以自由选择
// 如果之前的位和num一样，那么free == 0，表示接下的数字不能大于num当前位的数字
// 返回<=num的windy数有多少个
long long f(long long num, long long offset, int len, int pre, int free) {
    if (len == 0) {
        return 1;
    }
    if (dp[len][pre][free] != -1) {
        return dp[len][pre][free];
    }
    int cur = (int)(num / offset % 10);
    long long ans = 0;
    if (free == 0) {
        if (pre == 10) {
            // 之前的位和num一样，此时不能随意选择数字
            // 也从来没有选择过数字
            // 就表示：来到的是num的最高位
            ans += f(num, offset / 10, len - 1, 10, 1); // 一个数字也不要
            for (int i = 1; i < cur; i++) {
                ans += f(num, offset / 10, len - 1, i, 1);
            }
            ans += f(num, offset / 10, len - 1, cur, 0);
        } else {
            // 之前的位和num一样，此时不能随意选择数字，
            // 之前选择过数字pre
            for (int i = 0; i <= 9; i++) {
                if (i <= pre - 2 || i >= pre + 2) {
                    if (i < cur) {
                        ans += f(num, offset / 10, len - 1, i, 1);
                    } else if (i == cur) {
                        ans += f(num, offset / 10, len - 1, cur, 0);
                    }
                }
            }
        }
    } else {
        if (pre == 10) {
            // free == 1，可以自由选择数字，前面的状况 < num
            // 从来没有选择过数字
            ans += f(num, offset / 10, len - 1, 10, 1); // 还是可以不选择数字
            for (int i = 1; i <= 9; i++) {
                ans += f(num, offset / 10, len - 1, i, 1);
            }
        } else {
            // free == 1，可以自由选择数字，前面的状况 < num
            // 选择过数字pre
            for (int i = 0; i <= 9; i++) {
                if (i <= pre - 2 || i >= pre + 2) {
                    ans += f(num, offset / 10, len - 1, i, 1);
                }
            }
        }
    }
    dp[len][pre][free] = ans;
    return ans;
}

// 求0~num范围上，windy数的个数
long long cnt(long long num) {
    if (num == 0) {
        return 1;
    }
    int len = 1;
    long long offset = 1;
    long long tmp = num / 10;
    while (tmp > 0) {
        len++;
        offset *= 10;
        tmp /= 10;
    }
    build(len);
    return f(num, offset, len, 10, 0);
}

long long compute(long long a, long long b) {
    return cnt(b) - cnt(a - 1);
}

int main() {
    long long a, b;
    while (cin >> a >> b) {
        cout << compute(a, b) << "\n";
    }
    return 0;
}
