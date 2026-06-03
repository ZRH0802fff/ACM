#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    cin >> m >> n;
    int arr[1010], r = 1, l = 0,ans=0;
    for (int i = 0; i < n;++i){
        int num;
        cin >> num;
        auto it = find(arr + l, arr + r, num);
        if(it==arr+r){
            if(r-l==m)
                ++l;
            arr[r++] = num;
            ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}