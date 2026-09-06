#include<bits/stdc++.h>
using namespace std;

const int maxn = 1005;
const int maxk = 105;

int cow[maxk];
bool dt[maxn][maxn];

int k, n, m, ans;

void build(){
    for (int i = 1; i <= n;++i){
        for (int j = 1; j <= n;++j){
            dt[i][j] = false;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> k >> n >> m;
    for (int i = 1; i <= k; ++i){
        cin >> cow[i];
    }
    build();
    for (int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        dt[a][b] = true;
    }
    for (int i = 1; i <= n; ++i){
        dt[i][i] = true;
    }

    for (int t = 1; t <= n;++t){
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j){
                if(dt[i][t]&&dt[t][j]){
                    dt[i][j] = true;
                }
            }
        }
    }

    ans = 0;
    for (int i = 1; i <= n;++i){
        bool ok = true;
        for (int j = 1; j <= k;++j){
            if(!dt[cow[j]][i]){
                ok = false;
                break;
            }
        }
        if(ok) ++ans;
    }
    cout << ans << '\n';
    return 0;
}
