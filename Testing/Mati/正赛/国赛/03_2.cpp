#include <bits/stdc++.h>
using namespace std;

struct JuZhen
{
    int x1, x2, y1, y2;
} ju[5010];

int n;
int arr[5010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> ju[i].x1 >> ju[i].y1 >> ju[i].x2 >> ju[i].y2;
    }
    for (int i = 0, x1, x2, y1, y2; i < n; ++i)
    {
        x1 = ju[i].x1;
        x2 = ju[i].x2;
        y1 = ju[i].y1;
        y2 = ju[i].y2;
        int ans = 0;
        for (int j = 0, tx1, tx2, ty1, ty2; j < n; ++j)
        {
            tx1 = ju[j].x1;
            tx2 = ju[j].x2;
            ty1 = ju[j].y1;
            ty2 = ju[j].y2;

            // if((x2<tx1 && y2<ty1) || (x2==tx1 && y2<ty1) ||(x2<tx1 && y2==ty1) ||
            //    (x2<tx1 && y1>ty2) || (x2==tx1 && y1>ty2) ||(x2<tx1 && y1==ty2) ||
            //    (x1>tx2 && y1>ty2) ||(x1==tx2 && y1>ty2) ||(x1>tx2 && y1==ty2) ){
            //     continue;
            // }
            if(ty1>y2 || ty2<y1 || tx2<x1 || tx1>x2){
                continue;
            }
            //cout << "i=" << i << " j=" << j << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << tx1 << ' ' << ty1 << ' ' << tx2 << ' ' << ty2 << '\n';
            ans += 1;
        }
        cout << ans - 1 << ' ';
    }
    return 0;
}