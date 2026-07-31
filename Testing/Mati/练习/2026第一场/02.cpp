#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,pre;
    cin >> n >> pre;
    string ans = to_string(pre);
    for (int i; i < n-1;i++){
        int cur;
        cin >> cur;
        if(cur<pre){
            ans += ' ' + to_string(cur);
            pre = cur;
        }else{
            ans += ' ' + to_string(pre);
        }
    }
    cout << ans << "\n";
    return 0;
}