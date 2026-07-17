// 多重背包不进行枚举优化
// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1776
// 核心: 朴素三重循环 dp[i][j]=max(dp[i-1][j], dp[i-1][j-k*w[i]]+k*v[i])
//       枚举每种货物选0~c[i]个
// 坑点: 时间O(n*t*avg_cnt), 不优化会超时; 空间压缩时j倒序

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXW = 40005;
int val[MAXN];
int w[MAXN];
int c[MAXN];
int dp[MAXW];
int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m){
        for (int i = 1; i <= n;++i){
            cin >> val[i] >> w[i] >> c[i];
        }
        for (int i = 0; i <= m;++i){
            dp[i] = 0;
        }
        for (int i = 1; i <= n;++i){
            for (int j = m; j >= w[i];j--){
                for (int k = 1; k <= c[i] && j >= w[i] * k;++k){
                    dp[j] = max(dp[j], dp[j - k * w[i]] + k * val[i]);
                }
            }
        }
        cout << dp[m] << '\n';
    }
    return 0;
}