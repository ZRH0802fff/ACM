#include<bits/stdc++.h>
using namespace std;

int n;
int pwd;
int pma;
int idxm;
bool vis[105];
int tmp;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1,p; i <= n; ++i){
        cin >> p;
        if(p==-1){
            vis[i] = true;
        }else{
            if(p>pma){
                pma = p;
                idxm = i;
            }
            tmp += p;
        }
    }

    pwd = n - tmp;
    //cout << pwd << ' ' << pma << '\n';
    if(pwd>pma){
        for (int i = 1; i <= n;++i){
            if(vis[i])  cout<<i<<' ';
        }
        cout << '\n';
    }else if (pwd==pma){
        cout << idxm << '\n';
    }else{
        cout << idxm << '\n';
    }
    return 0;
}