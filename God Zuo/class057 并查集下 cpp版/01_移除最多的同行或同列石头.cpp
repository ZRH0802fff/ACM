// 移除最多的同行或同列石头 — LeetCode 947
// 石头同行或同列即可连通，每个连通分量保留1个，其余都可移除
// 答案 = n - 连通分量数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int father[MAXN];

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        int sets = n;
        for (int i = 0; i < n; i++) father[i] = i;

        auto find = [&](int i) {
            if (i != father[i]) father[i] = find(father[i]);
            return father[i];
        };

        auto unionSet = [&](int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx != fy) { father[fx] = fy; sets--; }
        };

        // 用 map 记录每行/列第一次遇到的石头
        unordered_map<int, int> rowFirst, colFirst;
        for (int i = 0; i < n; i++) {
            int r = stones[i][0], c = stones[i][1];
            if (rowFirst.count(r)) unionSet(i, rowFirst[r]);
            else rowFirst[r] = i;
            if (colFirst.count(c)) unionSet(i, colFirst[c]);
            else colFirst[c] = i;
        }
        return n - sets;
    }
};
