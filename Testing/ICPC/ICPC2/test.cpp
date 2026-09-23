#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
const int MOD = 998244353;

int n, q;
long long arr[MAXN];
long long ans;

long long fac[MAXN];
long long inv[MAXN];

long long qpow(long long a, long long b)
{
    long long res = 1;
    a %= MOD;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init()
{
    fac[0] = inv[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv[MAXN - 1] = qpow(fac[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 1; i--)
    {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

long long c(int n, int m)
{
    if (m < 0 || m > n)
        return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main(){
    init();
    cout << c(2, 2) << '\n';
    return 0;
}