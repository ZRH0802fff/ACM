// 删除至少几个字符可以变成另一个字符串的子串
// 给定两个字符串s1和s2
// 返回s1至少删除多少字符可以成为s2的子串
// 对数器验证
#include <bits/stdc++.h>
using namespace std;

// 暴力方法
// 为了验证

// 生成s1字符串的所有子序列串
void f(string& s1, int i, string path, vector<string>& list) {
    if (i == (int)s1.length()) {
        list.push_back(path);
    } else {
        f(s1, i + 1, path, list);
        f(s1, i + 1, path + s1[i], list);
    }
}

int minDelete1(string s1, string s2) {
    vector<string> list;
    f(s1, 0, "", list);
    // 排序 : 长度大的子序列先考虑
    // 因为如果长度大的子序列是s2的子串
    // 那么需要删掉的字符数量 = s1的长度 - s1子序列长度
    // 子序列长度越大，需要删掉的字符数量就越少
    // 所以长度大的子序列先考虑
    sort(list.begin(), list.end(), [](const string& a, const string& b) {
        return a.length() > b.length();
    });
    for (const string& str : list) {
        if (s2.find(str) != string::npos) {
            // 检查s2中，是否包含当前的s1子序列str
            return s1.length() - str.length();
        }
    }
    return s1.length();
}

// 正式方法，动态规划
int minDelete2(string str1, string str2) {
    int n = str1.length();
    int m = str2.length();
    // dp[len1][len2] :
    // s1[前缀长度为i]至少删除多少字符，可以变成s2[前缀长度为j]的任意后缀串
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        dp[i][0] = i;
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = dp[i - 1][j] + 1;
            }
        }
    }
    int ans = INT_MAX;
    for (int j = 0; j <= m; j++) {
        ans = min(ans, dp[n][j]);
    }
    return ans;
}

// 为了验证
// 生成长度为n，有v种字符的随机字符串
string randomString(int n, int v) {
    string ans(n, ' ');
    for (int i = 0; i < n; i++) {
        ans[i] = 'a' + rand() % v;
    }
    return ans;
}

// 为了验证
// 对数器
int main() {
    srand(time(0));
    // 测试的数据量比较小
    // 那是因为数据量大了，暴力方法过不了
    // 但是这个数据量足够说明正式方法是正确的
    int n = 12;
    int v = 3;
    int testTime = 20000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int len1 = rand() % n + 1;
        int len2 = rand() % n + 1;
        string s1 = randomString(len1, v);
        string s2 = randomString(len2, v);
        int ans1 = minDelete1(s1, s2);
        int ans2 = minDelete2(s1, s2);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
