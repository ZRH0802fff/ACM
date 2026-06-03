#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    map<pair<int,int>,int > grid;
    cin >> n >> q;
    for (int i = 0; i < q;++i){
        int op;
        cin >> op;
        if(op==1){
            int i, j, k;
            cin >> i >> j >> k;
            grid[{i, j}] = k;
        }else{
            int i, j;
            cin >> i >> j;
            cout << grid[{i, j}] << "\n";
        }
    }
    return 0;
}