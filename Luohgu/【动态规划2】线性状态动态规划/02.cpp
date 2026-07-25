/*
核心点：
    dp[i] 以鼠i结尾是最多打几个
    dp[i]=max(dp[i],dp[k]+1) 1<=k<i
    且要满足k到i的曼哈顿距离小于i
*/

#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x, y, t;
} p[10010];

int dp[10010];
int n, m,ans;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
        cin >> p[i].t >> p[i].x >> p[i].y;
    dp[1] = 1;
    for (int i = 2; i <= m; ++i){
        dp[i] = 1;
        for (int j = 1,dis; j < i; ++j){
            dis = abs(p[i].x - p[j].x) + abs(p[i].y - p[j].y);
            if(dis<=p[i].t-p[j].t){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    for (int i = 1; i <= m; ++i){
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}