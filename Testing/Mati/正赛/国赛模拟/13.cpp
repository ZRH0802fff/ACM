#include<bits/stdc++.h>
using namespace std;

int n, q, status;
string s;
int led[100010];
int rst[100010];

int f(char ch){
    return (int)ch - (int)'a';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    cin >> s;
    for (int i = 0; i < n; ++i){
        status ^= (1 << f(s[i]));
        led[i] = status;
    }
    rst[n - 1] = 1 << f(s[n - 1]);
    for (int i = n - 2; i >= 0; --i){
        rst[i] = rst[i + 1] ^ (1 << f(s[i]));
    }
    for (int _ = 0, l, r; _ < q; ++_){
        cin >> l >> r;
        int ll = (l == 1) ? 0 : led[l - 2];
        int rr = (r == n) ? 0 : rst[r];
        int mask = status ^ ll ^ rr;
        int odd = 0;
        for (int i = 0; i < 26; ++i)
            if (mask & (1 << i)) odd++;
        int even = 26 - odd;
        cout << even << ' ' << odd << '\n';
    }
    return 0;
}