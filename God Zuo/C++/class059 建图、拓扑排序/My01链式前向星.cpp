#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXM = 2000010;
//head数组下边表示图中的点，存的是这个点上第一条边的序号
//nxt数组中下标表示的是边号，存的是这个边下一条边（依旧是在当前节点做起始点的前提下）的边号，0表示没有了
//to数组中下标表示边号，存的是这个边去往的点
//weight数组中下标表示边号，存的是这个边的权重
//cnt表示当前到了第几条边
//综上所述，head数组和nxt数组用来存这个点的所有边和起点（head数组下标），to和weight数组用来存对应边的信息
int head[MAXN], nxt[MAXM], to[MAXM], weight[MAXM], cnt;

void build(int n){
    cnt = 1;
    fill(head + 1, head + n + 1, 0);
}

void addedge(int u,int v,int w){
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void directGraph(const vector<vector<int>>& edges){
    for(const auto& edge:edges){
        addedge(edge[0], edge[1], edge[2]);
    }
}

void bianli(int n){
    for (int i = 1; i <= n;++i){
        cout << i << "(邻居、边权) : ";
        for (int ei = head[i]; ei > 0;ei=nxt[ei]){
            cout << "(" << to[ei] << "," << weight[ei] << ") ";
        }
        cout << endl;
    }
}

int main(){
    int n = 4;
    vector<vector<int>> edges1 = {
        {1, 3, 6}, {4, 3, 4}, {2, 4, 2}, 
        {1, 2, 7}, {2, 3, 5}, {3, 1, 1}};
    build(n);
    directGraph(edges1);
    bianli(n);
    return 0;
}
 