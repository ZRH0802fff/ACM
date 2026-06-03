#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int max_v = 305;
int za[max_v][max_v];
int nd_t[max_v][max_v];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
struct point{
    int x, y;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < max_v;++i){
        for (int j = 0; j < max_v;++j){
            za[i][j] = INF;
            nd_t[i][j] = -1;
        }
    }
    for (int i = 0; i < n; ++i){
        int x, y, t;
        cin >> x >> y >> t;
        za[x][y] = min(za[x][y], t);
        for (int j = 0; j < 4;++j){
            int nx = x + dx[j];
            int ny = y + dy[j];
            if(nx>=0 && ny>=0){
                za[nx][ny] = min(za[nx][ny], t);
            }
        }
    }
    if(za[0][0]==0){
        cout << -1 << endl;
        return 0;
    }
    queue<point> dq;
    dq.push({0, 0});
    nd_t[0][0] = 0;

    while(!dq.empty()){
        point p = dq.front();
        dq.pop();
        int cx = p.x;
        int cy = p.y;
        int cur_time = nd_t[cx][cy];

        if(za[cx][cy]==INF){
            cout << cur_time << endl;
            return 0;
        }

        for (int k = 0; k < 4;++k){
            int nx = cx + dx[k];
            int ny = cy + dy[k];
            if(nx>=0 && ny>=0 and nx<max_v and ny<max_v){
                if (nd_t[nx][ny]==-1 && cur_time+1<za[nx][ny]){
                    nd_t[nx][ny] = cur_time + 1;
                    dq.push({nx, ny});
                }
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
