// tarjan算法解法
// 测试链接 : https://www.luogu.com.cn/problem/P3379
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code03_Tarjan2文件

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;

// 链式前向星建图
int headEdge[MAXN];

int edgeNext[MAXN << 1];

int edgeTo[MAXN << 1];

int tcnt;

// 每个节点有哪些查询，也用链式前向星方式存储
int headQuery[MAXN];

int queryNext[MAXN << 1];

int queryTo[MAXN << 1];

// 问题的编号，一旦有答案可以知道填写在哪
int queryIndex[MAXN << 1];

int qcnt;

// 某个节点是否访问过
bool visited[MAXN];

// 并查集
int father[MAXN];

// 收集的答案
int ans[MAXN];

void build(int n) {
	tcnt = qcnt = 1;
	memset(headEdge + 1, 0, n * sizeof(int));
	memset(headQuery + 1, 0, n * sizeof(int));
	memset(visited + 1, 0, n * sizeof(bool));
	for (int i = 1; i <= n; i++) {
		father[i] = i;
	}
}

void addEdge(int u, int v) {
	edgeNext[tcnt] = headEdge[u];
	edgeTo[tcnt] = v;
	headEdge[u] = tcnt++;
}

void addQuery(int u, int v, int i) {
	queryNext[qcnt] = headQuery[u];
	queryTo[qcnt] = v;
	queryIndex[qcnt] = i;
	headQuery[u] = qcnt++;
}

// 并查集找头节点递归版
// 一般来说都这么写，但是本题附加的测试数据很毒
// java这么写就会因为递归太深而爆栈，C++这么写就能通过
int find(int i) {
	if (i != father[i]) {
		father[i] = find(father[i]);
	}
	return father[i];
}

// tarjan算法递归版
// 一般来说都这么写，但是本题附加的测试数据很毒
// java这么写就会因为递归太深而爆栈，C++这么写就能通过
void tarjan(int u, int f) {
	visited[u] = true;
	for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
		v = edgeTo[e];
		if (v != f) {
			tarjan(v, u);
			father[v] = u;
		}
	}
	for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
		v = queryTo[e];
		if (visited[v]) {
			ans[queryIndex[e]] = find(v);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, root;
	cin >> n >> m >> root;
	build(n);
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		addQuery(u, v, i);
		addQuery(v, u, i);
	}
	tarjan(root, 0);
	for (int i = 1; i <= m; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}
