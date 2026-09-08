#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000010;
const int maxm = 1000010;

int t;
int n, m;

int head[maxn];
int to[maxm];
int nxt[maxm];
int cnt;

int ideg[maxn];
int ans[maxn];
int fil;

priority_queue<int, vector<int>, greater<int>> q;

void build(){
    memset(head, 0, sizeof(head));
    memset(ideg, 0, sizeof(ideg));
    cnt = 1;
    fil = 0;
    while(!q.empty()){
        q.pop();
    }
}

void addEdge(int u, int v){
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

bool toposort(){
    for(int i = 1; i <= n; ++i){
        if(ideg[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur = q.top();
        q.pop();
        ans[cur] = ++fil;
        for(int ei = head[cur]; ei != 0; ei = nxt[ei]){
            int v = to[ei];
            if(--ideg[v] == 0){
                q.push(v);
            }
        }
    }
    return fil == n;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while(t--){
        cin >> n >> m;
        build();
        for(int i = 0, l, r; i < m; ++i){
            cin >> l >> r;
            int pre;
            cin >> pre;
            for(int j = l + 1, v; j <= r; ++j){
                cin >> v;
                addEdge(pre, v);
                ideg[v]++;
                pre = v;
            }
        }

        if(!toposort()){
            cout << -1 << '\n';
        }
        else{
            for(int i = 1; i <= n; ++i){
                cout << ans[i] << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}