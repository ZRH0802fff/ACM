// 树节点的第K个祖先
// 树上有n个节点，编号0 ~ n-1，树的结构用parent数组代表
// 其中parent[i]是节点i的父节点，树的根节点是编号为0
// 树节点i的第k个祖先节点，是从节点i开始往上跳k步所来到的节点
// 实现TreeAncestor类
// TreeAncestor(int n, int[] parent) : 初始化
// getKthAncestor(int i, int k) : 返回节点i的第k个祖先节点，不存在返回-1
// 测试链接 : https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50001;

const int LIMIT = 16;

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

int nxt[MAXN];

int to[MAXN];

int cnt;

// deep[i] : 节点i在第几层
int deep[MAXN];

// stjump[i][p] : 节点i往上跳2的p次方步，到达的节点编号
int stjump[MAXN][LIMIT];

void addEdge(int u, int v) {
	nxt[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt++;
}

// 当前来到i节点，i节点父亲节点是f
void dfs(int i, int f) {
	if (i == 0) {
		deep[i] = 1;
	} else {
		deep[i] = deep[f] + 1;
	}
	stjump[i][0] = f;
	for (int p = 1; p <= power; p++) {
		stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
	}
	for (int e = head[i]; e != 0; e = nxt[e]) {
		dfs(to[e], i);
	}
}

class TreeAncestor {
public:
	TreeAncestor(int n, vector<int>& parent) {
		power = log2(n);
		cnt = 1;
		memset(head, 0, n * sizeof(int));
		for (int i = 1; i < (int)parent.size(); i++) {
			addEdge(parent[i], i);
		}
		dfs(0, 0);
	}

	int getKthAncestor(int i, int k) { 
		if (deep[i] <= k) {
			return -1;
		}
		// s是想要去往的层数
		int s = deep[i] - k;
		for (int p = power; p >= 0; p--) {
			if (deep[stjump[i][p]] >= s) {
				i = stjump[i][p];
			}
		}
		return i;
	}
};

int main() {
	vector<int> parent = { -1, 0, 0, 1, 1, 2, 2 };
	TreeAncestor ta(7, parent);
	cout << ta.getKthAncestor(3, 1) << "\n"; // 1
	cout << ta.getKthAncestor(5, 2) << "\n"; // 0
	cout << ta.getKthAncestor(6, 3) << "\n"; // -1
	return 0;
}
