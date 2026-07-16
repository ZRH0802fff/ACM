// 夏季特惠
// 某公司游戏平台的夏季特惠开始了，你决定入手一些游戏
// 现在你一共有X元的预算，平台上所有的 n 个游戏均有折扣
// 标号为 i 的游戏的原价a_i元，现价只要b_i元
// 也就是说该游戏可以优惠 a_i - b_i，并且你购买该游戏能获得快乐值为w_i
// 由于优惠的存在，你可能做出一些冲动消费导致最终买游戏的总费用超过预算
// 只要满足 : 获得的总优惠金额不低于超过预算的总金额
// 那在心理上就不会觉得吃亏。
// 现在你希望在心理上不觉得吃亏的前提下，获得尽可能多的快乐值。
// 测试链接 : https://leetcode.cn/problems/tJau2o/
// 核心: well = (原价-现价) - 现价
//       well>=0 → 变成"一定要买的商品"，预算增加well(相当于白送)，快乐值直接拿走
//       well<0  → 转为01背包商品，cost=-well, val=快乐值
// 坑点: well的推导——优惠(原-现)必须 >= 超预算部分(总花费-预算)
//       例如: 预算100, 原价10打折到3, well=(10-3)-3=4, 相当于预算变成104! 一定买!
//            预算104, 原价10打折到8, well=(10-8)-8=-6, 相当于花掉6元买这个商品
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXX = 100005;

// 对于"一定要买的商品"，直接买！
// 只把"需要考虑的商品"放入cost、val数组
int cost[MAXN];
long long val[MAXN];
long long dp[MAXX];
int n, m, x;

long long compute() {
    fill(dp, dp + x + 1, 0);
    for (int i = 1; i <= m; i++) {
        for (int j = x; j >= cost[i]; j--) {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    return dp[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> x) {
        m = 1;
        long long ans = 0;
        for (int i = 1, pre, cur, well; i <= n; i++) {
            long long happy;
            cin >> pre >> cur >> happy;
            // well = (原价 - 现价) - 现价 = 原价 - 2*现价
            well = pre - cur - cur;
            // 如下是一件"一定要买的商品"
            // 预算=100, 商品原价=10, 打折后=3
            // 那么好处(well) = (10-3)-3 = 4
            // 所以, 可以认为这件商品把预算增加到了104! 一定要买!
            if (well >= 0) {
                x += well;
                ans += happy;
            } else {
                // 如下是一件"需要考虑的商品"
                // 预算=104, 商品原价=10, 打折后=8
                // 那么好处(well) = (10-8)-8 = -6
                // 所以, 可以认为这件商品就花掉6元! (-well)
                cost[m] = -well;
                val[m++] = happy;
            }
        }
        ans += compute();
        cout << ans << '\n';
    }
    return 0;
}
