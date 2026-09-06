// 删增边使其重心唯一
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 现在希望重心是唯一的节点，调整的方式是先删除一条边、然后增加一条边
// 如果树上只有一个重心，需要删掉连接重心的任意一条边，再把这条边加上(否则无法通过已经实测)
// 如果树上有两个重心，调整的方式是先删除一条边、然后增加一条边，使重心是唯一的
// 如果方案有多种，打印其中一种即可
// 比如先删除节点3和节点4之间的边，再增加节点4和节点7之间的边，那么打印:
// "3 4"
// "4 7"
// 测试链接 : https://www.luogu.com.cn/problem/CF1406C
// 测试链接 : https://codeforces.com/problemset/problem/1406/C
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int n;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int cnt;

// size[i] : 从1号节点开始dfs的过程中，以i为头的子树的节点数
int size[MAXN];

// maxsub[i] : 如果节点i做整棵树的根，最大子树的大小
int maxsub[MAXN];

// 收集所有的重心
int centers[2];

// 最大子树上的叶节点
int leaf;

// 叶节点的父亲节点
int leafFather;

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

// 随意找一个叶节点和该叶节点的父亲节点
// 哪一组都可以
void find(int u, int f) {
	for (int e = head[u]; e != 0; e = nxt[e]) {
		if (to[e] != f) {
			find(to[e], u);
			return;
		}
	}
	leaf = u;
	leafFather = f;
}

// 返回重心的数量
int centerCnt() {
	int m = 0;
	for (int i = 1; i <= n; i++) {
		if (maxsub[i] <= n / 2) {
			centers[m++] = i;
		}
	}
	return m;
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
		if (centerCnt() == 1) {
			cout << centers[0] << " " << to[head[centers[0]]] << "\n";
			cout << centers[0] << " " << to[head[centers[0]]] << "\n";
		} else {
			find(centers[1], centers[0]);
			cout << leafFather << " " << leaf << "\n";
			cout << centers[0] << " " << leaf << "\n";
		}
	}
	return 0;
}
