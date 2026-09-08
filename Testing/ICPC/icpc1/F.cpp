#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    long long psum=0;
    int ans=0;
    for (int i = 1; i <= n; ++i){
        long long sum1 = 0;
        for (int j = 1; j <= m; ++j){
            long long num;
            cin >> num;
            sum1 += num;
        }
        if(sum1<psum){
            ans++;
        }
        psum = sum1;
    }
    cout << ans << '\n';
    return 0;
}