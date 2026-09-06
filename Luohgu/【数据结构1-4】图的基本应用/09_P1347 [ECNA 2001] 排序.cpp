#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> grid[30];
int indegree[30];
string ans;
int q[300];
int l, r;

int topo(){
    int d[30];
    for (int i = 0; i < n; ++i){
        d[i] = indegree[i];
    }
    l = r = 0;
    for (int i = 0; i < n; ++i){
        if(d[i]==0){
            q[r++] = i;
        }
    }

    ans = "";
    bool unique = true;
    int cnt = 0;

    while(l<r){
        if(r-l>1){
            unique = false;
        }
        int u = q[l++];
        ans += char('A' + u);
        cnt++;
        for(int v:grid[u]){
            d[v]--;
            if(d[v]==0){
                q[r++] = v;
            }
        }
    }
    if(cnt<n) return 0;
    if(!unique) return 1;
    return 2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        char a, op, b;
        cin >> a >> op >> b;
        int u = a - 'A';
        int v = b - 'A';
        grid[u].push_back(v);
        indegree[v]++;
        int sta = topo();
        if(sta==0){
            cout << "Inconsistency found after "<< i+1 << " relations.\n";
            return 0;
        }else if(sta==2){
            cout << "Sorted sequence determined after "<< i+1 << " relations: "<< ans << ".\n";
            return 0;
        }
    }
    cout << "Sorted sequence cannot be determined.\n";
    return 0;
}