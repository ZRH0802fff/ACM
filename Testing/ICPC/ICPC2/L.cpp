#include<bits/stdc++.h>
using namespace std;

const int maxn = 100010;
int T;
int n;
int arr[maxn];
int right[maxn];
int down[maxn];
int qzr[maxn];
int qzd[maxn];
map<int, int> book;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while(T--){
        cin >> n;
        for (int i = 1; i <= n; ++i){
            cin >> arr[i];
            down[i] = arr[i]*(n-i+1);

        }
    }
}