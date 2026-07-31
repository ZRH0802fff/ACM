#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int ans1 = 0;
    int ans2 = 0;
    for (int i; i < n;i++){
        int a, b;
        cin >> a >> b;
        if (b>=a){
            ans1 += 1;
        }else{
            ans2 += 1;
        }
    }
    cout << ans1 << ' ' << ans2 << "\n";
    return 0;
}