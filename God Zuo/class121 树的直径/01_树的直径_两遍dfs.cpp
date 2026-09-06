// 树的直径模版(两遍dfs)
// 给定一棵树，边权可能为负，求直径长度
// 测试链接 : https://www.luogu.com.cn/problem/U81904
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 会有无法通过的用例，因为树上有负边

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;

int n;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int weight[MAXN << 1];

int cnt;

// 直径的开始点
int start;

// 直径的结束点
int fin;

// 直径长度
int diameter;

// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];

// last[i] : 从规定的头节点出发，i节点的上一个节点
int last[MAXN];

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
}

void addEdge(int u, int v, int w) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt++;
}

void dfs(int u, int f, int w) {
	last[u] = f;
	dist[u] = dist[f] + w;
	for (int e = head[u]; e != 0; e = nxt[e]) {
		if (to[e] != f) {
			dfs(to[e], u, weight[e]);
		}
	}
}

void road() {
	dfs(1, 0, 0);
	start = 1;
	for (int i = 2; i <= n; i++) {
		if (dist[i] > dist[start]) {
			start = i;
		}
	}
	dfs(start, 0, 0);
	fin = 1;
	for (int i = 2; i <= n; i++) {
		if (dist[i] > dist[fin]) {
			fin = i;
		}
	}
	diameter = dist[fin];
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
	road();
	cout << diameter << "\n";
	return 0;
}
