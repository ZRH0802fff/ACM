#include<bits/stdc++.h>
using namespace std;

int mv[]={1,0,-1,0,1};
int grid[4010][4010];
int dt[4010][4010];
bool vis[4010][4010];

struct Record{
    int x,y,c;
};
struct Cmp{
    bool operator()(const Record& a, const Record& b) const {
        return a.c>b.c;
    }
};
priority_queue<Record,vector<Record>,Cmp> hq;

int f1(int x,int y,int tx,int ty){
    return (abs(tx-x)+abs(ty-y));
}

int a(int n,int sx,int sy,int tx,int ty){
    if(grid[sx][sy]==0 || grid[tx][ty]==0) return -1;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            dt[i][j]=INT_MAX;
            vis[i][j]=false;
        }
    }
    dt[sx][sy]=1;
    hq=priority_queue<Record,vector<Record>,Cmp>();

    hq.push({sx,sy,1+f1(sx,sy,tx,ty)});
    while(!hq.empty()){
        Record cur=hq.top();
        hq.pop();
        int x=cur.x;
        int y=cur.y;
        if(vis[x][y]) continue;
        vis[x][y]=true;
        if(x==tx && y==ty) return dt[x][y];
        for(int i=0,nx,ny;i<4;++i){
            nx=x+mv[i];
            ny=y+mv[i+1];
            if(nx>=0 && nx<n && ny>=0 && ny<n && grid[nx][ny]==1 && !vis[nx][ny] && dt[x][y]+1<dt[nx][ny]){
                dt[nx][ny]=dt[x][y]+1;
                hq.push({nx,ny,dt[x][y]+1+f1(nx,ny,tx,ty)});
            }
        }
    }
    return -1;
}