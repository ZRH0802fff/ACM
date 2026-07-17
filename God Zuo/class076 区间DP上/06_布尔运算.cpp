// 布尔运算
// 给定一个布尔表达式和一个期望的布尔结果 result
// 布尔表达式由 0 (false)、1 (true)、& (AND)、 | (OR) 和 ^ (XOR) 符号组成
// 布尔表达式一定是正确的，不需要检查有效性
// 但是其中没有任何括号来表示优先级
// 你可以随意添加括号来改变逻辑优先级
// 目的是让表达式能够最终得出result的结果
// 返回最终得出result有多少种不同的逻辑计算顺序
// 测试链接 : https://leetcode.cn/problems/boolean-evaluation-lcci/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
int dp[MAXN][MAXN][2];
bool has[MAXN][MAXN];

class Solution {
public:
    // 记忆化搜索
    int countEval(string str, int result) {
        int n = str.length();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                has[i][j] = false;
            }
        }
        int* ft = f(str, 0, n - 1);
        return ft[result];
    }

    // s[l...r]是表达式的一部分，且一定符合范式
    // 0/1  逻  0/1   逻       0/1
    //  l  l+1  l+2  l+3........r
    // s[l...r]  0 : ?
    //           1 : ?
    // ans : int[2] ans[0] = false方法数 ans[1] = true方法数
    int* f(string& s, int l, int r) {
        if (has[l][r]) {
            return dp[l][r];
        }
        int fcnt = 0;
        int tcnt = 0;
        if (l == r) {
            // 只剩一个字符，0/1
            fcnt = s[l] == '0' ? 1 : 0;
            tcnt = s[l] == '1' ? 1 : 0;
        } else {
            int *tmp1, *tmp2;
            int a, b, c, d;
            for (int k = l + 1; k < r; k += 2) {
                // l ... r
                // 枚举每一个逻辑符号最后执行 k = l+1 ... r-1  k+=2
                tmp1 = f(s, l, k - 1);
                a = tmp1[0];
                b = tmp1[1];
                tmp2 = f(s, k + 1, r);
                c = tmp2[0];
                d = tmp2[1];
                if (s[k] == '&') {
                    fcnt += a * c + a * d + b * c;
                    tcnt += b * d;
                } else if (s[k] == '|') {
                    fcnt += a * c;
                    tcnt += a * d + b * c + b * d;
                } else {
                    fcnt += a * c + b * d;
                    tcnt += a * d + b * c;
                }
            }
        }
        dp[l][r][0] = fcnt;
        dp[l][r][1] = tcnt;
        has[l][r] = true;
        return dp[l][r];
    }
};

int main() {
    Solution sol;
    cout << "=== 布尔运算 ===" << endl;

    // 测试用例
    string s1 = "1";
    cout << "s = \"1\", result = 1, 预期: 1" << endl;
    cout << "结果: " << sol.countEval(s1, 1) << endl;
    cout << endl;

    string s2 = "0";
    cout << "s = \"0\", result = 0, 预期: 1" << endl;
    cout << "结果: " << sol.countEval(s2, 0) << endl;
    cout << endl;

    string s3 = "1^0|0|1";
    cout << "s = \"1^0|0|1\", result = 0, 预期: 2" << endl;
    cout << "结果: " << sol.countEval(s3, 0) << endl;
    cout << endl;

    string s4 = "0&0&0&1^1|0";
    cout << "s = \"0&0&0&1^1|0\", result = 1, 预期: 10" << endl;
    cout << "结果: " << sol.countEval(s4, 1) << endl;

    return 0;
}
