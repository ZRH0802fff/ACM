// 自由之路
// 题目描述比较多，打开链接查看
// 测试链接 : https://leetcode.cn/problems/freedom-trail/
// 为了让所有语言的同学都可以理解
// 不会使用任何java语言自带的数据结构
// 只使用最简单的数组结构

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int MAXC = 26;
int ring[MAXN];
int key[MAXN];
int sz[MAXC];
int where[MAXC][MAXN];
int dp[MAXN][MAXN];
int n, m;

void build(string r, string k) {
    memset(sz, 0, sizeof(sz));
    n = r.length();
    m = k.length();
    for (int i = 0, v; i < n; i++) {
        v = r[i] - 'a';
        where[v][sz[v]++] = i;
        ring[i] = v;
    }
    for (int i = 0; i < m; i++) {
        key[i] = k[i] - 'a';
    }
    memset(dp, -1, sizeof(dp));
}

// 指针当前指着轮盘i位置的字符，要搞定key[j....]所有字符，最小代价返回
int f(int i, int j) {
    if (j == m) {
        // key长度是m
        // 都搞定
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    int ans;
    if (ring[i] == key[j]) {
        // ring b
        //      i
        // key  b
        //      j
        ans = 1 + f(i, j + 1);
    } else {
        // 轮盘处在i位置，ring[i] != key[j]
        // jump1 : 顺时针找到最近的key[j]字符在轮盘的什么位置
        // distance1 : 从i顺时针走向jump1有多远
        int jump1 = clockFind(i, key[j]);
        int distance1 = (jump1 > i ? (jump1 - i) : (n - i + jump1));
        // jump2 : 逆时针找到最近的key[j]字符在轮盘的什么位置
        // distance2 : 从i逆时针走向jump2有多远
        int jump2 = counterClockFind(i, key[j]);
        int distance2 = (i > jump2 ? (i - jump2) : (i + n - jump2));
        ans = min(distance1 + f(jump1, j), distance2 + f(jump2, j));
    }
    dp[i][j] = ans;
    return ans;
}

// 从i开始，顺时针找到最近的v在轮盘的什么位置
int clockFind(int i, int v) {
    int l = 0;
    // size[v] : 属于v这个字符的下标有几个
    int r = sz[v] - 1, m;
    // sorted[0...size[v]-1]收集了所有的下标，并且有序
    int* sorted = where[v];
    int find = -1;
    // 有序数组中，找>i尽量靠左的下标
    while (l <= r) {
        m = (l + r) / 2;
        if (sorted[m] > i) {
            find = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    // 找到了就返回
    // 没找到，那i顺指针一定先走到最小的下标
    return find != -1 ? sorted[find] : sorted[0];
}

int counterClockFind(int i, int v) {
    int l = 0;
    int r = sz[v] - 1, m;
    int* sorted = where[v];
    int find = -1;
    // 有序数组中，找<i尽量靠右的下标
    while (l <= r) {
        m = (l + r) / 2;
        if (sorted[m] < i) {
            find = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    // 找到了就返回
    // 没找到，那i逆指针一定先走到最大的下标
    return find != -1 ? sorted[find] : sorted[sz[v] - 1];
}

class Solution {
public:
    int findRotateSteps(string r, string k) {
        build(r, k);
        return f(0, 0);
    }
};
