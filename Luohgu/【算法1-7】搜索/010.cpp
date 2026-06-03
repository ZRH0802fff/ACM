#include<bits/stdc++.h>
using namespace std;
int n,ans;
int memo[25];
string s[25];
char sta;

void dfs(const string &tmp){
    ans = max(ans, int(tmp.size()));
    for (int i = 1; i <= n;++i){
        if(memo[i]>=2) continue;
        for (int j = 1; j < min(tmp.size(), s[i].size());++j){
            if (tmp.substr(tmp.size()-j)==s[i].substr(0,j)){
                ++memo[i];
                dfs(tmp + s[i].substr(j));
                --memo[i];
                // 【优化】贪心策略：为了让接龙最长，重叠部分越短越好。
                // 既然 j 是从小到大遍历的，找到的第一个重叠就是最短重叠，直接 break 即可。
                break;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> s[i];
    }
    cin >> sta;
    for (int i = 1; i <= n;++i) if(s[i][0]==sta){
            ++memo[i];
            dfs(s[i]);
            --memo[i];
    }
    cout << ans << "\n";
    return 0;
}