#include<bits/stdc++.h>
using namespace std;
int n, x;
int arr[100010];
long long ans;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x;
    for (int i = 0; i < n;++i)
        cin >> arr[i];
    for (int i = 0; i < n - 1;++i){
        if(arr[i]+arr[i+1]>x){
            long long nd = arr[i] + arr[i + 1] - x;
            ans += nd;
            if(arr[i+1]>=nd){
                arr[i + 1] -= nd;
            }else{
                arr[i + 1] = 0;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}