// 所有直径的公共部分(迭代版)
// 给定一棵树，边权都为正
// 打印直径长度、所有直径的公共部分有几条边
// 测试链接 : https://www.luogu.com.cn/problem/P3304
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

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

// dfs方法改迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
int ufeStack[MAXN][3];

long long distStack[MAXN];

int stackSize;

int u, f, e;

long long c;

void push(int u, int f, int e, long long c) {
	ufeStack[stackSize][0] = u;
	ufeStack[stackSize][1] = f;
	ufeStack[stackSize][2] = e;
	distStack[stackSize] = c;
	stackSize++;
}

void pop() {
	--stackSize;
	u = ufeStack[stackSize][0];
	f = ufeStack[stackSize][1];
	e = ufeStack[stackSize][2];
	c = distStack[stackSize];
}

void dfs(int root) {
	stackSize = 0;
	push(root, 0, -1, 0);
	while (stackSize > 0) {
		pop();
		if (e == -1) {
			last[u] = f;
			dist[u] = c;
			e = head[u];
		} else {
			e = nxt[e];
		}
		if (e != 0) {
			push(u, f, e, c);
			if (to[e] != f) {
				push(to[e], u, -1, c + weight[e]);
			}
		}
	}
}

void road() {
	dfs(1);
	start = 1;
	for (int i = 2; i <= n; i++) {
		if (dist[i] > dist[start]) {
			start = i;
		}
	}
	dfs(start);
	fin = 1;
	for (int i = 2; i <= n; i++) {
		if (dist[i] > dist[fin]) {
			fin = i;
		}
	}
	diameter = dist[fin];
}

// maxDistanceExceptDiameter方法改迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
long long maxDistanceExceptDiameter(int root) {
	stackSize = 0;
	push(root, 0, -1, 0);
	long long ans = 0;
	while (stackSize > 0) {
		pop();
		if (e == -1) {
			e = head[u];
		} else {
			e = nxt[e];
		}
		int v;
		if (e != 0) {
			push(u, f, e, c);
			v = to[e];
			if (!diameterPath[v] && v != f) {
				push(v, u, -1, c + weight[e]);
			}
		} else {
			ans = max(ans, c);
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
		maxDist = maxDistanceExceptDiameter(i);
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
