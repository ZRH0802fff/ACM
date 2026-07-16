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

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 33000;
const int MAXM = 65;
int cost[MAXM];
int val[MAXM];
bool king[MAXM];
int fans[MAXM];
int follow[MAXM][2];
int dp[MAXM][MAXN];
int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n>>m){
        for (int i = 1; i <= m; ++i){
            fans[i] = 0;
        }
        for (int i = 1,v,p,q; i <= m;++i){
            cin >> v >> p >> q;
            cost[i] = v;
            val[i] = v * p;
            king[i] = (q == 0);
            if(q!=0){
                follow[q][fans[q]++] = i;
            }
        }
        int p = 0;
        for (int i = 1; i <= m; ++i){
            if(king[i]){
                for (int j = 0; j <= n;++j){
                    dp[i][j] = dp[p][j];
                    if(j>=cost[i]){
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i]] + val[i]);
                    }
                    int fan1 = fans[i] >= 1 ? follow[i][0] : -1;
                    int fan2 = fans[i] >= 2 ? follow[i][1] : -1;
                    if(fan1!=-1 && j>=cost[i]+cost[fan1])
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
                    if (fan2 != -1 && j >= cost[i] + cost[fan2])
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
                    if (fan1 != -1 && fan2 != -1 && j >= cost[i] + cost[fan1] + cost[fan2])
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
                }
                p = i;
            }
        }
        cout<<dp[p][n]<<'\n';
    }
    return 0;
}