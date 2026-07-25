// 情侣牵手 — LeetCode 765
// row 是 0..2n-1 的排列，每对情侣编号为 (2k, 2k+1)
// 求最少交换次数让每对情侣相邻

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;
int father[MAXN];

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size(), couples = n / 2;
        int sets = couples;
        for (int i = 0; i < couples; i++) father[i] = i;

        auto find = [&](int i) {
            if (i != father[i]) father[i] = find(father[i]);
            return father[i];
        };

        auto unionSet = [&](int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx != fy) { father[fx] = fy; sets--; }
        };

        for (int i = 0; i < n; i += 2)
            unionSet(row[i] / 2, row[i + 1] / 2);

        return couples - sets;
    }
};
