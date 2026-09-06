#include<bits/stdc++.h>
using namespace std;

int n;
int arr[70];
bool vis[70];
int cnt;
int sum, maxval;
int len;

bool dfs(int cur,int cab,int last){
    if(cur>cnt) return true;
    if(cab==len) return dfs(cur+1,0,0);
    int fail = 0;
    for (int i = last; i < n; ++i){
        if(vis[i]) continue;
        if(cab+arr[i]<=len && fail!=arr[i]){
            vis[i] = true;
            if(dfs(cur,cab+arr[i],i+1)) return true;
            fail = arr[i];
            vis[i] = false;
            if(cab==0 || cab+arr[i]==len) return false;
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n && n){
        sum = 0;
        maxval = 0;
        for (int i = 0; i < n; ++i){
            cin>>arr[i];
            sum += arr[i];
            maxval = max(maxval, arr[i]);
        }
        sort(arr, arr + n, greater<int>());

        for (len = maxval; len <= sum; ++len){
            if(sum%len!=0) continue;
            cnt = sum / len;
            memset(vis, 0, sizeof(vis));
            if(dfs(1,0,0)) break;
        }
        cout << len << '\n';
    }
    return 0;
}