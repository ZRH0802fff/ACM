// 最长公共子序列其中一个结果
// 给定两个字符串str1和str2
// 输出两个字符串的最长公共子序列
// 如果最长公共子序列为空，则输出-1
// 测试链接 : https://www.nowcoder.com/practice/4727c06b9ee9446cab2e859b4bb86bb8
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

// 讲解067 - 题目3，最长公共子序列长度
const int MAXN = 5001;

int dp[MAXN][MAXN];
char ans[MAXN];
string s1, s2;
int n, m, k;

// 填好dp表
void fillDp() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
}

void lcs() {
    fillDp();
    k = dp[n][m];
    if (k > 0) {
        for (int len = k, i = n, j = m; len > 0;) {
            if (s1[i - 1] == s2[j - 1]) {
                ans[--len] = s1[i - 1];
                i--;
                j--;
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    i--;
                } else {
                    j--;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    getline(cin, s1);
    getline(cin, s2);
    n = s1.length();
    m = s2.length();
    lcs();
    if (k == 0) {
        cout << -1 << "\n";
    } else {
        for (int i = 0; i < k; i++) {
            cout << ans[i];
        }
        cout << "\n";
    }
    return 0;
}
