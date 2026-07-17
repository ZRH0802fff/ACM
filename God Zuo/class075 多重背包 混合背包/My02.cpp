// 多重背包通过二进制分组转化成01背包(模版)
// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1776
// 核心: 每种货物按数量二进制拆分: 1+2+4+...+剩余=原数量
//       例如cnt=13拆成1,2,4,6; 每组作为一个新物品, 转化为01背包
//       时间复杂度O(t * sum(log cnt_i)), 最常用
// 坑点: ①二进制拆分后m个物品做01背包(j倒序) ②剩余部分(cnt>0)也要放入

#include<bits/stdc++.h>
using namespace std;

const int maxn = 1005;
const int maxm = 40005;

int n,t,idx;
int val[maxn];
int wei[maxn];
int dp[maxm];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n>>t){
        idx = 0;
        for (int i = 1, v, w, c; i <= n; ++i){
            cin >> v >> w >> c;
            for (int k = 1; k <= c;k<<=1){
                val[++idx] = k * v;
                wei[idx] = k * w;
                c -= k;
            }
            if(c>0){
                val[++idx] = c * v;
                wei[idx] = c * w;
            }
        }
        for (int i = 1; i <= idx;++i){
            for (int j = t; j >= wei[i]; --j){
                dp[j] = max(dp[j], dp[j - wei[i]] + val[i]);
            }
        }
        cout << dp[t] << '\n';
    }
    return 0;
}