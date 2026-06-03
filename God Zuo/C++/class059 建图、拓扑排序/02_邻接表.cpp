#include <iostream>
#include <vector>

using namespace std;

// 拓扑排序模版：直接作为普通函数
vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites){
    // 邻接表建图（动态方式）
    vector<vector<int>> graph(numCourses);

    // 入度表，初始化为 0
    vector<int> indegree(numCourses, 0);

    // 遍历所有先修课程的要求，建图并统计入度
    for (const auto &edge : prerequisites){
        graph[edge[1]].push_back(edge[0]);
        indegree[edge[0]]++;
    }

    // 用数组模拟队列
    vector<int> queue(numCourses);
    int l = 0;
    int r = 0;

    // 将所有入度为 0 的节点入队
    for (int i = 0; i < numCourses; i++){
        if (indegree[i] == 0)
        {
            queue[r++] = i;
        }
    }

    int cnt = 0;
    while (l < r){
        int cur = queue[l++];
        cnt++;

        // 遍历当前节点的所有邻居
        for (int next : graph[cur]){
            // 如果入度减为 0，则入队
            if (--indegree[next] == 0){
                queue[r++] = next;
            }
        }
    }

    // 如果成功遍历的节点数等于总课程数，说明没有环，返回 queue
    // 否则返回空数组
    return cnt == numCourses ? queue : vector<int>();
}

// 本地测试样例
int main(){
    int numCourses = 4;
    // 课程对：[1,0] 表示学 1 前要先学 0
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    vector<int> order = findOrder(numCourses, prerequisites);

    if (order.empty()){
        cout << "不可能完成所有课程（存在环）" << endl;
    }else{
        cout << "学习顺序为: ";
        for (int course : order)
        {
            cout << course << " ";
        }
        cout << endl;
    }

    return 0;
}