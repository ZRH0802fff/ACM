// 售货员的难题 - TSP问题
// 某乡有n个村庄(1<=n<=20)，有一个售货员，他要到各个村庄去售货
// 各村庄之间的路程s(1<=s<=1000)是已知的
// 且A村到B村的路程，与B到A的路大多不同(有向带权图)
// 为了提高效率，他从商店出发到每个村庄一次，然后返回商店所在的村，
// 假设商店所在的村庄为1
// 他不知道选择什么样的路线才能使所走的路程最短
// 请你帮他选择一条最短的路
// 测试链接 : https://www.luogu.com.cn/problem/P1171

#include<bits/stdc++.h>
using namespace std;

int n;
int graph[20][20];
int dp[1 << 20][20];

int f(int s,int i){
    if(s==(1<<n)-1) return graph[i][0];
    if(dp[s][i]!=-1) return dp[s][i];
    int ans = INT_MAX;
    for (int j = 0; j < n; ++j){
        if((s&(1<<j))==0){
            ans = min(ans, graph[i][j] + f(s | (1 << j), j));
        }
    }
    dp[s][i] = ans;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> graph[i][j];
        }
    }
    for (int i = 0; i < (1 << n); ++i){
        for (int j = 0; j < n; ++j)
            dp[i][j] = -1;
    }
    cout << f(1, 0) << '\n';
    return 0;
}