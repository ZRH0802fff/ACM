#include<bits/stdc++.h>
using namespace std;

int T;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int _ = 0; _< T; ++_){
        int n, q;
        cin >> n >> q;
        set<pair<int, int>> griph;
        for (int i = 0; i < n;++i){
            string s;
            cin >> s;
            int len = s.size();
            int x = s[0]-'a';
            int y = s[len - 1]-'a';
            griph.insert({x, y});
            for (int k = 0; k < 26; ++k){
                if (griph.find({k, x}) != griph.end())  griph.insert({k,y});
                if (griph.find({y, k}) != griph.end())  griph.insert({x,k});
            }   
        }
        // for(auto it : griph){
        //     cout << it.first << ' ' << it.second << '\n';
        // }
        for (int t = 0; t < q; ++t){
            char u, v;
            cin >> u >> v;
            int iu = u - 'a';
            int iv = v - 'a';
            if(griph.find({iu,iv})!=griph.end()){
                cout << "Yes" << '\n';
            }else{
                cout << "No" << '\n';
            }
        }
    }
    return 0;
}