#include<bits/stdc++.h>
using namespace std;

int n,m;
unordered_map<string, int> p;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i){
        string t;
        cin >> t;
        p[t] = 0;
    }
    cin >> m;
    for (int _ = 0; _ < m; ++_){
        int op, y;
        string x;
        cin >> op;
        if(op==1){
            cin >> x >> y;
            if(p.count(x))
                p[x] += y;
        }else if (op==2){
            cin >> x;
            if(p.count(x)){
                cout << p[x] << '\n';
            }else{
                cout << -1 << '\n';
            }
        }
    }
    return 0;
}