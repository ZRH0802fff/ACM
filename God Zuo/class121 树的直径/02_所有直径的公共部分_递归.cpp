// 所有直径的公共部分(递归版)
// 给定一棵树，边权都为正
// 打印直径长度、所有直径的公共部分有几条边
// 测试链接 : https://www.luogu.com.cn/problem/P3304
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code02_DiameterAndCommonEdges2文件

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

int n;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int weight[MAXN << 1];

int cnt;

int start;

int fin;

long long dist[MAXN];

int last[MAXN];

long long diameter;

bool diameterPath[MAXN];

int commonEdges;

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	memset(diameterPath + 1, 0, n * sizeof(bool));
}

void addEdge(int u, int v, int w) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt++;
}

void dfs(int u, int f, long long c) {
	last[u] = f;
	dist[u] = c;
	for (int e = head[u]; e != 0; e = nxt[e]) {
		if (to[e] != f) {
			dfs(to[e], u, c + weight[e]);
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

// 不能走向直径路径上的节点
// 能走出的最大距离
long long maxDistanceExceptDiameter(int u, int f, long long c) {
	long long ans = c;
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (!diameterPath[v] && v != f) {
			ans = max(ans, maxDistanceExceptDiameter(v, u, c + weight[e]));
		}
	}
	return ans;
}

void compute() {
	road();
	for (int i = fin; i != 0; i = last[i]) {
		diameterPath[i] = true;
	}
	int l = start;
	int r = fin;
	long long maxDist;
	for (int i = last[fin]; i != start; i = last[i]) {
		maxDist = maxDistanceExceptDiameter(i, 0, 0);
		if (maxDist == diameter - dist[i]) {
			r = i;
		}
		if (maxDist == dist[i] && l == start) {
			l = i;
		}
	}
	if (l == r) {
		commonEdges = 0;
	} else {
		commonEdges = 1;
		for (int i = last[r]; i != l; i = last[i]) {
			commonEdges++;
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
	compute();
	cout << diameter << "\n";
	cout << commonEdges << "\n";
	return 0;
}
