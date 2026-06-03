#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;
int head[MAXN], nxt[MAXM], to[MAXM], cnt;
int indegree[MAXN], ans[MAXN];
int n, m;

void build(int n){
    cnt = 1;
    for (int i = 0; i <= n;++i){
        head[i] = 0;
        indegree[i] = 0;
    }
}

void addEdge(int u, int v){
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void topSort(){
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n;++i){
        if (indegree[i] == 0)
            pq.push(i);
    }
    int fill = 0;
    while(!pq.empty()){
        int cur = pq.top();
        pq.pop();
        ans[fill++] = cur;
        for (int e = head[cur]; e != 0; e = nxt[e]){
            if(--indegree[to[e]]==0){
                pq.push(to[e]);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin >> n >> m){
        build(n);
        for (int i = 0; i < m;++i){
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
            indegree[v]++;
        }
        topSort();
        for (int i = 0; i < n;++i){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}