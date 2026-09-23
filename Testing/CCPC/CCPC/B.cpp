#include<bits/stdc++.h>
using namespace std;

int a[7];
int b[7];
int k;

int main(){
    for (int i = 1; i <= 6; ++i){
        cin >> a[i];
    }
    cin >> k;
    sort(a + 1, a + 7);
    if ((a[3] + 1) * 5+a[4]+1<=k){
        for (int i = 1; i <= 5;++i){
            b[i] = a[3] + 1;
        }
        b[6] = a[4] + 1;
    }else if((a[4]+1)*4+a[3]+1<=k ){
        for (int i = 1; i <= 4; ++i){
            b[i] = a[4] + 1;
        }
        b[6] = a[3] + 1;
    } else if (((a[4] + 1) * 4 + a[1] + 1 + a[2] + 1)<=k){
        for (int i = 1; i <= 4; ++i){
            b[i] = a[4] + 1;
        }
        b[5] = a[1] + 1;
        b[6] = a[2] + 1;
    } else if((a[6]+1)*3+a[1]+1+2<=k){
        for (int i = 1; i <= 3; ++i){
            b[i] = a[6] + 1;
        }
        b[4] = a[1] + 1;
        b[5] = 1;
        b[6] = k - ((a[6] + 1) * 3 + a[1] + 1 + 1);
    }else{
        cout << "No" << '\n';
        return 0;
    }
    sort(b + 1, b + 7);
    cout << "YES" << '\n';
    for (int i = 1; i <=6; ++i)
        cout << b[i] << ' ';
    return 0;
}