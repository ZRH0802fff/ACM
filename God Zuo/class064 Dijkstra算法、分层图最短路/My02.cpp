// 最小体力消耗路径
// 你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights
// 其中 heights[row][col] 表示格子 (row, col) 的高度
// 一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1)
// （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动
// 你想要找到耗费 体力 最小的一条路径
// 一条路径耗费的体力值是路径上，相邻格子之间高度差绝对值的最大值
// 请你返回从左上角走到右下角的最小 体力消耗值
// 测试链接 ：https://leetcode.cn/problems/path-with-minimum-effort/

#include<bits/stdc++.h>
using namespace std;

struct Record{
    int x,y,c;
};
struct Cmp{
    bool operator()(const Record& a,const Record& b) const{
        return a.c>b.c;
    }
};
priority_queue<Record,vector<Record>,Cmp>hq;
int dt[105][105];
bool vis[105][105];
int n,m;
int mv[]={-1,0,1,0,-1};


class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        n=heights.size();
        m=heights[0].size();
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                dt[i][j]=INT_MAX;
                vis[i][j]=false;
            }
        }
        dt[0][0]=0;
        hq=priority_queue<Record,vector<Record>,Cmp>();

        hq.push({0,0,0});
        while(!hq.empty()){
            Record rec=hq.top();
            hq.pop();
            int x=rec.x , y=rec.y , c=rec.c;
            if(vis[x][y]) continue;
            if(x==n-1 && y==m-1) return c;
            vis[x][y]=true;
            for(int i=0;i<4;++i){
                int nx=x+mv[i];
                int ny=y+mv[i+1];
                if(nx>=0 && nx<n && ny>=0 && ny<m && !vis[nx][ny]){
                    int nc=max(c,abs(heights[x][y]-heights[nx][ny]));
                    if(nc<dt[nx][ny]){
                        dt[nx][ny]=nc;
                        hq.push({nx,ny,nc});
                    }
                }
            }
        }
        return -1;
    }
};