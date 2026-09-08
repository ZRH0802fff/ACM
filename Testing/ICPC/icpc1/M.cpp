#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    unordered_map<string, bool> grid;
    unordered_set<string> arr;
    for (int i = 0; i < n; ++i){
        string s;
        cin >> s;
        grid[s] = false;
        arr.insert(s);
    }
    for (int i = 0; i < m; ++i){
        string s;
        cin >> s;
        if(arr.find(s)!=arr.end()){
            if(grid[s]==false){
                cout << "OK" << '\n';
                grid[s] = true;
            }else{
                cout << "REPEAT" << '\n';
            }
        }else{
            cout << "WRONG" << '\n';
        }
    }
    return 0;
}