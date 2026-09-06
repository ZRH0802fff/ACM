#include<bits/stdc++.h>
using namespace std;

struct QU{
    int t, contry;
} q[300010];
int c[100010];
int n;
int l, r;
int ans;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    while(n--){
        int t, k;
        cin >> t >> k;
        for (int i = 0,tc; i < k;++i){
            cin >> tc;
            q[r++] = {t, tc};
            c[tc]++;
            if(c[tc]==1)  ans++;
        }
        while(l<r && t-q[l].t>=86400){
            c[q[l].contry]--;
            if (c[q[l].contry]==0) ans--;
            l++;
        }
        cout << ans << '\n';
    }
    return 0;
}