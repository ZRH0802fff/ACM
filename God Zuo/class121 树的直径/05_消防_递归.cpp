// 消防(递归版)
// 一共n个节点，编号1~n，有n-1条边连接成一棵树，每条边上有非负权值
// 给定一个非负整数s，表示可以在树上选择一条长度不超过s的路径
// 然后在这条路径的点上建立消防站，每个居民可以去往这条路径上的任何消防站
// 目标：哪怕最远的居民走到消防站的距离也要尽量少
// 返回最远居民走到消防站的最短距离
// 测试链接 : https://www.luogu.com.cn/problem/P2491
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code05_FireFighting2文件

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300001;

int n;

int s;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int weight[MAXN << 1];

int cnt;

int start;

int fin;

int diameter;

int dist[MAXN];

int last[MAXN];

// pred[i] : i节点在直径上，和前一个点之间的距离，以start做根
int pred[MAXN];

bool diameterPath[MAXN];

int maxDist[MAXN];

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	memset(diameterPath + 1, 0, (n - 1) * sizeof(bool));
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
	pred[u] = w;
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

// 不能走向直径路径上的节点
// 能走出的最大距离
int maxDistanceExceptDiameter(int u, int f, int c) {
	int ans = c;
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (!diameterPath[v] && v != f) {
			ans = max(ans, maxDistanceExceptDiameter(v, u, c + weight[e]));
		}
	}
	return ans;
}

void distance() {
	for (int i = fin; i != 0; i = last[i]) {
		diameterPath[i] = true;
	}
	for (int i = fin; i != 0; i = last[i]) {
		maxDist[i] = maxDistanceExceptDiameter(i, 0, 0);
	}
}

// 单调队列维护窗口内最大值
// 不会的看讲解054
int que[MAXN];

int compute() {
	int suml = 0, sumr = 0;
	// 用h和t表示单调队列的头和尾
	int h = 0, t = 0;
	int ans = INT_MAX;
	// 窗口范围[l,r)，左闭右开，直径上的窗口[l...r-1]
	// l是窗口左端点，r是窗口右端点的再下一个点
	// 课上图解是从start到end，实际是从end到start，思路没有区别
	for (int l = fin, r = fin; l != 0; l = last[l]) {
		while (r != 0 && sumr - suml + pred[r] <= s) {
			while (h < t && maxDist[que[t - 1]] <= maxDist[r]) {
				t--;
			}
			sumr += pred[r];
			que[t++] = r;
			r = last[r];
		}
		ans = min(ans, max(max(suml, maxDist[que[h]]), diameter - sumr));
		if (que[h] == l) {
			h++;
		}
		suml += pred[l];
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> s;
	build();
	for (int i = 1, u, v, w; i < n; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	road();
	distance();
	cout << compute() << "\n";
	return 0;
}
