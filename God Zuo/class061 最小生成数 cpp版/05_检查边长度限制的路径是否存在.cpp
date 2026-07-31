// 检查边长度限制的路径是否存在
// 给你一个 n 个点组成的无向图边集 edgeList
// 其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边
// 请注意，两个点之间可能有 超过一条边 。
// 给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj]
// 你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径
// 且这条路径上的每一条边都 严格小于 limitj 。
// 请你返回一个 布尔数组 answer ，其中 answer.length == queries.length
// 当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false
// 测试链接 : https://leetcode.cn/problems/checking-existence-of-edge-length-limited-paths/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

struct Edge {
    int u, v, w;
};

struct Question {
    int u, v, limit, idx;
};

Question questions[MAXN];
int father[MAXN];

void build(int n) {
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

bool isSameSet(int x, int y) {
    return find(x) == find(y);
}

void unionSet(int x, int y) {
    father[find(x)] = find(y);
}

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int m = edgeList.size();
        int k = queries.size();
        // 将edges转为struct数组以便排序
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++) {
            edges[i].u = edgeList[i][0];
            edges[i].v = edgeList[i][1];
            edges[i].w = edgeList[i][2];
        }
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });
        for (int i = 0; i < k; i++) {
            questions[i].u = queries[i][0];
            questions[i].v = queries[i][1];
            questions[i].limit = queries[i][2];
            questions[i].idx = i;
        }
        sort(questions, questions + k, [](const Question& a, const Question& b) {
            return a.limit < b.limit;
        });
        build(n);
        vector<bool> ans(k);
        for (int i = 0, j = 0; i < k; i++) {
            // i : 问题编号
            // j : 边的编号
            for (; j < m && edges[j].w < questions[i].limit; j++) {
                unionSet(edges[j].u, edges[j].v);
            }
            ans[questions[i].idx] = isSameSet(questions[i].u, questions[i].v);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    // 示例: n=3, edges=[[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries=[[0,1,2],[0,2,5]]
    vector<vector<int>> edges = {{0,1,2},{1,2,4},{2,0,8},{1,0,16}};
    vector<vector<int>> queries = {{0,1,2},{0,2,5}};
    vector<bool> res = sol.distanceLimitedPathsExist(3, edges, queries);
    cout << "results: ";
    for (bool b : res) cout << (b ? "true" : "false") << " ";
    cout << "(expected: false true)" << endl;
    return 0;
}
