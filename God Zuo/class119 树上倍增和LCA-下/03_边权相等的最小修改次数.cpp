// 边权相等的最小修改次数
// 一棵树有n个节点，编号0 ~ n-1，每条边(u,v,w)表示从u到v有一条权重为w的边
// 一共有m条查询，每条查询(a,b)表示，a到b的最短路径中把所有边变成一种值需要修改几条边
// 返回每条查询的查询结果
// 1 <= n <= 10^4
// 1 <= m <= 2 * 10^4
// 0 <= u、v、a、b < n
// 1 <= w <= 26
// 测试链接 : https://leetcode.cn/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10001;

const int MAXM = 20001;

const int MAXW = 26;

// 链式前向星建图
int headEdge[MAXN];

int edgeNext[MAXN << 1];

int edgeTo[MAXN << 1];

int edgeValue[MAXN << 1];

int tcnt;

// weightCnt[i][w] : 从头节点到i的路径中，权值为w的边有几条
int weightCnt[MAXN][MAXW + 1];

// 以下所有的结构都是为了tarjan算法做准备
int headQuery[MAXN];

int queryNext[MAXM << 1];

int queryTo[MAXM << 1];

int queryIndex[MAXM << 1];

int qcnt;

bool visited[MAXN];

int father[MAXN];

int lca[MAXM];

void build(int n) {
	tcnt = qcnt = 1;
	memset(headEdge, 0, n * sizeof(int));
	memset(headQuery, 0, n * sizeof(int));
	memset(visited, 0, n * sizeof(bool));
	for (int i = 0; i < n; i++) {
		father[i] = i;
	}
}

void addEdge(int u, int v, int w) {
	edgeNext[tcnt] = headEdge[u];
	edgeTo[tcnt] = v;
	edgeValue[tcnt] = w;
	headEdge[u] = tcnt++;
}

// 当前来到u节点，父亲节点f，从f到u权重为w
// 统计从头节点到u节点，每种权值的边有多少条
// 信息存放在weightCnt[u][1..26]里
void dfs(int u, int w, int f) {
	if (u == 0) {
		memset(weightCnt[u], 0, sizeof(weightCnt[u]));
	} else {
		for (int i = 1; i <= MAXW; i++) {
			weightCnt[u][i] = weightCnt[f][i];
		}
		weightCnt[u][w]++;
	}
	for (int e = headEdge[u]; e != 0; e = edgeNext[e]) {
		if (edgeTo[e] != f) {
			dfs(edgeTo[e], edgeValue[e], u);
		}
	}
}

void addQuery(int u, int v, int i) {
	queryNext[qcnt] = headQuery[u];
	queryTo[qcnt] = v;
	queryIndex[qcnt] = i;
	headQuery[u] = qcnt++;
}

int find(int i) {
	if (i != father[i]) {
		father[i] = find(father[i]);
	}
	return father[i];
}

// tarjan算法批量查询两点的最低公共祖先
void tarjan(int u, int f) {
	visited[u] = true;
	for (int e = headEdge[u]; e != 0; e = edgeNext[e]) {
		if (edgeTo[e] != f) {
			tarjan(edgeTo[e], u);
		}
	}
	for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
		v = queryTo[e];
		if (visited[v]) {
			lca[queryIndex[e]] = find(v);
		}
	}
	father[u] = f;
}

class Solution {
public:
	vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
		build(n);
		for (auto& edge : edges) {
			addEdge(edge[0], edge[1], edge[2]);
			addEdge(edge[1], edge[0], edge[2]);
		}
		// 从头节点到每个节点的边权值词频统计
		dfs(0, 0, -1);
		int m = queries.size();
		for (int i = 0; i < m; i++) {
			addQuery(queries[i][0], queries[i][1], i);
			addQuery(queries[i][1], queries[i][0], i);
		}
		// 得到每个查询的最低公共祖先
		tarjan(0, -1);
		vector<int> ans(m);
		for (int i = 0, a, b, c; i < m; i++) {
			a = queries[i][0];
			b = queries[i][1];
			c = lca[i];
			int allCnt = 0; // 从a到b的路，所有权值的边一共多少条
			int maxCnt = 0; // 从a到b的路，权值重复最多的次数
			for (int w = 1, wcnt; w <= MAXW; w++) { // 所有权值枚举一遍
				wcnt = weightCnt[a][w] + weightCnt[b][w] - 2 * weightCnt[c][w];
				maxCnt = max(maxCnt, wcnt);
				allCnt += wcnt;
			}
			ans[i] = allCnt - maxCnt;
		}
		return ans;
	}
};

int main() {
	Solution sol;
	int n = 4;
	vector<vector<int>> edges = { {0, 1, 1}, {1, 2, 1}, {1, 3, 2} };
	vector<vector<int>> queries = { {2, 3}, {0, 2} };
	vector<int> ans = sol.minOperationsQueries(n, edges, queries);
	for (int x : ans) {
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}
