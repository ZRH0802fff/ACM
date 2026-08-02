#include<bits/stdc++.h>
using namespace std;

int n, q;
int arr[1000010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 0; i < n; ++i){
        cin >> arr[i];
    }
    for (int i = 0,op; i < q; ++i){
        cin >> op;
        if(op==1){
            for (int i = 0; i < n; ++i){
                int tmp = arr[i] & (-arr[i]);
                int k = 0;
                int num = 1;
                while( tmp^(1<<k)){
                    k++;
                    num *= 2;
                }
                arr[i] += num;
            }
        }else{
            int sum = 0;
            for(int num:arr){
                sum += num;
            }
            cout << sum << '\n';
        }
    }
    return 0;
}