#include<bits/stdc++.h>
using namespace std;

int n, ans;
int arr[130][130];
int mx = -1828810;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n;++i){
        for (int j = 1; j <= n;++j){
            int t;
            cin >> t;
            arr[i][j] = t + arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
        }
    }
    for (int x1 = 1; x1 <= n;++x1){
        for (int y1 = 1; y1 <= n;++y1){
            for (int x2 = x1; x2 <= n;++x2){
                for (int y2 = y1; y2 <= n;++y2){
                    mx = max(mx, arr[x2][y2] - arr[x2][y1 - 1] - arr[x1 - 1][y2] + arr[x1 - 1][y1 - 1]);
                }
            }
        }
    }
    cout << mx << "\n";
    return 0;
}