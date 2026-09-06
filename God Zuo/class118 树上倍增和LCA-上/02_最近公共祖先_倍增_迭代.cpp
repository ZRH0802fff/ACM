// 树上倍增解法迭代版
// 测试链接 : https://www.luogu.com.cn/problem/P3379
// 所有递归函数一律改成等义的迭代版
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;

const int LIMIT = 20;

int power;

int log2(int n) {
	int ans = 0;
	while ((1 << ans) <= (n >> 1)) {
		ans++;
	}
	return ans;
}

int cnt;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int stjump[MAXN][LIMIT];

int deep[MAXN];

void build(int n) {
	power = log2(n);
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
}

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

// dfs迭代版
// ufe是为了实现迭代版而准备的栈
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

void dfs(int root) {
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
			deep[u] = deep[f] + 1;
			stjump[u][0] = f;
			for (int p = 1; p <= power; p++) {
				stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
			}
			e = head[u];
		} else {
			e = nxt[e];
		}
		if (e != 0) {
			push(u, f, e);
			if (to[e] != f) {
				push(to[e], u, -1);
			}
		}
	}
}

int lca(int a, int b) {
	if (deep[a] < deep[b]) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	for (int p = power; p >= 0; p--) {
		if (deep[stjump[a][p]] >= deep[b]) {
			a = stjump[a][p];
		}
	}
	if (a == b) {
		return a;
	}
	for (int p = power; p >= 0; p--) {
		if (stjump[a][p] != stjump[b][p]) {
			a = stjump[a][p];
			b = stjump[b][p];
		}
	}
	return stjump[a][0];
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
	dfs(root);
	for (int i = 1, a, b; i <= m; i++) {
		cin >> a >> b;
		cout << lca(a, b) << "\n";
	}
	return 0;
}
