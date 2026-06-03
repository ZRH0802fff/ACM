#include<bits/stdc++.h>
using namespace std;

int n, m;
int arr[1010][1010], cf[1010][1010];

int main(){
    cin >> n >> m;
    for (int i = 0; i < m;++i){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ++cf[x1][y1];
        --cf[x2 + 1][y1];
        --cf[x1][y2 + 1];
        ++cf[x2 + 1][y2 + 1];
    }
    for (int i = 1; i <= n;++i){
        for (int j = 1; j <= n;++j){
            arr[i][j] += cf[i][j] + arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n;++i){
        for (int j = 1; j <= n;++j){
            cout << arr[i][j]<<' ';
        }
        cout << "\n";
    }
    return 0;
}