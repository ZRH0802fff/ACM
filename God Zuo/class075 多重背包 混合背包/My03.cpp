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

#include<bits/stdc++.h>
using namespace std;

const int maxn = 100005;
const int maxw = 1005;
int h1, m1, h2, m2,n,t,idx;
char T;
int v[maxn], w[maxn], dp[maxw];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> h1 >> T >> m1 >> h2 >> T >> m2 >> n){
        if (m1 > m2){
            h2--;
            m2 += 60;
        }
        t = (h2 - h1) * 60 + m2 - m1;
        idx=0;
        for (int i = 1,cos,val,cnt; i <= n;++i){
            cin >> cos >> val >> cnt;
            if(cnt==0)
                cnt = 1001;
            for (int k = 1; k <= cnt; k<<=1){
                v[++idx] = k * val;
                w[idx] = k * cos;
                cnt -= k;
            }
            if(cnt>0){
                v[++idx] = cnt * val;
                w[idx] = cos * cnt;
            }
        }
        for (int i = 0; i <= t;++i)
            dp[i] = 0;
        for (int i = 1; i <= idx;++i){
            for (int j = t; j >= w[i]; --j){
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
        cout << dp[t] << '\n';
    }
    return 0;
}