#include<bits/stdc++.h>
using namespace std;

struct Point{
    int val, idx, pidx;
} p[1000010];

int n;
int ans[1000010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> p[i].val;
        p[i].idx = i;
    }
    sort(p, p + n, [](const Point &p1, const Point &p2)
         { return p1.val < p2.val; });
    p[0].pidx = 0;
    for (int i = 1; i < n;++i){
        p[i].pidx = i;
        if(p[i].val==p[i-1].val)
            p[i].pidx = p[i - 1].pidx;
        //cout << p[i].val << ' ' << p[i].idx <<' '<< p[i].pidx << '\n';
    }
    for (int i = 0; i < n; ++i){
        ans[p[i].idx] = p[i].pidx + 1;
    }
    for (int i = 0; i < n;++i)
        cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}