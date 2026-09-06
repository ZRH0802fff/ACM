// 树上倍增解法
// 测试链接 : https://www.luogu.com.cn/problem/P3379
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code02_Multiply2文件

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;

const int LIMIT = 20;

// 根据节点个数n，计算出2的几次方就够用了
int power;

int log2(int n) {
	int ans = 0;
	while ((1 << ans) <= (n >> 1)) {
		ans++;
	}
	return ans;
}

// 链式前向星建图
int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int cnt;

// deep[i] : 节点i在第几层
int deep[MAXN];

// stjump[i][p] : 节点i往上跳2的p次方步，到达的节点编号
int stjump[MAXN][LIMIT];

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

// dfs递归版
// 一般来说都这么写，但是本题附加的测试数据很毒
// java这么写就会因为递归太深而爆栈，c++这么写就能通过
void dfs(int u, int f) {
	deep[u] = deep[f] + 1;
	stjump[u][0] = f;
	for (int p = 1; p <= power; p++) {
		stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
	}
	for (int e = head[u]; e != 0; e = nxt[e]) {
		if (to[e] != f) {
			dfs(to[e], u);
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
	dfs(root, 0);
	for (int i = 1, a, b; i <= m; i++) {
		cin >> a >> b;
		cout << lca(a, b) << "\n";
	}
	return 0;
}
