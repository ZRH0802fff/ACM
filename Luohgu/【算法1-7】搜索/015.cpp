#include<bits/stdc++.h>
using namespace std;

struct Dq{
    int x, y;
}q[90010];

int n, m;
int l, r;
int lx, ly,sx,sy;
char gird[310][310];
int chuan[26][4];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
bool vis[310][310];

int main(){
    cin >> n >> m;
    for (int i = 0; i < 26;++i){
        for (int j = 0; j < 4;++j)
            chuan[i][j] = -1;
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            char tmp;
            cin >> tmp;
            gird[i][j] = tmp;
            if (tmp == '@'){
                sx = i;
                sy = j;
            }else if (tmp == '='){
                lx = i;
                ly = j;
            }else if (tmp != '.' && tmp != '#'){
                int idx = int(tmp) - int('A');
                if(chuan[idx][0]==-1){
                    chuan[idx][0] = i;
                    chuan[idx][1] = j;
                }else{
                    chuan[idx][2] = i;
                    chuan[idx][3] = j;
                }
            }
        }
    }
    q[r].x = sx;
    q[r++].y = sy;
    int tm = 0;
    vis[sx][sy] = true;
    while(l<r){
        ++tm;
        int size = r - l;
        for (int i = 0; i < size;++i){
            int cx = q[l].x;
            int cy = q[l++].y;
            if(gird[cx][cy]=='='){
                cout << tm-1 << "\n";
                return 0;
            }
            for (int t = 0; t < 4;++t){
                int nx = cx + dx[t];
                int ny = cy + dy[t];
                if(nx>=0 && nx<n && ny>=0 && ny<m && gird[nx][ny]!='#'){
                    if(gird[nx][ny]>='A' && gird[nx][ny]<='Z'){
                        int idx = gird[nx][ny] - 'A';
                        if(nx==chuan[idx][0] && ny==chuan[idx][1]){
                            nx = chuan[idx][2];
                            ny = chuan[idx][3];
                        }else{
                            nx = chuan[idx][0];
                            ny = chuan[idx][1];
                        }
                    }
                    if(!vis[nx][ny]){
                        vis[nx][ny] = true;
                        q[r].x = nx;
                        q[r++].y = ny;
                    }
                }
            }
        }
    }
}
