// Dijkstra算法模版（Leetcode）
// 网络延迟时间
// 有 n 个网络节点，标记为 1 到 n
// 给你一个列表 times，表示信号经过 有向 边的传递时间
// times[i] = (ui, vi, wi)，表示从ui到vi传递信号的时间是wi
// 现在，从某个节点 s 发出一个信号
// 需要多久才能使所有节点都收到信号
// 如果不能使所有节点收到信号，返回 -1
// 测试链接 : https://leetcode.cn/problems/network-delay-time

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> graph;
int dt[105];
int vis[105];
struct Record{
    int u,c;
};
struct Cmp{
    bool operator()(const Record& a,const Record& b) const {
        return a.c>b.c;
    }
};
priority_queue<Record,vector<Record>,Cmp> hq;


class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int s) {
        graph.clear();
        graph.resize(n+1);
        for(auto& ed:times){
            graph[ed[0]].push_back({ed[1],ed[2]});
        }
        for(int i=1;i<=n;++i){
            dt[i]=INT_MAX;
            vis[i]=false;
        }
        dt[s]=0;
        hq.push({s,0});
        while(!hq.empty()){
            Record rec=hq.top();
            hq.pop();
            int u=rec.u;
            if(vis[u]) continue;
            vis[u]=true;
            for(auto& ed:graph[u]){
                int v=ed.first;
                int w=ed.second;
                if(!vis[v] && dt[u]+w<dt[v]){
                    dt[v]=dt[u]+w;
                    hq.push({v,dt[u]+w});
                }
            }
        }
        int ans=INT_MIN;
        for(int i=1;i<=n;++i){
            if(dt[i]==INT_MAX){
                return -1;
            }
            ans=max(ans,dt[i]);
        }
        return ans;
    }
};