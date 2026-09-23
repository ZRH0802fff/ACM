#include<bits/stdc++.h>
using namespace std;

string op;
int n;
int arr[2010];
int tmp[4010];

bool isok(){
    int st = 0;
    for (int i = 0; i < n; ++i){
        if(tmp[i]==arr[0]){
            st = i;
            break;
        }
        for (int i = 0; i <n; ++i){
            if(tmp[i+st]!=arr[i]) return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> op >> n;
    if(op=="first"){
        for (int i = 0; i < n; ++i)
            cin >> arr[i];

        tmp[0] = arr[1];
        tmp[1] = arr[0];
        for (int i = 2; i < n; ++i){
            tmp[i] = arr[i];
        }
        for (int i = 0; i < n; ++i){
            tmp[n + i] = tmp[i];
        }

        for (int i = 0; i < n; ++i){
            cout << arr[i] << ' ';
        }
        cout << '\n';

        for (int st = 0; st < n - 1; ++st){
            for (int i = 0; i < n; ++i){
                cout << tmp[i + st] << ' ';
            }
            cout << '\n';
        }
    }else if(op=="second"){
        for (int i = 0; i < n; ++i){
            cin >> tmp[i];
        }
        for (int i = 0; i < n; ++i){
            tmp[n + i] = tmp[i];
        }

        for (int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        if(!isok()){
            int arr2[n];
            for (int i = 0; i < n; ++i){
                arr2[i] = arr[i];
            }
            for (int i = 0; i < n; ++i){
                cin >> arr[i];
            }
            if(isok()){
                for (int i = 0; i < n; ++i){
                    cout << arr2[i] << ' ';
                }
                cout << '\n';
            }else{
                for (int i = 0; i < n; ++i){
                    cout << tmp[i] << ' ';
                }
                cout << '\n';
            }
            return 0;
        }else{
            for (int ci = 3; ci <= n; ++ci){
                for (int i = 0; i < n; ++i){
                    cin >> arr[i];
                }
                if(!isok()){
                    for (int i = 0; i < n; ++i){
                        cout << arr[i]<<' ';
                    }
                    cout << "\n";
                    return 0;
                }
            }
        }
    }
    return 0;
}