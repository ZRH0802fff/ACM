#include<bits/stdc++.h>
using namespace std;

int n, w;
int arr[20];
int memo[20];
int ans;

void dfs(int i,int cnt){
    if(cnt>=ans) return;
    if(i==n+1){
        ans = min(cnt, ans);
        return;
    }
    for (int j = 1; j <= cnt; ++j){
        if (arr[i] + memo[j] <= w){
            memo[j] += arr[i];
            dfs(i + 1, cnt);
            memo[j] -= arr[i];
        }
    }
    memo[cnt + 1] = arr[i];
    dfs(i + 1, cnt + 1);
    memo[cnt + 1] = 0;
}

int main(){
    cin >> n >> w;
    for (int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    sort(arr + 1, arr + 1 + n, greater<int>());
    ans = n;
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}