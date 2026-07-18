// 没有上司的舞会
// 某大学有n个职员，编号为1...n
// 他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树
// 父结点就是子结点的直接上司
// 现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数
// 但是如果某个职员的直接上司来参加舞会了
// 那么这个职员就无论如何也不肯来参加舞会了
// 所以请你编程计算邀请哪些职员可以使快乐指数最大
// 返回最大的快乐指数。
// 测试链接 : https://www.luogu.com.cn/problem/P1352
// 本题和讲解037的题目7类似
// 链式链接 : https://leetcode.cn/problems/house-robber-iii/

#include<bits/stdc++.h>
using namespace std;

int n,h;
bool boss[6005];
int arr[6005];
int head[6005];
int nxt[6005];
int to[66005];
int cnt;
int no[6005];
int yes[6005];

void clean(int n){
    cnt = 1;
    for (int i = 0; i <= n;++i) {
        boss[i] = true;
        head[i] = 0;
        no[i] = 0;
        yes[i] = 0;
    }
}

void addEdge(int u,int v){
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void f(int u){
    no[u] = 0;
    yes[u] = arr[u];
    for (int ei = head[u], v; ei > 0;ei=nxt[ei]){
        v = to[ei];
        f(v);
        no[u] += max(no[v] , yes[v]);
        yes[u] += no[v];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    clean(n);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    for (int i = 1,s,x; i < n;++i){
        cin >> x >> s;
        addEdge(s, x);
        boss[x] = false;
    }
    for (int i = 1; i <= n;++i){
        if(boss[i]){
            h = i;
            break;
        }
    }
    f(h);
    cout << max(no[h], yes[h]) << '\n';
    return 0;
}