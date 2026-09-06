// 平衡行为
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 返回重心点，返回重心点最大子树的节点数
// 树的重心第一种求解方式
// 以某个节点为根时，最大子树的节点数最少，那么这个节点是重心
// 测试链接 : http://poj.org/problem?id=1655
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20001;

int n;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int cnt;

int size[MAXN];

int center;

int best;

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	best = INT_MAX;
}

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

// 当前来到u节点，父亲节点是f
void dfs(int u, int f) {
	size[u] = 1;
	// 以当前节点u做根节点，最大的子树有多少节点
	int maxsub = 0;
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			dfs(v, u);
			size[u] += size[v];
			maxsub = max(maxsub, size[v]);
		}
	}
	maxsub = max(maxsub, n - size[u]);
	// 题目要求找到编号最小的重心
	if (maxsub < best || (maxsub == best && u < center)) {
		best = maxsub;
		center = u;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testCase;
	cin >> testCase;
	for (int t = 1; t <= testCase; t++) {
		cin >> n;
		build();
		for (int i = 1, u, v; i < n; i++) {
			cin >> u >> v;
			addEdge(u, v);
			addEdge(v, u);
		}
		dfs(1, 0);
		cout << center << " " << best << "\n";
	}
	return 0;
}
