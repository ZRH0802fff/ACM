#include<bits/stdc++.h>
using namespace std;

int n;
unordered_map<int, int> arr;
int tarr[300010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n;++i){
        cin >> tarr[i];
        if(arr.count(tarr[i])){
            arr[tarr[i]]++;
        }else{
            arr[tarr[i]] = 1;
        }
    }
    for (int i = 0; i < n; ++i){
        cout << arr[tarr[i]] - 1 << ' ';
    }
    cout << '\n';
    return 0;
}