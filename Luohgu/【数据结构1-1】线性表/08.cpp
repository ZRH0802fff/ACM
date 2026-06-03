#include<bits/stdc++.h>
using namespace std;

bool vis[110];
int r;
int stc[110];

int main(){
    string s;
    cin >> s;
    int len = s.size();
    for (int i = 0; i < len;++i){
        if(s[i]=='(' || s[i]=='['){
            stc[r++] = i;
        }else{
            if(r==0)
                vis[i] = false;
            else{
                if (s[i] == ']' && s[stc[r - 1]] == '['){
                    vis[i] = true;
                    vis[stc[--r]] = true;
                }else if (s[i] == ')' && s[stc[r - 1]] == '('){
                    vis[i] = true;
                    vis[stc[--r]] = true;
                }else{
                    vis[i] = false;
                }
            }
        }
    }
    string ans = "";
    for (int i = 0; i < len;++i){
        if (vis[i] == false){
            if(s[i]=='('||s[i]==')')
                ans += "()";
            else
                ans += "[]";
        }else{
            ans += s[i];
        }
    }
    cout << ans << endl;
    return 0;
}