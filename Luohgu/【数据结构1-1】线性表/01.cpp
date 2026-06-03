#include<bits/stdc++.h>
using namespace std;

int n, m, arr[2000010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n;++i){
        cin >> arr[i];
    }
    for (int i = 0; i < m;++i){
        int op;
        cin >> op;
        cout << arr[op-1] << "\n";
    }
    return 0;
}