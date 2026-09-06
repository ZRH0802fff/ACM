// 教父
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 返回所有重心点
// 树的重心第二种求解方式
// 以某个节点为根时，每颗子树的节点数不超过总节点数的一半，那么这个节点是重心
// 测试链接 : http://poj.org/problem?id=3107
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50001;

int n;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int cnt;

int size[MAXN];

int maxsub[MAXN];

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
}

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

void dfs(int u, int f) {
	size[u] = 1;
	maxsub[u] = 0;
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			dfs(v, u);
			size[u] += size[v];
			maxsub[u] = max(maxsub[u], size[v]);
		}
	}
	maxsub[u] = max(maxsub[u], n - size[u]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	build();
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(1, 0);
	int m = 0;
	int centers[2];
	for (int i = 1; i <= n; i++) {
		if (maxsub[i] <= n / 2) {
			centers[m++] = i;
		}
	}
	if (m == 1) {
		cout << centers[0] << "\n";
	} else { // m == 2
		cout << centers[0] << " " << centers[1] << "\n";
	}
	return 0;
}
