#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
ll dp[1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i){
        ll lose, win, use;
        cin >> lose >> win >> use;
        for (int j=m; j >= 0; --j){
            if(j>=use){
                dp[j] = max(dp[j]+lose, dp[j - use] + win);
            }else{
                dp[j] += lose;
            }
        }
    }
    cout << dp[m]*5 << '\n';
    return 0;
}

/*

题意：
    01背包
    有足够的药，代价是药，用指定的药可以获得胜利的val，不用就打不过但是也可以获得失败的val
核心：
    01背包的板子题，只不过在不选i时要加上lose的val
坑点：
    losei，wini<1e6,n<1e3 ans<1e9 
    ans*5会越界
    建议都使用ll
    
*/