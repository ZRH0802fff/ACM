#include<bits/stdc++.h>
using namespace std;

int n, m, q;
int griph[1005][1005];
int temp[2010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cin >> griph[i][j];
    }
    cin >> q;
    for (int _ = 0,op,x,k; _ < q; ++_){
        cin >> op >> x >> k;
        int l = m;
        if(op==1)
            l += (k % m);
        else
            l -= (k % m);
        if(l>=m)
            l -= m;
        for (int i = 0; i < m; ++i){
            temp[i] = griph[x - 1][i];
            temp[m + i] = griph[x - 1][i];
        }
        for (int i = 0; i < 2 * m; ++i){
            //cout << temp[i] << ' ';
        }
        //cout << '\n';
        for (int i = 0; i < m; ++i){
            griph[x - 1][i] = temp[l + i];
            //cout << l+i<< temp[l + i] << ' ';
        }
        //cout << '\n';
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout << griph[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}