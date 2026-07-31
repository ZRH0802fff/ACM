#include<bits/stdc++.h>
using namespace std;
int MOD = 10007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m,ans=0;
    cin >> n >> m;
    int pr = INT_MAX;
    for (int i=0; i < n;++i){
        int t;
        cin >> t;
        pr = min(pr, t);
    }
    //cout << "pr=" << pr << "\n";
    for (int i=0; i < m; ++i){
        int sta, ed;
        cin >> sta >> ed;
        sta -= pr;
        ed -= pr;
        sta = max(0, sta);
        ed = min(n - 1, ed);
        int len = 0;
        if (sta <= ed){
            len = ed - sta + 1;
        }
        int current_val = (n - len) % MOD;
        ans = (ans + current_val + MOD) % MOD;
    }
    cout << ans << "\n";
    return 0;
}