// 消防(迭代版)
// 一共n个节点，编号1~n，有n-1条边连接成一棵树，每条边上有非负权值
// 给定一个非负整数s，表示可以在树上选择一条长度不超过s的路径
// 然后在这条路径的点上建立消防站，每个居民可以去往这条路径上的任何消防站
// 目标：哪怕最远的居民走到消防站的距离也要尽量少
// 返回最远居民走到消防站的最短距离
// 测试链接 : https://www.luogu.com.cn/problem/P2491
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

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

// dfs方法改迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
int ufwe[MAXN][4];

int stackSize;

int u, f, w, e;

void push(int u, int f, int w, int e) {
	ufwe[stackSize][0] = u;
	ufwe[stackSize][1] = f;
	ufwe[stackSize][2] = w;
	ufwe[stackSize][3] = e;
	stackSize++;
}

void pop() {
	--stackSize;
	u = ufwe[stackSize][0];
	f = ufwe[stackSize][1];
	w = ufwe[stackSize][2];
	e = ufwe[stackSize][3];
}

void dfs(int root) {
	stackSize = 0;
	push(root, 0, 0, -1);
	while (stackSize > 0) {
		pop();
		if (e == -1) {
			last[u] = f;
			dist[u] = dist[f] + w;
			pred[u] = w;
			e = head[u];
		} else {
			e = nxt[e];
		}
		if (e != 0) {
			push(u, f, w, e);
			if (to[e] != f) {
				push(to[e], u, weight[e], -1);
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

// maxDistanceExceptDiameter方法不用改迭代居然能通过
// 那就不改了
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

int que[MAXN];

int compute() {
	int suml = 0, sumr = 0;
	int h = 0, t = 0;
	int ans = INT_MAX;
	for (int l = fin, r = fin; l != 0; l = last[l]) {
		while (r != 0 && sumr + pred[r] - suml <= s) {
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
