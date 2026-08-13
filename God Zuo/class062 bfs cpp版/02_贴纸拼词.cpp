// 贴纸拼词
// 我们有 n 种不同的贴纸。每个贴纸上都有一个小写的英文单词。
// 您想要拼写出给定的字符串 target ，方法是从收集的贴纸中切割单个字母并重新排列它们
// 如果你愿意，你可以多次使用每个贴纸，每个贴纸的数量是无限的。
// 返回你需要拼出 target 的最小贴纸数量。如果任务不可能，则返回 -1
// 注意：在所有的测试用例中，所有的单词都是从 1000 个最常见的美国英语单词中随机选择的
// 并且 target 被选择为两个随机单词的连接。
// 测试链接 : https://leetcode.cn/problems/stickers-to-spell-word/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 401;

string queue_[MAXN];
int l, r;

// 下标0 -> a
// 下标1 -> b
// 下标2 -> c
// ...
// 下标25 -> z
vector<vector<string>> graph(26);

unordered_set<string> visited;

string sortStr(const string& str) {
    string s = str;
    sort(s.begin(), s.end());
    return s;
}

string nextStr(const string& t, const string& s) {
    string builder;
    int i = 0, j = 0;
    while (i < (int)t.length()) {
        if (j == (int)s.length()) {
            builder += t[i++];
        } else {
            if (t[i] < s[j]) {
                builder += t[i++];
            } else if (t[i] > s[j]) {
                j++;
            } else {
                i++;
                j++;
            }
        }
    }
    return builder;
}

class Solution {
public:
    // 宽度优先遍历的解法
    // 也可以使用动态规划
    // 后续课程会有动态规划专题讲解
    int minStickers(vector<string>& stickers, string target) {
        for (int i = 0; i < 26; i++) {
            graph[i].clear();
        }
        visited.clear();
        for (string& str : stickers) {
            str = sortStr(str);
            for (int i = 0; i < (int)str.length(); i++) {
                if (i == 0 || str[i] != str[i - 1]) {
                    graph[str[i] - 'a'].push_back(str);
                }
            }
        }
        target = sortStr(target);
        visited.insert(target);
        l = r = 0;
        queue_[r++] = target;
        int level = 1;
        // 使用队列的形式是整层弹出
        while (l < r) {
            int size = r - l;
            for (int i = 0; i < size; i++) {
                string cur = queue_[l++];
                for (string& s : graph[cur[0] - 'a']) {
                    string next = nextStr(cur, s);
                    if (next == "") {
                        return level;
                    } else if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        queue_[r++] = next;
                    }
                }
            }
            level++;
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<string> stickers1 = {"with","example","science"};
    cout << sol.minStickers(stickers1, "thehat") << " (expected: 3)" << endl;
    vector<string> stickers2 = {"notice","possible"};
    cout << sol.minStickers(stickers2, "basicbasic") << " (expected: -1)" << endl;
    return 0;
}
