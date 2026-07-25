#include<bits/stdc++.h>
using namespace std;

const int MAXN = 33000;
const int MAXM = 65;
int cost[MAXM];
int val[MAXM];
bool king[MAXM];        //是否为主件
int fans[MAXM];         //存附件个数
int follow[MAXM][2];    //存附件下标
int dp[MAXM][MAXN];
int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n>>m){
        for (int i = 1; i <= m; ++i){
            fans[i] = 0;
        }
        for (int i = 1,v,p,q; i <= m;++i){
            cin >> v >> p >> q;
            cost[i] = v;
            val[i] = v * p;
            king[i] = (q == 0);
            if(q!=0){
                follow[q][fans[q]++] = i;
            }
        }
        int p = 0;
        for (int i = 1; i <= m; ++i){
            if(king[i]){
                for (int j = 0; j <= n;++j){
                    dp[i][j] = dp[p][j];
                    if(j>=cost[i]){
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i]] + val[i]);
                    }
                    int fan1 = fans[i] >= 1 ? follow[i][0] : -1;
                    int fan2 = fans[i] >= 2 ? follow[i][1] : -1;
                    if(fan1!=-1 && j>=cost[i]+cost[fan1])
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
                    if (fan2 != -1 && j >= cost[i] + cost[fan2])
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
                    if (fan1 != -1 && fan2 != -1 && j >= cost[i] + cost[fan1] + cost[fan2])
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
                }
                p = i;
            }
        }
        cout<<dp[p][n]<<'\n';
    }
    return 0;
}


/*
核心点：
    只展开是主件的行，并通过p来找到上一个有效行
    可能性分为 1 不要该主件 2 只要主件 3 要主件+附件1  4要主件+附件2  5 要主件+附件1+附件2 
*/