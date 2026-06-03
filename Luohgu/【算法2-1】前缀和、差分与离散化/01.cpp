#include<bits/stdc++.h>
using namespace std;

int n, m, arr[100010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n;++i){
        int t;
        cin >> t;
        arr[i] = t + arr[i - 1];
    }
    cin >> m;
    for (int i = 0; i < m;++i){
        int sta, ed;
        cin >> sta >> ed;
        cout << arr[ed] - arr[sta - 1] << "\n";
    }
    return 0;
}