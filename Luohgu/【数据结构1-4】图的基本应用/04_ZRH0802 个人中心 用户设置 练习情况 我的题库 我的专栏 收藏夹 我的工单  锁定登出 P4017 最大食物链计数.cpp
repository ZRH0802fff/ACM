#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5001;
const int MAXM = 500001;
const int MOD = 80112002;

// 链式前向星建图
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt;

// 拓扑排序需要的队列
int queue_[MAXN];

// 拓扑排序需要的入度表
int indegree[MAXN];

// 拓扑排序需要的推送信息
int lines[MAXN];

int n, m;

void build(int n) {
    cnt = 1;
    for (int i = 0; i <= n; i++) {
        indegree[i] = 0;
        lines[i] = 0;
        head[i] = 0;
    }
}

void addEdge(int u, int v) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int ways() {
    int l = 0;
    int r = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue_[r++] = i;
            lines[i] = 1;
        }
    }
    int ans = 0;
    while (l < r) {
        int u = queue_[l++];
        if (head[u] == 0) {
            // 当前的u节点不再有后续邻居了
            ans = (ans + lines[u]) % MOD;
        } else {
            for (int ei = head[u], v; ei > 0; ei = nxt[ei]) {
                // u -> v
                v = to[ei];
                lines[v] = (lines[v] + lines[u]) % MOD;
                if (--indegree[v] == 0) {
                    queue_[r++] = v;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        build(n);
        for (int i = 0, u, v; i < m; i++) {
            cin >> u >> v;
            addEdge(u, v);
            indegree[v]++;
        }
        cout << ways() << '\n';
    }
    return 0;
}