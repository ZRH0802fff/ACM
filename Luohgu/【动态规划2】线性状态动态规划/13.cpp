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