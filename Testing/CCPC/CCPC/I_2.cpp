#include<bits/stdc++.h>
using namespace std;

#define int long long

int n;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    //int p = pow(n, 1.0 / 3);
    int p = 0;
    for (p = 0; p <= 1e6; ++p){
        if(p*p*p>n)
            break;
    }
    p--;
    //cout << p << '\n';
    for (int a = 0; a <= p; ++a){
        for (int b = a; b <= p; ++b){
            for (int c = b; c <= p; ++c){
                if (a * b * (a + b) + b * c * (b + c) + a * c * (a + c) == n){
                    cout << a << ' ' << b << ' ' << c << '\n';
                    return 0;
                }
            }
        }
    }
    cout << -1 << '\n';
    return 0;
}