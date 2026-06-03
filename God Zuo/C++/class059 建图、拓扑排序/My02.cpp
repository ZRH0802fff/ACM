#include<bits/stdc++.h>
using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites){
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);
    for(const auto &edge:prerequisites){
        graph[edge[1]].push_back(edge[0]);
        indegree[edge[0]]++;
    }
    vector<int> queue(numCourses);
    int l = 0;
    int r = 0;
    for (int i = 0; i < numCourses;++i){
        if(indegree[i]==0){
            queue[r++] = i;
        }
    }
    int cnt = 0;
    while(l<r){
        int cur = queue[l++];
        ++cnt;
        for(int nxt:graph[cur]){
            if(--indegree[nxt]==0){
                queue[r++] = nxt;
            }
        }
    }
    return cnt == numCourses ? queue : vector<int>();
}

int main()
{
    int numCourses = 4;
    // 课程对：[1,0] 表示学 1 前要先学 0
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    vector<int> order = findOrder(numCourses, prerequisites);

    if (order.empty())
    {
        cout << "不可能完成所有课程（存在环）" << endl;
    }
    else
    {
        cout << "学习顺序为: ";
        for (int course : order)
        {
            cout << course << " ";
        }
        cout << endl;
    }

    return 0;
}