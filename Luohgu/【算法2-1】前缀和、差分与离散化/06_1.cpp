#include<bits/stdc++.h>
using namespace std;

int n;
long long ans,l,r;

struct Point{
    long long x, y;
}p[20010];

bool cmp(Point a,Point b){
    if(a.x==b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n;++i){
        cin >> p[i].x >> p[i].y;
    }
    sort(p, p + n, cmp);
    long long l=p[0].x, r = p[0].y;
    for (int i = 1; i < n;++i){
        if(p[i].x<=r){
            r = max(r, p[i].y);
        }else{
            ans += (r - l);
            l = p[i].x;
            r = p[i].y;
        }
    }
    ans += (r - l);
    cout << ans << "\n";
    return 0;
}