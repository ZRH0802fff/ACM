#include<bits/stdc++.h>
using namespace std;

int n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int n =0 ; n < 20; ++n){
        int p = 0;
        for (p = 0; p <= 1e6; ++p){
            if (p * p * p > n)
                break;
        }
        cout << n << ' '<<p<< '\n';
        for (int a = -n; a <= n;++a){
            for (int b = -n; b <= n; ++b){
                for (int c = -n; c <= n; ++c){
                    if((a*b*(a+b)+b*c*(b+c)+a*c*(a+c))==n){
                        cout << "   " << a << ' ' << b << " " << c << ' ' << '\n';
                    }
                }
            }
        }
    }
    return 0;
}