// 喧闹和富有
// 从 0 到 n - 1 编号，其中每个人都有不同数目的钱，以及不同程度的安静值
// 给你一个数组richer，其中richer[i] = [ai, bi] 表示
// person ai 比 person bi 更有钱
// 还有一个整数数组 quiet ，其中 quiet[i] 是 person i 的安静值
// richer 中所给出的数据 逻辑自洽
// 也就是说，在 person x 比 person y 更有钱的同时，不会出现
// person y 比 person x 更有钱的情况
// 现在，返回一个整数数组 answer 作为答案，其中 answer[x] = y 的前提是,
// 在所有拥有的钱肯定不少于 person x 的人中，
// person y 是最安静的人（也就是安静值 quiet[y] 最小的人）。
// 测试链接 : https://leetcode.cn/problems/loud-and-rich/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 501;

// 拓扑排序，入度表
int indegree[MAXN];

// 拓扑排序，队列
int queue_[MAXN];
int l, r;

class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        // 邻接表建图（和Java一样用动态方式）
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            indegree[i] = 0;
        }
        for (auto& r : richer) {
            graph[r[0]].push_back(r[1]);
            indegree[r[1]]++;
        }
        l = 0;
        r = 0;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                queue_[r++] = i;
            }
        }
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = i;
        }
        while (l < r) {
            int cur = queue_[l++];
            for (int next : graph[cur]) {
                if (quiet[ans[cur]] < quiet[ans[next]]) {
                    ans[next] = ans[cur];
                }
                if (--indegree[next] == 0) {
                    queue_[r++] = next;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    // 示例: richer=[[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet=[3,2,5,4,6,1,7,0]
    vector<vector<int>> richer = {{1,0},{2,1},{3,1},{3,7},{4,3},{5,3},{6,3}};
    vector<int> quiet = {3,2,5,4,6,1,7,0};
    vector<int> ans = sol.loudAndRich(richer, quiet);
    cout << "answer: ";
    for (int x : ans) cout << x << " ";
    cout << "(expected: 5 5 2 5 4 5 6 7)" << endl;
    return 0;
}
