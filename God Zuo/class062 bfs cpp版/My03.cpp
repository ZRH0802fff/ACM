// 到达角落需要移除障碍物的最小数目
// 给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n
// 每个单元格都是两个值之一：
// 0 表示一个 空 单元格，
// 1 表示一个可以移除的 障碍物
// 你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。
// 现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1)
// 返回需要移除的障碍物的最小数目
// 测试链接 : https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
#include<bits/stdc++.h>
using namespace std;

int dq[100010][2];
int h,t;
int mv[5]={-1,0,1,0,-1};
int n,m;

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        n=grid.size();
        m=grid[0].size();
        int dt[n][m];
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                dt[i][j]=INT_MAX;
            }
        }

        h=t=50000;
        dq[h][0]=0;
        dq[h][1]=0;
        dt[0][0]=0;
        while(h<=t){
            int x=dq[h][0];
            int y=dq[h++][1];
            if(x==n-1 && y==m-1){
                return dt[x][y];
            }
            for(int i=0;i<4;++i){
                int nx=x+mv[i];
                int ny=y+mv[i+1];
                if(nx>=0 && nx<n && ny>=0 && ny<m && dt[x][y]+grid[nx][ny]<dt[nx][ny]){
                    dt[nx][ny]=dt[x][y]+grid[nx][ny];
                    if(grid[nx][ny]==0){
                        dq[--h][0]=nx;
                        dq[h][1]=ny;
                    }else{
                        dq[++t][0]=nx;
                        dq[t][1]=ny;
                    }
                }
            }
        }
        return -1;
    }
};