#include<bits/stdc++.h>
using namespace std;

int n, k,ans;
int arr[300010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i){
        cin >> arr[i];
        if(i%k==0)
            ans += arr[i];
    }
    cout << ans << '\n';
    return 0;
}