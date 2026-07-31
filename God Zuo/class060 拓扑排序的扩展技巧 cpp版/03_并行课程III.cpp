// 并行课程 III
// 给你一个整数 n ，表示有 n 节课，课程编号从 1 到 n
// 同时给你一个二维整数数组 relations ，
// 其中 relations[j] = [prevCoursej, nextCoursej]
// 表示课程 prevCoursej 必须在课程 nextCoursej 之前 完成（先修课的关系）
// 同时给你一个下标从 0 开始的整数数组 time
// 其中 time[i] 表示完成第 (i+1) 门课程需要花费的 月份 数。
// 请你根据以下规则算出完成所有课程所需要的 最少 月份数：
// 如果一门课的所有先修课都已经完成，你可以在 任意 时间开始这门课程。
// 你可以 同时 上 任意门课程 。请你返回完成所有课程所需要的 最少 月份数。
// 注意：测试数据保证一定可以完成所有课程（也就是先修课的关系构成一个有向无环图）
// 测试链接 : https://leetcode.cn/problems/parallel-courses-iii/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50001;

// 拓扑排序，入度表
int indegree[MAXN];

// 拓扑排序，队列
int queue_[MAXN];
int l, r;

// cost[i] : 完成课程i的最早时间
int cost[MAXN];

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        // 点 : 1....n
        // 邻接表建图（和Java一样用动态方式）
        vector<vector<int>> graph(n + 1);
        for (int i = 0; i <= n; i++) {
            indegree[i] = 0;
            cost[i] = 0;
        }
        for (auto& edge : relations) {
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }
        l = 0;
        r = 0;
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) {
                queue_[r++] = i;
            }
        }
        int ans = 0;
        while (l < r) {
            int cur = queue_[l++];
            // 1 : time[0]
            // x : time[x-1]
            cost[cur] += time[cur - 1];
            ans = max(ans, cost[cur]);
            for (int next : graph[cur]) {
                cost[next] = max(cost[next], cost[cur]);
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
    // 示例: n=3, relations=[[1,3],[2,3]], time=[3,2,5]
    vector<vector<int>> rel = {{1,3},{2,3}};
    vector<int> time = {3,2,5};
    cout << "min time: " << sol.minimumTime(3, rel, time) << " (expected: 8)" << endl;
    return 0;
}
