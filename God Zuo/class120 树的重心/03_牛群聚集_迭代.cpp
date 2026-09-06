// 牛群聚集(迭代版)
// 一共有n个节点，编号1~n，每个点有牛的数量
// 一共有n-1条边把所有点连通起来形成一棵树，每条边有权值
// 想把所有的牛汇聚在一点，希望走过的总距离最小
// 返回总距离最小是多少
// 利用重心的性质：
// 树上的边权如果都>=0，不管边权怎么分布，所有节点都走向重心的总距离和最小
// 测试链接 : https://www.luogu.com.cn/problem/P2986
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int n;

int cow[MAXN];

int cowSum;

int head[MAXN];

int nxt[MAXN << 1];

int to[MAXN << 1];

int weight[MAXN << 1];

int cnt;

int best, center;

int size[MAXN];

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

// 迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
void findCenter(int root) {
	stackSize = 0;
	push(root, 0, -1);
	while (stackSize > 0) {
		pop();
		if (e == -1) { // 如果第一次来到当前节点u
			size[u] = cow[u];
			e = head[u];
		} else { // 如果不是第一次来到当前节点u
			e = nxt[e];
		}
		if (e != 0) { // 如果还有后续边、还有后续子节点
			push(u, f, e);
			if (to[e] != f) {
				push(to[e], u, -1);
			}
		} else { // 如果没有后续边了，那么就做最后的统计工作
			int maxsub = 0;
			for (int i = head[u], v; i != 0; i = nxt[i]) {
				v = to[i];
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
	}
}

// 迭代版
// 不会改，看讲解118，讲了怎么从递归版改成迭代版
void setPath(int root) {
	stackSize = 0;
	push(root, 0, -1);
	while (stackSize > 0) {
		pop();
		if (e == -1) {
			e = head[u];
		} else {
			e = nxt[e];
		}
		if (e != 0) {
			push(u, f, e);
			int v = to[e];
			if (v != f) {
				path[v] = path[u] + weight[e];
				push(v, u, -1);
			}
		}
	}
}

long long compute() {
	for (int i = 1; i <= n; i++) {
		cowSum += cow[i];
	}
	findCenter(1);
	path[center] = 0;
	setPath(center);
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
