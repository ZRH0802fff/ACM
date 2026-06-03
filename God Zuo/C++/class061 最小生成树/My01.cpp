#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
const int MAXM = 200010;

struct Edge{
    int u, v, w;
}edges[MAXM];

bool cmp(Edge x,Edge y){
    return x.w < y.w;
}

int father[MAXN];
int n, m, ans;

void build (int n){
    for (int i = 0; i <= n;++i){
        father[i] = i;
    }
}

int find(int i){
    if(i!=father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

bool merge(int x,int y){
    int fx = find(x);
    int fy = find(y);
    if(fx!=fy){
        father[fx] = fy;
        return true;
    }else{
        return false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m){
        build(n);
        for (int i = 0; i < m;++i){
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        sort(edges, edges + m, cmp);
        int tmp = 0;
        for (int i = 0; i < m;++i){
            if(merge(edges[i].u,edges[i].v)){
                ++tmp;
                ans += edges[i].w;
            }
        }
        
        if (tmp==n-1){
            cout << ans << "\n";
        }else{
            cout << "orz" << "\n";
        }
    }
    return 0;
}