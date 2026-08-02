#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int _ = 0; _ < T; ++_){
        int n;
        cin >> n;
        long long ans = 0;
        int t1;
        cin >> t1;
        for (int i = 1; i < n; ++i){
            long long num;
            cin >> num;
            if(num>0)
                ans += num;
        }
        cout << ans << '\n';
    }
    return 0;
}