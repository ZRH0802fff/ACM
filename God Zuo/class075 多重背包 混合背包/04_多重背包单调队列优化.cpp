// 多重背包单调队列优化
// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1776
// 核心: 同余分组(mod=0..w[i]-1), 每组用单调队列维护窗口最大值
//       指标值 = dp[上一行][j] - j/w[i]*v[i], 把多重背包的k枚举优化掉
//       时间复杂度O(n*t), 最优解
// 坑点: ①空间压缩时需要从右往左求(保证左侧是上一行旧值)
//       ②单调队列队头判断过期: queue[l]==j-w[i]*(c[i]+1)
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXW = 40005;

int v[MAXN], w[MAXN], c[MAXN];
int dp[MAXW];
int qu[MAXW]; // 单调队列
int l, r;
int n, t;

// 当前来到i号货物，需要j位置的指标，返回指标值
// 指标 = dp[i-1][j] - j/w[i]*v[i]
inline int value(int i, int j) {
    return dp[j] - j / w[i] * v[i];
}

// 空间压缩的动态规划 + 单调队列优化枚举
// 因为求dp[i][j]时需要上一行左侧的若干格子
// 所以做空间压缩时，每一行需要从右往左求
// 以此来保证左侧的格子还没有更新，还是"上一行"的状况
int compute() {
    fill(dp, dp + t + 1, 0);
    for (int i = 1; i <= n; i++) {
        // 同余分组: mod = 0, 1, 2, ..., w[i]-1
        for (int mod = 0; mod <= min(t, w[i] - 1); mod++) {
            l = r = 0;
            // 先把c[i]个的指标进入单调队列（从右往左）
            for (int j = t - mod, cnt = 1; j >= 0 && cnt <= c[i]; j -= w[i], cnt++) {
                while (l < r && value(i, qu[r - 1]) <= value(i, j)) {
                    r--;
                }
                qu[r++] = j;
            }
            // 滑动窗口，从右往左求dp[j]
            for (int j = t - mod, enter = j - w[i] * c[i]; j >= 0; j -= w[i], enter -= w[i]) {
                // 窗口进入enter位置
                if (enter >= 0) {
                    while (l < r && value(i, qu[r - 1]) <= value(i, enter)) {
                        r--;
                    }
                    qu[r++] = enter;
                }
                // 计算dp[j] = 队头指标 + j/w[i]*v[i]
                dp[j] = value(i, qu[l]) + j / w[i] * v[i];
                // 窗口弹出j位置
                if (qu[l] == j) {
                    l++;
                }
            }
        }
    }
    return dp[t];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> t) {
        for (int i = 1; i <= n; i++) {
            cin >> v[i] >> w[i] >> c[i];
        }
        cout << compute() << '\n';
    }
    return 0;
}
