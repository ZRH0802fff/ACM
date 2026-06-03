#include<bits/stdc++.h>
using namespace std;

int n, p, mi=1e9;
int arr[5000010],qz[5000010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p;
    for (int i = 1; i <= n;++i){
        cin >> arr[i];
    }
    for (int i = 0; i < p;++i){
        int x, y, z;
        cin >> x >> y >> z;
        qz[x] += z;
        qz[y + 1] -= z;
    }
    for (int i = 1; i <= n;++i){
        qz[i] += qz[i - 1];
        arr[i] += qz[i];
        if(arr[i]<mi)
            mi = arr[i];
    }
    cout << mi << "\n";
    return 0;
}