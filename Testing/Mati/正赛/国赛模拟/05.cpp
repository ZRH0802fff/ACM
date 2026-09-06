#include <bits/stdc++.h>
using namespace std;

int n,idx,lens;
string s;
string arr[1000];

bool isT(string& t){
    for (int i = 0; i < idx; ++i){
        if(arr[i]==t)
            return true;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    cin >> n;
    lens = s.size();
    for (int _ = 0; _ < n; ++_){
        string t;
        cin >> t;
        int m = t.size();
        if(m>lens){
            cout << "NO" << '\n';
            continue;
        }
        if(isT(t)){
            cout << "YES" << '\n';
            continue;
        }
        int i = 0,j=0;
        while(i<lens && j<m){
            //cout << s[i] << ' ' << t[j] << ' ' << i << j;
            if(s[i]==t[j]){
                ++i;
                ++j;
            } else{
                ++i;
            }
            //cout << i << j;
        }
        if(j==m){
            cout << "YES" << '\n';
            arr[idx++] = t;
        }else{
            cout << "NO" << '\n';
        }
    }
    for (int i = 0; i < idx;++i)
        //cout << arr[i] << ' ';
    return 0;
}