#include<bits/stdc++.h>
using namespace std;

int T;
int n,ma,sun;
int sushu[300010];
int arr[300010];
bool isprime[300010];

void isPrime(int n){
    fill(isprime, isprime + n + 1, true);
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= n; ++i){
        if(isprime[i]){
            sushu[sun] = i;
            ++sun;
        }
        for (int j = 0; j < sun && i * sushu[j] <= n; ++j){
            isprime[i * sushu[j]] = false;
            if(i%sushu[j]==0)
                break;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while(T--){
        cin >> n;
        isPrime(n);
        for (int i = 0; i < sun;++i){
            cout << sushu[i] << ' ';
        }
        // for (int i = 0; i < n; ++i){
        //     cin >> arr[i];
        //     ma = arr[i] > ma ? arr[i] : ma;
        // }
        

    }
    return 0;
}