// 电动车游城市
// 小明的电动车电量充满时可行驶距离为 cnt，每行驶 1 单位距离消耗 1 单位电量，且花费 1 单位时间
// 小明想选择电动车作为代步工具。地图上共有 N 个景点，景点编号为 0 ~ N-1
// 他将地图信息以 [城市 A 编号,城市 B 编号,两城市间距离] 格式整理在在二维数组 paths，
// 表示城市 A、B 间存在双向通路。
// 初始状态，电动车电量为 0。每个城市都设有充电桩，
// charge[i] 表示第 i 个城市每充 1 单位电量需要花费的单位时间。
// 请返回小明最少需要花费多少单位时间从起点城市 start 抵达终点城市 end
// 测试链接 : https://leetcode.cn/problems/DFPeFJ/

#include <bits/stdc++.h>
using namespace std;

// 城市数量最多 100，电量上限最多 100，n * (cnt+1) <= 10100
const int MAXN = 101;
const int MAXC = 101;

// 邻接表
// graph[i] = {{邻居城市, 距离}, ...}
vector<vector<pair<int, int>>> graph;

// (点，到达这个点的电量) 图上的点！
int distance_[MAXN][MAXC];
bool visited[MAXN][MAXC];

// 小根堆的记录
// 0 : 当前点
// 1 : 来到当前点的电量
// 2 : 花费时间
struct Record {
    int cur, power, cost;
};
// 按花费时间组织小根堆
struct Cmp {
    bool operator()(const Record& a, const Record& b) const {
        return a.cost > b.cost;
    }
};
priority_queue<Record, vector<Record>, Cmp> heap;

class Solution {
public:
    // 电动车总电量，cnt
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        int n = charge.size();
        graph.clear();
        graph.resize(n);
        for (auto& path : paths) {
            graph[path[0]].push_back({ path[1], path[2] });
            graph[path[1]].push_back({ path[0], path[2] });
        }
        // n : 0 ~ n-1，不代表图上的点
        // (点，到达这个点的电量)图上的点！
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= cnt; j++) {
                distance_[i][j] = INT_MAX;
            }
        }
        distance_[start][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= cnt; j++) {
                visited[i][j] = false;
            }
        }
        heap = priority_queue<Record, vector<Record>, Cmp>();
        heap.push({ start, 0, 0 });
        while (!heap.empty()) {
            Record rec = heap.top();
            heap.pop();
            int cur = rec.cur;
            int power = rec.power;
            int cost = rec.cost;
            if (visited[cur][power]) {
                continue;
            }
            if (cur == end) {
                // 常见剪枝
                // 发现终点直接返回
                // 不用等都结束
                return cost;
            }
            visited[cur][power] = true;
            if (power < cnt) {
                // 充一格电
                // cur, power+1
                if (!visited[cur][power + 1] && cost + charge[cur] < distance_[cur][power + 1]) {
                    distance_[cur][power + 1] = cost + charge[cur];
                    heap.push({ cur, power + 1, cost + charge[cur] });
                }
            }
            for (auto& edge : graph[cur]) {
                // 不充电去别的城市
                int nextCity = edge.first;
                int restPower = power - edge.second;
                int nextCost = cost + edge.second;
                if (restPower >= 0 && !visited[nextCity][restPower] && nextCost < distance_[nextCity][restPower]) {
                    distance_[nextCity][restPower] = nextCost;
                    heap.push({ nextCity, restPower, nextCost });
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> paths1 = { { 1, 3, 3 }, { 3, 2, 1 }, { 2, 1, 3 }, { 0, 1, 4 }, { 3, 0, 5 } };
    vector<int> charge1 = { 2, 10, 4, 1 };
    cout << sol.electricCarPlan(paths1, 6, 1, 0, charge1) << " (expected: 43)" << endl;
    vector<vector<int>> paths2 = { { 0, 1, 1 } };
    vector<int> charge2 = { 1, 1 };
    cout << sol.electricCarPlan(paths2, 1, 0, 1, charge2) << " (expected: 2)" << endl;
    return 0;
}
