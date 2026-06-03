#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    queue<int> q;
    for (int i = 1; i <= n;++i)
        q.push(i);
    int idx = 1;
    int ans[n];
    int ans_idx = 0;
    while(!q.empty()){
        while(idx<m){
            ++idx;
            int tmp = q.front();
            q.pop();
            q.push(tmp);
        }
        ans[ans_idx++] = q.front();
        q.pop();
        idx = 1;
    }
    for (int i = 0; i < n; ++i){
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}