// 并查集模板 — 洛谷 P3367
// n 个元素，m 次操作：1 x y 查询是否同集合，2 x y 合并

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
int father[MAXN];
int sz[MAXN]; // 小挂大
int n, m;

void build() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        sz[i] = 1;
    }
}

// 迭代版路径压缩
int find(int i) {
    int path[MAXN], cnt = 0;
    while (i != father[i]) {
        path[cnt++] = i;
        i = father[i];
    }
    for (int k = 0; k < cnt; k++) father[path[k]] = i;
    return i;
}

void unionSet(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        if (sz[fx] >= sz[fy]) { sz[fx] += sz[fy]; father[fy] = fx; }
        else { sz[fy] += sz[fx]; father[fx] = fy; }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    build();
    for (int i = 0, op, x, y; i < m; i++) {
        cin >> op >> x >> y;
        if (op == 1) cout << (find(x) == find(y) ? "Yes" : "No") << "\n";
        else unionSet(x, y);
    }
    return 0;
}
