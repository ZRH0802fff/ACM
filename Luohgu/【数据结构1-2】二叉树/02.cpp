#include<bits/stdc++.h>
using namespace std;

int n;
int tree[2000010];

int dfs(int i){
    if(i==0)
        return 0;
    int lh = dfs(tree[2 * i]);
    int rh = dfs(tree[2 * i + 1]);
    return max(lh, rh) + 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n;++i){
        int l, r;
        cin >> l >> r;
        tree[i * 2] = l;
        tree[i * 2 + 1] = r;
    }
    int ans = dfs(1);
    cout << ans << "\n";
    return 0;
}