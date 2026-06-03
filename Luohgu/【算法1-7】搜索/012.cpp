#include<bits/stdc++.h>
using namespace std;

int n;
int path[15];

void dfs(int nd, int pre, int idx){
    if(nd==0){
        if(idx==1)
            return;
        for (int i = 0; i < idx - 1;++i){
            cout << path[i] << "+";
        }
        cout << path[idx - 1]<<endl;
    }
    for (int i = pre; i <= nd;++i){
        if(i<n){
            path[idx] = i;
            dfs(nd - i, i, idx + 1);
        }
    }
}

int main(){
    cin >> n;
    dfs(n, 1, 0);
    return 0;
}