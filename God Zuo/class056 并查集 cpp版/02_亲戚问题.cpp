// 亲戚问题 — 洛谷 P1551
// 并查集简化版：递归路径压缩，无小挂大

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
int father[MAXN];
int n, m, p;

int find(int i) {
    if (i != father[i]) father[i] = find(father[i]);
    return father[i];
}

void unionSet(int x, int y) {
    father[find(x)] = find(y);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) father[i] = i;
    for (int i = 0, x, y; i < m; i++) {
        cin >> x >> y; unionSet(x, y);
    }
    for (int i = 0, x, y; i < p; i++) {
        cin >> x >> y;
        cout << (find(x) == find(y) ? "Yes" : "No") << "\n";
    }
    return 0;
}
