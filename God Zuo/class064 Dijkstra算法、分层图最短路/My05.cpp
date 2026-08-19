// 电动车游城市
// 小明的电动车电量充满时可行驶距离为 cnt，每行驶 1 单位距离消耗 1 单位电量，且花费 1 单位时间
// 小明想选择电动车作为代步工具。地图上共有 N 个景点，景点编号为 0 ~ N-1
// 他将地图信息以 [城市 A 编号,城市 B 编号,两城市间距离] 格式整理在在二维数组 paths，
// 表示城市 A、B 间存在双向通路。
// 初始状态，电动车电量为 0。每个城市都设有充电桩，
// charge[i] 表示第 i 个城市每充 1 单位电量需要花费的单位时间。
// 请返回小明最少需要花费多少单位时间从起点城市 start 抵达终点城市 end
// 测试链接 : https://leetcode.cn/problems/DFPeFJ/

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> graph;
int dt[105][105];
int vis[105][105];

struct Record{
    int cur,power,cost;
};

struct Cmp{
    bool operator()(const Record& a, const Record& b) const{
        return a.cost > b.cost;
    }
};
priority_queue<Record,vector<Record>,Cmp> hq;
int n;

class Solution {
public:
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        graph.clear();
        graph.resize(n);
        for (auto& path : paths) {
            graph[path[0]].push_back({ path[1], path[2] });
            graph[path[1]].push_back({ path[0], path[2] });
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= cnt; j++) {
                dt[i][j] = INT_MAX;
                vis[i][j]=false;
            }
        }
        dt[start][0] = 0;
        hq=priority_queue<Record,vector<Record>,Cmp>();


        hq.push({start,0,0});
        while(!hq.empty()){
            Record rec=hq.top();
            hq.pop();
            int cur = rec.cur;
            int power = rec.power;
            int cost = rec.cost;
            if (vis[cur][power]) {
                continue;
            }
            if (cur == end) {
                return cost;
            }
            vis[cur][power] = true;
            if(power<cnt){
                if(!vis[cur][power+1] && cost+charge[cur]<dt[cur][power+1]){
                    dt[cur][power+1]=cost+charge[cur];
                    hq.push({cur,power+1,cost+charge[cur]});
                }
            }
            for(auto& edge:graph[cur]){
                int nxtct=edge.first;
                int restpower=power-edge.second;
                int nxtcost=cost+edge.second;
                if(restpower>=0 && !vis[nxtct][restpower] && nxtcost<dt[nxtct][restpower]){
                    dt[nxtct][restpower]=nxtcost;
                    hq.push({nxtct,restpower,nxtcost});
                }
            }
        }
        return -1;
    }
};