#include<bits/stdc++.h>
using namespace std;

const int N = 11;
const int M = 21;

int graph1[N][N];

vector<vector<pair<int, int>>> graph2;

int head[N];
int nxt[M];
int to[M];
int wei[M];
int cnt;

void build(int n){
    for (int i = 0; i <= n; ++i){
        for (int j = 0; j <= n; ++j){
            graph1[i][j] = 0;
        }
    }

    graph2.clear();
    graph2.resize(n + 1);

    cnt = 1;
    for (int i = 0; i <= n; ++i){
        head[i] = 0;
    }
}

void addEdge(int u,int v,int w){
    nxt[cnt] = head[u];
    to[cnt] = v;
    wei[cnt] = w;
    head[u] = cnt++;
}

void jinatu(int n, int edge[][3], int m){
    for (int i = 0; i < m; ++i){
        graph1[edge[i][0]][edge[i][1]] = edge[i][2];
    }

    for (int i = 0; i < m; ++i){
        graph2[edge[i][0]].push_back({edge[i][1], edge[i][2]});
    }

    for (int i = 0; i < m; ++i){
        addEdge(edge[i][0], edge[i][1], edge[i][2]);
    }
}

void binali(int n){
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            cout << graph1[i][j]<<' ';
        }
        cout << '\n';
    }

    for (int i = 1; i <= n; ++i){
        cout << i << "(邻居、边权) : ";
        for(auto& edge:graph2[i]){
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << '\n';
    }

    for (int i = 1; i <= n; ++i){
        cout << i << "(邻居、边权) : ";
        for (int ei = head[i]; ei > 0;ei=nxt[ei]){
            cout << '(' << to[ei] << ',' << wei[ei] << ')';
        }
        cout << '\n';
    }
}

int main(){

}