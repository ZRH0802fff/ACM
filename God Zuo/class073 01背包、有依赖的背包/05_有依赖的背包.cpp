// 有依赖的背包(模版)
// 物品分为两大类：主件和附件
// 主件的购买没有限制，钱够就可以；附件的购买有限制，该附件所归属的主件先购买，才能购买这个附件
// 每个主件最多有2个附件，并且附件不会再有附件，主件购买后，怎么去选择归属附件完全随意，钱够就可以
// 所有的物品编号都在1~m之间，每个物品有三个信息：价格v、重要度p、归属q
// 价格就是花费，价格 * 重要度 就是收益，归属就是该商品是依附于哪个编号的主件
// 给定m件商品的信息，给定总钱数n，返回在不违反购买规则的情况下最大的收益
// 测试链接 : https://www.luogu.com.cn/problem/P1064
// 核心: 每个主件最多2附件, 5种选择: 不选/只要主/主+附1/主+附2/主+附1+附2
//       用p记录上一个主件行, dp[i]从dp[p]转移而非dp[i-1]
// 坑点: ①附件跟随主件展开, 非主件的行直接跳过 ②空间压缩时j必须从n到cost[i]倒序
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 33005;
const int MAXM = 65;

int cost[MAXM];
int val[MAXM];
bool king[MAXM];
int fans[MAXM];
int follows[MAXM][2];
int dp[MAXN];
int n, m;

void clean() {
    for (int i = 1; i <= m; i++) {
        fans[i] = 0;
    }
}

// 严格位置依赖的动态规划
int compute1() {
    int f[MAXM][MAXN] = {};
    int p = 0; // 上一个主件
    for (int i = 1, fan1, fan2; i <= m; i++) {
        if (!king[i]) continue;
        for (int j = 0; j <= n; j++) {
            f[i][j] = f[p][j];
            if (j >= cost[i]) {
                f[i][j] = max(f[i][j], f[p][j - cost[i]] + val[i]);
            }
            fan1 = fans[i] >= 1 ? follows[i][0] : -1;
            fan2 = fans[i] >= 2 ? follows[i][1] : -1;
            if (fan1 != -1 && j >= cost[i] + cost[fan1]) {
                f[i][j] = max(f[i][j], f[p][j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
            }
            if (fan2 != -1 && j >= cost[i] + cost[fan2]) {
                f[i][j] = max(f[i][j], f[p][j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
            }
            if (fan1 != -1 && fan2 != -1 && j >= cost[i] + cost[fan1] + cost[fan2]) {
                f[i][j] = max(f[i][j],
                    f[p][j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
            }
        }
        p = i;
    }
    return f[p][n];
}

// 空间压缩
int compute2() {
    fill(dp, dp + n + 1, 0);
    for (int i = 1, fan1, fan2; i <= m; i++) {
        if (!king[i]) continue;
        for (int j = n; j >= cost[i]; j--) {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
            fan1 = fans[i] >= 1 ? follows[i][0] : -1;
            fan2 = fans[i] >= 2 ? follows[i][1] : -1;
            if (fan1 != -1 && j >= cost[i] + cost[fan1]) {
                dp[j] = max(dp[j], dp[j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
            }
            if (fan2 != -1 && j >= cost[i] + cost[fan2]) {
                dp[j] = max(dp[j], dp[j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
            }
            if (fan1 != -1 && fan2 != -1 && j >= cost[i] + cost[fan1] + cost[fan2]) {
                dp[j] = max(dp[j],
                    dp[j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
            }
        }
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        clean();
        for (int i = 1, v, p, q; i <= m; i++) {
            cin >> v >> p >> q;
            cost[i] = v;
            val[i] = v * p;
            king[i] = (q == 0);
            if (q != 0) {
                follows[q][fans[q]++] = i;
            }
        }
        cout << compute2() << '\n';
    }
    return 0;
}
