// 检查树上两节点间的路径是否是回文
// 一颗树上有n个节点，编号1~n
// 给定长度为n的数组parent, parent[i]表示节点i的父节点编号
// 给定长度为n的数组s, s[i]表示节点i上是什么字符
// 从节点a到节点b经过节点最少的路，叫做a和b的路径
// 一共有m条查询，每条查询(a,b)，a和b的路径字符串是否是回文
// 是回文打印"YES"，不是回文打印"NO"
// 1 <= n <= 10^5
// 1 <= m <= 10^5
// parent[1] = 0，即整棵树的头节点一定是1号节点
// 每个节点上的字符一定是小写字母a~z
// 测试链接 : https://ac.nowcoder.com/acm/contest/78807/G
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

const int LIMIT = 17;

int power;

int s[MAXN];

int head[MAXN];

int to[MAXN << 1];

int nxt[MAXN << 1];

int cnt;

int deep[MAXN];

int jump[MAXN][LIMIT];

const long long K = 499;

// kpow[i] = k的i次方
long long kpow[MAXN];

long long stup[MAXN][LIMIT];

long long stdown[MAXN][LIMIT];

int log2(int n) {
	int ans = 0;
	while ((1 << ans) <= (n >> 1)) {
		ans++;
	}
	return ans;
}

void build(int n) {
	power = log2(n);
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	kpow[0] = 1;
	for (int i = 1; i <= n; i++) {
		kpow[i] = kpow[i - 1] * K;
	}
}

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

void dfs(int u, int f) {
	deep[u] = deep[f] + 1;
	jump[u][0] = f;
	stup[u][0] = stdown[u][0] = s[f];
	for (int p = 1, v; p <= power; p++) {
		v = jump[u][p - 1];
		jump[u][p] = jump[v][p - 1];
		stup[u][p] = stup[u][p - 1] * kpow[1 << (p - 1)] + stup[v][p - 1];
		stdown[u][p] = stdown[v][p - 1] * kpow[1 << (p - 1)] + stdown[u][p - 1];
	}
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			dfs(v, u);
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
		if (deep[jump[a][p]] >= deep[b]) {
			a = jump[a][p];
		}
	}
	if (a == b) {
		return a;
	}
	for (int p = power; p >= 0; p--) {
		if (jump[a][p] != jump[b][p]) {
			a = jump[a][p];
			b = jump[b][p];
		}
	}
	return jump[a][0];
}

long long calcHash(int from, int anc, int to) {
	// up是上坡hash值
	long long up = s[from];
	for (int p = power; p >= 0; p--) {
		if (deep[jump[from][p]] >= deep[anc]) {
			up = up * kpow[1 << p] + stup[from][p];
			from = jump[from][p];
		}
	}
	if (to == anc) {
		return up;
	}
	// down是下坡hash值
	long long down = s[to];
	// height是目前下坡的总高度
	int height = 1;
	for (int p = power; p >= 0; p--) {
		if (deep[jump[to][p]] > deep[anc]) {
			down = stdown[to][p] * kpow[height] + down;
			height += 1 << p;
			to = jump[to][p];
		}
	}
	return up * kpow[height] + down;
}

bool isPalindrome(int a, int b) {
	int anc = lca(a, b);
	long long hash1 = calcHash(a, anc, b);
	long long hash2 = calcHash(b, anc, a);
	return hash1 == hash2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	build(n);
	string str;
	cin >> str;
	int si = 1;
	for (char c : str) {
		s[si++] = c - 'a' + 1;
	}
	for (int u = 1, v; u <= n; u++) {
		cin >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(1, 0);
	int m;
	cin >> m;
	for (int i = 1, a, b; i <= m; i++) {
		cin >> a >> b;
		cout << (isPalindrome(a, b) ? "YES" : "NO") << "\n";
	}
	return 0;
}
