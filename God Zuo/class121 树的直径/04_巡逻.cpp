// 巡逻
// 一共n个节点，编号1~n，结构是一棵树，每条边都是双向的
// 警察局在1号点，警车每天从1号点出发，一定要走过树上所有的边，最后回到1号点
// 现在为了减少经过边的数量，你可以新建k条边，把树上任意两点直接相连
// 并且每天警车必须经过新建的道路正好一次
// 计算出最佳的新建道路的方案，返回巡逻走边数量的最小值
// 测试链接 : https://www.luogu.com.cn/problem/P3629
// 1 <= n <= 10^5
// 1 <= k <= 2
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int n;

int k;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int cnt;

int start;

int fin;

int dist[MAXN];

int last[MAXN];

int diameter1;

int diameter2;

bool diameterPath[MAXN];

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	diameter1 = 0;
	diameter2 = 0;
	memset(diameterPath + 1, 0, (n - 1) * sizeof(bool));
}

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

void dfs(int u, int f, int w) {
	last[u] = f;
	dist[u] = dist[f] + w;
	for (int e = head[u]; e != 0; e = nxt[e]) {
		if (to[e] != f) {
			dfs(to[e], u, 1);
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
	diameter1 = dist[fin];
}

// 树型dp第二次求直径长度
void dp(int u, int f) {
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			dp(v, u);
		}
	}
	for (int e = head[u], v, w; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			w = diameterPath[u] && diameterPath[v] ? -1 : 1;
			diameter2 = max(diameter2, dist[u] + dist[v] + w);
			dist[u] = max(dist[u], dist[v] + w);
		}
	}
}

int compute() {
	road();
	if (k == 1) {
		return 2 * (n - 1) - diameter1 + 1;
	} else {
		for (int i = fin; i != 0; i = last[i]) {
			diameterPath[i] = true;
		}
		memset(dist + 1, 0, n * sizeof(int));
		dp(1, 0);
		return 2 * (n - 1) - diameter1 - diameter2 + 2;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	build();
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	cout << compute() << "\n";
	return 0;
}
