#include<bits/stdc++.h>
using namespace std;
int arr[100000];
int main(){
    int n;
    cin >> n;
    int sta;
    cin >> sta;
    int ans = sta;
    arr[0] = sta;
    for (int i = 1; i < n;++i){
        int num;
        cin >> num;
        arr[i] = num;
        int tans = INT_MAX;
        for (int t = 0; t < i;++t){
            if(abs(arr[t]-num)<tans)
                tans = abs(arr[t] - num);
                //cout << "  " << arr[t] << ' ' << num << ' ' << tans << endl;
            //cout <<"  "<<abs(arr[t] - num) << endl;
        }
        //cout << i << ':' << tans << endl;
        ans += tans;
    }
    cout << ans << endl;
    return 0;
}