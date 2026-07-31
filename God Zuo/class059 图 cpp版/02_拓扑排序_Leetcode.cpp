// 拓扑排序模版（Leetcode）
// 邻接表建图（动态方式）
// 课程表II
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1
// 给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi]
// 表示在选修课程 ai 前 必须 先选修 bi
// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1]
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序
// 你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组
// 测试链接 : https://leetcode.cn/problems/course-schedule-ii/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        // 入度表
        vector<int> indegree(numCourses, 0);
        for (auto& edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }
        vector<int> queue(numCourses);
        int l = 0;
        int r = 0;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                queue[r++] = i;
            }
        }
        int cnt = 0;
        while (l < r) {
            int cur = queue[l++];
            cnt++;
            for (int next : graph[cur]) {
                if (--indegree[next] == 0) {
                    queue[r++] = next;
                }
            }
        }
        if (cnt == numCourses) {
            return queue;
        }
        return vector<int>();
    }
};

int main() {
    Solution sol;
    // 示例: 4门课，[1,0],[2,0],[3,1],[3,2] → 一种可能的顺序: [0,1,2,3] 或 [0,2,1,3]
    vector<vector<int>> pre1 = {{1,0},{2,0},{3,1},{3,2}};
    vector<int> res1 = sol.findOrder(4, pre1);
    cout << "numCourses=4: ";
    for (int x : res1) cout << x << " ";
    cout << endl;
    // 不可行的例子: 2门课，[1,0],[0,1]
    vector<vector<int>> pre2 = {{1,0},{0,1}};
    vector<int> res2 = sol.findOrder(2, pre2);
    cout << "numCourses=2(impossible): " << (res2.empty() ? "empty" : "has result") << endl;
    return 0;
}
