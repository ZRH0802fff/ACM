#include<bits./stdc++.h>
using namespace std;

const int MOD = 998244353;
int n, m;
int na, nb;
string s;
int ans;

int f(int cur,int numa,int numb){
    if(cur==0 || (numa==0 && numb==0))
        return 1;
    int ans = 1;
    ans += numa*f(cur - 1, numa - 1, numb + 1);
    ans %= MOD;
    ans += numa*f(cur - 1, numa - 1, numb);
    ans %= MOD;
    ans += numb*f(cur - 1, numa, numb - 1);
    ans %= MOD;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    cin >> s;
    for(char ch :s){
        if(ch=='a') na++;
        else if(ch=='b') nb++;
    }
    cout << f(m, na, nb) << '\n';
    return 0;
}