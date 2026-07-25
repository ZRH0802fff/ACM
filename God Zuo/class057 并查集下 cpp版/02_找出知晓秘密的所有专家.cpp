// 找出知晓秘密的所有专家 — LeetCode 2092
// 会议按时间排序，同一时间的会议先合并，再检查哪些组不知道秘密并撤销

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int father[MAXN];
bool secret[MAXN];

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(),
             [](auto& a, auto& b) { return a[2] < b[2]; });
        for (int i = 0; i < n; i++) father[i] = i;
        memset(secret, 0, sizeof(secret));
        father[firstPerson] = 0;
        secret[0] = true;

        auto find = [&](int i) {
            if (i != father[i]) father[i] = find(father[i]);
            return father[i];
        };

        auto unionSet = [&](int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx != fy) { father[fx] = fy; secret[fy] |= secret[fx]; }
        };

        int m = meetings.size();
        for (int l = 0; l < m;) {
            int r = l;
            while (r + 1 < m && meetings[l][2] == meetings[r + 1][2]) r++;
            // 第一阶段：同时间会议连通
            for (int i = l; i <= r; i++)
                unionSet(meetings[i][0], meetings[i][1]);
            // 第二阶段：不知道秘密的组撤销连通
            for (int i = l; i <= r; i++) {
                int a = meetings[i][0], b = meetings[i][1];
                if (!secret[find(a)]) father[a] = a, father[b] = b;
            }
            l = r + 1;
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (secret[find(i)]) ans.push_back(i);
        return ans;
    }
};
