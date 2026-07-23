#include<bits/stdc++.h>
using namespace std;

int n,ans;
bool ist[23][23];
int val[23];
int dp[23];
int path[23];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    for (int i = 1; i < n; ++i){
        for (int j = i + 1,op; j <= n; ++j){
            cin >> op;
            if(op==1){
                ist[i][j] = true;
                ist[j][i] = true;
            }
        }
    }

    dp[n] = val[n];
    for (int i = n - 1; i >= 1; --i){
        dp[i] = val[i];
        int dt = 0;
        int didx = -1;
        for (int j = i + 1; j <= n;++j){
            if(ist[i][j]){
                if(dp[j]>dt){
                    dt = dp[j];
                    didx = j;
                }
            }
        }
        dp[i] += dt;
        if(didx!=-1){
            path[i] = didx;
        }
    }
    int maxidx = 0;
    for (int i = 1; i <= n; ++i){
        if(dp[i]>ans){
            ans = dp[i];
            maxidx = i;
        }
    }
    int cur = maxidx;
    while (cur!=0){
        cout << cur << ' ';
        cur = path[cur];
    }
    
    cout << '\n';
    cout << ans << '\n';
    return 0;
}

/*
核心点：
    正推推不出来的时候考虑逆推
    即dp[i]表示以i开头时的最大
    并用辅助数组path记录路径
    最后每个点开始都可能是最大值，遍历得到最大的值与路径开头
    最终通过辅助数组path跳转出路径

坑点：
    path中可能存了很多个路径
    要根据最佳开头去跳转而不是输出非0路径
*/