// 统计整数数目
// 给你两个数字字符串 num1 和 num2 ，以及两个整数max_sum和min_sum
// 如果一个整数 x 满足以下条件，我们称它是一个好整数
// num1 <= x <= num2
// min_sum <= digit_sum(x) <= max_sum
// 请你返回好整数的数目
// 答案可能很大，答案对 1000000007 取模
// 注意，digit_sum(x)表示x各位数字之和
// 测试链接 : https://leetcode.cn/problems/count-of-integers/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 23;
const int MAXM = 401;

int dp[MAXN][MAXM][2];
string num;
int minSum, maxSum, len;

void build() {
    memset(dp, -1, sizeof(dp));
}

// 注意：
// 数字，string num
// 数字长度，int len
// 累加和最小要求，int minSum
// 累加和最大要求，int maxSum
// 这四个变量都是全局静态变量，所以不用带参数，直接访问即可
// 递归含义：
// 从num的高位出发，当前来到i位上
// 之前决定的数字累加和是sum
// 之前的决定已经比num小，后续可以自由选择数字，那么free == 1
// 之前的决定和num一样，后续不可以自由选择数字，那么free == 0
// 返回有多少种可能性
int f(int i, int sum, int free) {
    if (sum > maxSum) {
        return 0;
    }
    if (sum + (len - i) * 9 < minSum) {
        return 0;
    }
    if (i == len) {
        return 1;
    }
    if (dp[i][sum][free] != -1) {
        return dp[i][sum][free];
    }
    // cur : num当前位的数字
    int cur = num[i] - '0';
    int ans = 0;
    if (free == 0) {
        // 还不能自由选择
        for (int pick = 0; pick < cur; pick++) {
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
        }
        ans = (ans + f(i + 1, sum + cur, 0)) % MOD;
    } else {
        // 可以自由选择
        for (int pick = 0; pick <= 9; pick++) {
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
        }
    }
    dp[i][sum][free] = ans;
    return ans;
}

bool check() {
    int sum = 0;
    for (char cha : num) {
        sum += cha - '0';
    }
    return sum >= minSum && sum <= maxSum;
}

class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        minSum = min_sum;
        maxSum = max_sum;
        num = num2;
        len = num2.length();
        build();
        int ans = f(0, 0, 0);
        num = num1;
        len = num1.length();
        build();
        ans = (ans - f(0, 0, 0) + MOD) % MOD;
        if (check()) {
            ans = (ans + 1) % MOD;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    // 示例1
    cout << "num1=1, num2=12, min=1, max=8: "
         << sol.count("1", "12", 1, 8) << " (expected 11)" << endl;
    // 示例2
    cout << "num1=1, num2=5, min=1, max=5: "
         << sol.count("1", "5", 1, 5) << " (expected 5)" << endl;
    return 0;
}
