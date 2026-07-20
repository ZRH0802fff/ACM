// 选课，树上01背包的最优解
// 在大学里每个学生，为了达到一定的学分，必须从很多课程里选择一些课程来学习
// 在课程里有些课程必须在某些课程之前学习，如高等数学总是在其它课程之前学习
// 现在有 N 门功课，每门课有个学分，每门课有一门或没有直接先修课
// 若课程 a 是课程 b 的先修课即只有学完了课程 a，才能学习课程 b
// 一个学生要从这些课程里选择 M 门课程学习
// 问他能获得的最大学分是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2014
// 最优解，链式前向星建图 + dfn序的利用 + 巧妙定义下的尝试
// 时间复杂度O(n * m)，推荐掌握，尤其是理解有效结构

#include<bits/stdc++.h>
using namespace std;

int n, m;
int nums[305];

int edgecnt;
int head[305];
int nxt[305];
int to[305];

int dfncnt;
int dfn[305];
int sz[305];
int val[305];

int dp[305][305];

void bulid(int n,int m){
    edgecnt = 1;
    dfncnt = 0;
    for (int i = 0; i <= n;++i){
        head[i] = 0;
    }
    for (int j = 0; j <= m; ++j){
        dp[n + 2][j] == 0;
    }
}

void addEdge(int u,int v){
    nxt[edgecnt] = head[u];
    to[edgecnt] = v;
    head[u] = edgecnt++;
}

void dfs(int u){
    int i = ++dfncnt;
    dfn[u] = i;
    val[i] = nums[u];
    sz[i] = 1;
    for (int ei = head[u], v; ei > 0;ei=nxt[ei]){
        v = to[ei];
        dfs(v);
        sz[i] += sz[dfn[v]];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1,u; i <= n; ++i){
        cin >> u >> nums[i];
        addEdge(u, i);
    }
    dfs(0);
    for (int i = n + 1; i >= 2; --i){
        for (int j = 1; j <= m;++j){
            dp[i][j] = max(dp[i + sz[i]][j], dp[i + 1][j - 1]+val[i]);
        }
    }
    cout << dp[2][m] << '\n';
    return 0;
}