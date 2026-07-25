// 去除重复字母 — LeetCode 316
// 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次
// 需保证返回结果的字典序最小（不能打乱其他字符的相对位置）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
int cnts[256];
bool enter[256];
char stk[MAXN];
int r;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        memset(cnts, 0, sizeof(cnts));
        memset(enter, 0, sizeof(enter));
        r = 0;

        // 统计每个字符的出现次数
        for (char c : s) cnts[c]++;

        for (char c : s) {
            cnts[c]--; // 遍历过了，剩余可用次数减1
            if (!enter[c]) {
                // 栈顶字符比当前大，且后面还会出现 → 可以弹出
                while (r > 0 && stk[r - 1] > c && cnts[stk[r - 1]] > 0) {
                    enter[stk[r - 1]] = false;
                    r--;
                }
                stk[r++] = c;
                enter[c] = true;
            }
        }
        stk[r] = '\0';
        return string(stk);
    }
};
