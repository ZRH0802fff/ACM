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
// 核心: well = (原价-现价) - 现价; well>=0变为白送(预算增加+直接拿快乐); well<0转为背包物品
// 坑点: ② well的推导: 优惠(原-现)必须 >= 超预算部分(总花费-预算), 变形得 预算+well >= 0

#include<bits/stdc++.h>
using namespace std;

const int MN = 505;
const int MX = 100010;
int cost[MN];
long long happy[MN];
long long dp[MX];
int n, idx, x;

long long f(){
    fill(dp, dp + x + 1, 0);
    for (int i = 1; i <= idx;++i){
        for (int j = x; j >= cost[i];--j){
            dp[j] = max(dp[j], dp[j - cost[i]] + happy[i]);
        }
    }
    return dp[x];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin >> n >> x){
        idx = 1;
        long long ans = 0;
        for (int i = 1, pre, cur, well; i <= n;++i){
            long long hp;
            cin >> pre >> cur >> hp;
            well = pre - cur - cur;
            if(well>=0){
                x+=well;
                ans += hp;
            }else{
                cost[idx] = -well;
                happy[idx++] = hp;
            }
        }
        ans += f();
        cout << ans << '\n';
    }
    
    return 0;
}