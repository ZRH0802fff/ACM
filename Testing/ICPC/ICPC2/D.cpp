#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+5;
const int MOD = 998244353;

long long n,q;
long long arr[MAXN];
long long ans;

long long fac[MAXN];
long long inv[MAXN];

long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv[MAXN - 1] = qpow(fac[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 1; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

long long c(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

long long jiecheng(int num){
    long long ans = 1;
    for (int i = 2; i <= num; ++i){
        ans = (ans * i) % MOD;
    }
    return ans%MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    cin >> n >> q;
    ans = 1;
    bool flag = true;
    for (int i = 0, idx, val; i < q; ++i){
        cin >> idx >> val;
        if(arr[idx]!=0){
            flag = false;
        }
        arr[idx] = val;
    }

    for (int i = 1; i < (1 << n); ++i){
        if(arr[i]!=0){
            if(arr[2*i]>arr[i] || arr[2*i+1]>arr[i]){
                flag = false;
                break;
            }
            if(arr[2*i]==arr[i] || arr[2*i+1]==arr[i]){
                continue;
            }else{
                arr[2 * i] = arr[i];
            arr[2 * i + 1] = arr[i];
            }
        }
    }

    // for (int i = 1; i < (2 << n); ++i){
    //         cout << arr[i] << ' ';
    //     }
    // cout << '\n';

    if(!flag){
        cout << 0 << '\n';
        return 0;
    }

    long long  idx = (1 << n);
    long long num = 0;
    int maxidx = 2 << n;
    //cout << maxidx << '\n';
    while(idx < maxidx){
        //cout << idx << '\n';
        if(arr[idx]==0){
            idx++;
            num++;
        } else {
            long long curnum = arr[idx];
            int qn = 1;
            while(idx+1<(2<<n) && arr[idx+1]==arr[idx]) {
                idx++;
                qn++;
            }
            idx++;
            //cout << qn << ' ' << arr[idx]<<" ";
            ans = (ans * ((c(curnum-1,qn-1)*jiecheng(qn))%MOD))%MOD;
            ans = (ans * (qn - 1)) % MOD;
        }
        //out << '\n';
    }
    // cout << num <<' '<<ans<<'\n';
    //cout << ans << '\n';
    ans = (ans * jiecheng(num)) % MOD;
    cout << ans << '\n';
    return 0;
}