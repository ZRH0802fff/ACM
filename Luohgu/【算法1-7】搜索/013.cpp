#include<bits/stdc++.h>
using namespace std;

int n, m,tal;
bool girph[110][110];//0是旱地，-1是水
int dx[4] = {0,1,1,1};
int dy[4] = {1,-1,0,1};
int father[10010];

int find(int i){
    if(i!=father[i])
        father[i] = find(father[i]);
    return father[i];
}

void unio(int x,int y){
    int fx = find(x);
    int fy = find(y);
    if(fx==fy)
        return;
    father[fx] = fy;
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n * m; ++i){
        father[i] = i;
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            char tmp;
            cin >> tmp;
            if (tmp == 'W'){
                girph[i][j] = true;
            }
        }
    }
    for (int i = 0; i < n;++i){
        for (int j = 0; j < m;++j) {
            if(girph[i][j]){
                girph[i][j] = true;
                int idx = i * m + j;
                for (int _ = 0; _ < 4;++_){
                    int nx = i + dx[_];
                    int ny = j + dy[_];
                    if (nx >= 0 &&nx < n &&ny >= 0 &&ny < m &&girph[nx][ny]){
                        unio(idx, nx * m + ny);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n;++i){
        for (int j = 0; j < m;++j){
            if(girph[i][j]){
                int idx = i * m + j;
                if(father[idx]==idx)
                    ++tal;
            }
        }
    }
    cout << tal << "\n";
    return 0;
}