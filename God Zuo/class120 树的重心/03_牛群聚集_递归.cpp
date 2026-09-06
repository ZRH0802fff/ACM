// 牛群聚集(递归版)
// 一共有n个节点，编号1~n，每个点有牛的数量
// 一共有n-1条边把所有点连通起来形成一棵树，每条边有权值
// 想把所有的牛汇聚在一点，希望走过的总距离最小
// 返回总距离最小是多少
// 利用重心的性质：
// 树上的边权如果都>=0，不管边权怎么分布，所有节点都走向重心的总距离和最小
// 测试链接 : https://www.luogu.com.cn/problem/P2986
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code03_GreatCowGathering2文件

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int n;

// cow[i] : i号农场牛的数量
int cow[MAXN];

// 牛的总数
int cowSum;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int weight[MAXN << 1];

int cnt;

int best, center;

// size[i] : 从1号节点开始dfs的过程中，以i为头的子树，牛的总量
int size[MAXN];

// path[i] : 从重心节点开始dfs的过程中，从重心到达i节点，距离是多少
int path[MAXN];

void build() {
	cnt = 1;
	memset(head + 1, 0, n * sizeof(int));
	cowSum = 0;
	best = INT_MAX;
}

void addEdge(int u, int v, int w) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt++;
}

void findCenter(int u, int f) {
	size[u] = cow[u];
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			findCenter(v, u);
		}
	}
	// 如下代码是遍历完成后再做统计工作
	// 这个写法和之前的逻辑是一样的，为什么要拆开写？
	// 为了后续改迭代版方便
	int maxsub = 0;
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			size[u] += size[v];
			maxsub = max(maxsub, size[v]);
		}
	}
	maxsub = max(maxsub, cowSum - size[u]);
	if (maxsub < best) {
		best = maxsub;
		center = u;
	}
}

void setPath(int u, int f) {
	for (int e = head[u], v; e != 0; e = nxt[e]) {
		v = to[e];
		if (v != f) {
			path[v] = path[u] + weight[e];
			setPath(v, u);
		}
	}
}

long long compute() {
	for (int i = 1; i <= n; i++) {
		cowSum += cow[i];
	}
	findCenter(1, 0);
	path[center] = 0;
	setPath(center, 0);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += (long long)cow[i] * path[i];
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	build();
	for (int i = 1; i <= n; i++) {
		cin >> cow[i];
	}
	for (int i = 1, u, v, w; i < n; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	cout << compute() << "\n";
	return 0;
}
