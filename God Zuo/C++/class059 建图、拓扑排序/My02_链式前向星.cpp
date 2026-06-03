#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
const int MAXM = 200010;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt;
int q[MAXM];
int l, r;
int indegree[MAXN];
int ans[MAXM];
int n, m;

void bulid(int n){
    cnt = 1;
    for (int i = 0; i <= n;++i){
        head[i] = 0;
        indegree[i]=0;
    }
}

void addEdge(int u,int v){
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

bool topsort(){
    l = r = 0;
    for (int i = 1; i <= n;++i){
        if(indegree[i]==0){
            q[r++] = i;
        }
    }
    int fill = 0;
    while(l<r){
        int cur = q[l++];
        ans[fill++] = cur;
        for (int e = head[cur]; e != 0;e=nxt[e]){
            if(--indegree[to[e]]==0){
                q[r++] = to[e];
            }
        }
    }
    return fill == n;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n>>m){
        bulid(n);
        for (int i = 0; i < m;++i){
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
            indegree[v]++;
        }
        if(!topsort())
            cout << -1 << "\n";
        else{
            for (int i = 0; i < n - 1;++i){
                cout << ans[i] << ' ';
            }
            cout << ans[n - 1] << "\n";
        }
    }
    return 0;
}