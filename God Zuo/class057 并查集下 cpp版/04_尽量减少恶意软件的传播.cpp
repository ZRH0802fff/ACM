// 尽量减少恶意软件的传播 — LeetCode 924
// 并查集只在非病毒节点间建图，统计每个病毒"独家"影响的连通分量大小

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
int father[MAXN], sz[MAXN];
int infect[MAXN]; // -1=安全, >=0=唯一感染源, -2=多个感染源
int cnts[MAXN];

class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        unordered_set<int> virusSet(initial.begin(), initial.end());
        for (int i = 0; i < n; i++) father[i] = i, sz[i] = 1;

        auto find = [&](int i) {
            while (i != father[i]) {
                father[i] = father[father[i]];
                i = father[i];
            }
            return i;
        };

        auto unionSet = [&](int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx != fy) { father[fx] = fy; sz[fy] += sz[fx]; }
        };

        // 只让非病毒节点连通
        for (int i = 0; i < n; i++) {
            if (virusSet.count(i)) continue;
            for (int j = i + 1; j < n; j++) {
                if (!virusSet.count(j) && graph[i][j] == 1)
                    unionSet(i, j);
            }
        }

        memset(infect, -1, sizeof(infect));
        memset(cnts, 0, sizeof(cnts));

        for (int sick : initial) {
            for (int nb = 0; nb < n; nb++) {
                if (!virusSet.count(nb) && graph[sick][nb] == 1) {
                    int fn = find(nb);
                    if (infect[fn] == -1) infect[fn] = sick;
                    else if (infect[fn] != -2 && infect[fn] != sick) infect[fn] = -2;
                }
            }
        }

        for (int i = 0; i < n; i++)
            if (i == father[i] && infect[i] >= 0)
                cnts[infect[i]] += sz[i];

        sort(initial.begin(), initial.end());
        int ans = initial[0];
        for (int v : initial)
            if (cnts[v] > cnts[ans]) ans = v;
        return ans;
    }
};
