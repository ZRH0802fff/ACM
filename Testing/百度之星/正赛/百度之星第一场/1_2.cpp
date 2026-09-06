#include<bits/stdc++.h>
using namespace std;

int T;
int n, k, s;
struct G{
    int hp, val;
} arr[105];
bool Cmp(G a,G b){
    if(a.hp==b.hp) return a.val>b.val;
    return a.hp < b.hp;
}
int cnt;
int dp[105][35];


int f(int i,int j,int s){
    if(s>=arr[i-1].hp){
        
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int _ = 0; _ < T; ++_){
        cin >> n >> k >> s;
        for (int i = 0; i < n; ++i){
            cin >> arr[i].hp >> arr[i].val;
        }
        sort(arr, arr + n, Cmp);
        // for (int i = 0; i < n;++i){
        //     cout << arr[i].hp << ' ' << arr[i].val<<'\n';
        // }

        dp[0][0] = s;
        for (int j = 1; j <= k; ++j) dp[0][j]=s*2;
        for (int i = 1; i <= n; ++i){
            for (int j = 0; j <= k;++j){
                if(dp[i-1][j]>=arr[i].hp)
                    dp[i][j] = (dp[i - 1][j] + arr[i - 1].val);
                else{
                    dp[i][j] = dp[i][j - 1]*2;
                }
            }
        }
    }
    return 0;
}