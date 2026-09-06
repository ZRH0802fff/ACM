#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        int jingsheng = m - (n + 1) / 2;
        cout << jingsheng + 1 << '\n';
    }
    return 0;
}