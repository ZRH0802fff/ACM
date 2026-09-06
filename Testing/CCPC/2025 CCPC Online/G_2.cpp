#include<bits/stdc++.h>
using namespace std;

int n, q;
unordered_map<int, vector<int>> grid;
struct Question{
    int x, y;
    bool operator<(const Question& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};
map<Question,int> memo;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    grid = unordered_map<int, vector<int>>();
    for (int i = 0, num; i < n; ++i){
        cin >> num;
        grid[num].push_back(i);
    }

    for (int i = 0, x, y; i < q; ++i){
        cin >> x >> y;
        if(memo.count({x,y})){
            cout << memo[{x, y}] << '\n';
            continue;
        }
        auto& a = grid[x];
        auto& b = grid[y];
        int na = a.size();
        int nb = b.size();
        int cur = 0, ia = 0, ib = 0;
        long long ans = 0;
        if (x == y) {
            long long cnt = na;
            cout << cnt * (cnt - 1) / 2 << '\n';
            continue;
        }
        while(ia<na){
            int nxtt = 0;
            if(ia+1<na){
                nxtt = a[ia + 1];
            }else{
                nxtt = n;
            }
            cur = 0;
            while(ib<nb && b[ib]<a[ia]) ib++;
            while(ib<nb && b[ib]<nxtt){
                ib++;
                cur++;
            }
            ans += (++ia) * cur;
            // cout << "收集到的y的个数cur " << cur << '\n';
            // cout << "当前答案 " << ans << '\n';
        }
        cout << ans << '\n';
        memo[{x, y}] = ans;
    }
    return 0;
}