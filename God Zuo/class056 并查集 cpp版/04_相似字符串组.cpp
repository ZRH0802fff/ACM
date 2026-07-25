// 相似字符串组 — LeetCode 839
// 两个字符串"相似"：完全相同，或只交换一次的2个字符位置不同（即diff==0或2）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
int father[MAXN];

class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size(), m = strs[0].size();
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

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (find(i) != find(j)) { // 剪枝
                    int diff = 0;
                    for (int k = 0; k < m && diff <= 2; k++)
                        if (strs[i][k] != strs[j][k]) diff++;
                    if (diff == 0 || diff == 2) unionSet(i, j);
                }
            }
        }
        return sets;
    }
};
