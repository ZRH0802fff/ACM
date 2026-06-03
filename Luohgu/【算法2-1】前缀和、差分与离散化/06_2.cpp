#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vector<ll> a(n), b(n);
    vector<ll> vals;
    for (int i = 0; i < n;++i){
        cin >> a[i] >> b[i];
        vals.push_back(a[i]);
        vals.push_back(b[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> cf(vals.size(), 0);
    for (int i = 0; i < n;++i){
        int l = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        int r = lower_bound(vals.begin(), vals.end(), b[i]) - vals.begin();
        ++cf[l];
        --cf[r];
    }
    ll ans = 0;
    int sum = 0;
    for (int i = 0; i < vals.size()-1; ++i){
        sum += cf[i];
        if(sum>0){
            ans += (vals[i + 1] - vals[i]);
        }
    }
    cout << ans << "\n";
    return 0;
}