#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        int ans;
        if (n % 2 == 0){
            ans = (n * (n - 2)) / 2;
        }else{
            ans = (n * (n - 1)) / 2;
        }
        if(n%3==0){
            ans -= n * 2 / 3;
        }
        cout << ans << '\n';
    }
    return 0;
}