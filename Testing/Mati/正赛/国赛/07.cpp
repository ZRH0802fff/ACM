#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n, x;
        cin >> n>>x;
        int ed = x / 2;
        if(x%2==0){
            ed--;
        }
        // cout << n << ' ' << ed << '*' << '\n';
         cout << n - ed<<'\n';
        for (int i = ed + 1; i <= n; ++i){
            cout << i << ' ';
        }
        cout << '\n';
    }
    return 0;
}