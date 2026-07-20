#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int T, n;
ll m;
ll arr[510010];

bool check(ll mid,int n){
    ll tal = 0;
    for (int i = 0; i < n;++i){
        tal += arr[i] / mid;
    }
    return tal <= m;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int _ = 0; _ < T;++_){
        cin >> n >> m;
        for (int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        ll l = 1, r = 1e9 + 1,mid;
        ll ans;
        while (l<=r){
            mid = (l + r) / 2;
            if(check(mid,n)){
                ans = mid;
                r = mid - 1;
            }else{
                l = mid + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}