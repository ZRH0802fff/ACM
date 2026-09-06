// 树的直径模版(树型dp版逻辑小化简)
// 给定一棵树，边权可能为负，求直径长度
// 测试链接 : https://www.luogu.com.cn/problem/U81904
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;

int n;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int weight[MAXN << 1];

int cnt;

int dist[MAXN];

// 直径的长度
int diameter;

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	memset(dist + 1, 0, n * sizeof(int));
	diameter = INT_MIN;
}

void addEdge(int u, int v, int w) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt++;
}

void dp(int u, int f) {
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			dp(v, u);
		}
	}
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			// 干脆直接去更新diameter
			diameter = max(diameter, dist[u] + dist[v] + weight[e]);
			dist[u] = max(dist[u], dist[v] + weight[e]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	build();
	for (int i = 1, u, v, w; i < n; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	dp(1, 0);
	cout << diameter << "\n";
	return 0;
}
