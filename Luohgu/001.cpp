#include<bits/stdc++.h>
using namespace std;

int n;
string s, ans="";


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<string, string> umap;
    cin >> n;
    for (int i = 0; i < n;++i){
        string k, v;
        cin >> k >> v;
        umap[k] = v;
    }
    string dummy;
    getline(cin, dummy);
    getline(cin, s);
    int len = s.size();
    int i = 0;

    while (i<len){
        char tmp = s[i];
        if(s[i]=='#'){
            ++i;
            string tt="";
            while(i<len && s[i]>='0' and s[i]<='9'){
                tt += s[i];
                ++i;
            }
            //cout <<  tt<<i << "\n";
            ans += umap[tt];
            //cout << ans << "\n";
        }else{
            ans += s[i];
            i++;
            //cout << ans << "\n";
        }
    }
    cout << ans << "\n";
    return 0;
}