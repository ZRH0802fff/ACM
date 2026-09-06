// tarjan算法解法迭代版
// 测试链接 : https://www.luogu.com.cn/problem/P3379
// 所有递归函数一律改成等义的迭代版
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;

int headEdge[MAXN];

int edgeNext[MAXN << 1];

int edgeTo[MAXN << 1];

int tcnt;

int headQuery[MAXN];

int queryNext[MAXN << 1];

int queryTo[MAXN << 1];

int queryIndex[MAXN << 1];

int qcnt;

bool visited[MAXN];

int father[MAXN];

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

// 为了实现迭代版而准备的栈
int stk[MAXN];

// 并查集找头节点迭代版
int find(int i) {
	int size = 0;
	while (i != father[i]) {
		stk[size++] = i;
		i = father[i];
	}
	while (size > 0) {
		father[stk[--size]] = i;
	}
	return i;
}

// 为了实现迭代版而准备的栈
int ufe[MAXN][3];

int stackSize, u, f, e;

void push(int u, int f, int e) {
	ufe[stackSize][0] = u;
	ufe[stackSize][1] = f;
	ufe[stackSize][2] = e;
	stackSize++;
}

void pop() {
	--stackSize;
	u = ufe[stackSize][0];
	f = ufe[stackSize][1];
	e = ufe[stackSize][2];
}

// 为了容易改成迭代版，修改一下递归版
void tarjan(int u, int f) {
	visited[u] = true;
	for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
		v = edgeTo[e];
		if (v != f) {
			tarjan(v, u);
			// 注意这里，注释了一行
//			father[v] = u;
		}
	}
	for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
		v = queryTo[e];
		if (visited[v]) {
			ans[queryIndex[e]] = find(v);
		}
	}
	// 注意这里，增加了一行
	father[u] = f;
}

// tarjan算法迭代版，根据上面的递归版改写
void tarjan(int root) {
	stackSize = 0;
	// 栈里存放三个信息
	// u : 当前处理的点
	// f : 当前点u的父节点
	// e : 处理到几号边了
	// 如果e==-1，表示之前没有处理过u的任何边
	// 如果e==0，表示u的边都已经处理完了
	push(root, 0, -1);
	while (stackSize > 0) {
		pop();
		if (e == -1) {
			visited[u] = true;
			e = headEdge[u];
		} else {
			e = edgeNext[e];
		}
		if (e != 0) {
			push(u, f, e);
			if (edgeTo[e] != f) {
				push(edgeTo[e], u, -1);
			}
		} else {
			// e == 0代表u后续已经没有边需要处理了
			for (int q = headQuery[u], v; q != 0; q = queryNext[q]) {
				v = queryTo[q];
				if (visited[v]) {
					ans[queryIndex[q]] = find(v);
				}
			}
			father[u] = f;
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
	tarjan(root);
	for (int i = 1; i <= m; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}
