#include<bits/stdc++.h>
using namespace std;

const int MAXN = 11;
vector<vector<pair<int, int>>> grid;

void build(int n){
    grid.assign(n + 1, vector<pair<int, int>>());
}

void jiantu(const vector<vector<int>>& edges){
    for(const auto& edge:edges){
        grid[edge[0]].push_back({edge[1], edge[2]});
    }
}

void bianli(int n){
    for (int i = 1; i <= n;++i){
        cout << i << "(邻居、边权) : ";
        for(const auto& edge:grid[i]){
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << endl;
    }
}

int main(){
    // 例子1：有向带权图
    int n1 = 4;
    vector<vector<int>> edges1 = {
        {1, 3, 6}, {4, 3, 4}, {2, 4, 2}, {1, 2, 7}, {2, 3, 5}, {3, 1, 1}};
    build(n1);
    jiantu(edges1);
    bianli(n1);
    return 0;
}