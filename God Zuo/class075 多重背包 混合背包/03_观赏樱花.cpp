// 观赏樱花
// 给定一个背包的容量t，一共有n种货物，并且给定每种货物的信息
// 花费(cost)、价值(val)、数量(cnt)
// 如果cnt == 0，代表这种货物可以无限选择
// 如果cnt > 0，那么cnt代表这种货物的数量
// 挑选货物的总容量在不超过t的情况下，返回能得到的最大价值
// 背包容量不超过1000，每一种货物的花费都>0
// 测试链接 : https://www.luogu.com.cn/problem/P1833
// 核心: 完全背包(cnt=0)先转为多重背包(cnt=ENOUGH), 再二进制分组转01背包
//       ENOUGH = 1001 (> t=1000), 保证"无限"够用
// 坑点: ①时间计算: 别忘处理跨小时借位 ②输入有冒号需跳过
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXW = 1005;
const int ENOUGH = 1001; // 容量不超过1000, >1000即可视为无限

int v[MAXN], w[MAXN];
int dp[MAXW];
int hour1, minute1, hour2, minute2;
int t, n, m;

// 01背包的空间压缩代码(模版)
int compute() {
    fill(dp, dp + t + 1, 0);
    for (int i = 1; i <= m; i++) {
        for (int j = t; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[t];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    char colon;
    while (cin >> hour1 >> colon >> minute1 >> hour2 >> colon >> minute2 >> n) {
        // 时间跨小时的处理
        if (minute1 > minute2) {
            hour2--;
            minute2 += 60;
        }
        // 计算背包容量（分钟数）
        t = (hour2 - hour1) * 60 + minute2 - minute1;
        m = 0;
        for (int i = 0, cost, val, cnt; i < n; i++) {
            cin >> cost >> val >> cnt;
            if (cnt == 0) {
                cnt = ENOUGH; // 完全背包 → 多重背包
            }
            // 二进制分组
            for (int k = 1; k <= cnt; k <<= 1) {
                v[++m] = k * val;
                w[m] = k * cost;
                cnt -= k;
            }
            if (cnt > 0) {
                v[++m] = cnt * val;
                w[m] = cnt * cost;
            }
        }
        cout << compute() << '\n';
    }
    return 0;
}
