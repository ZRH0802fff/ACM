#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, q;
int arr[100010];
int pre,cur;
int ans;
int idx;
struct Question{
    int x, y;
    bool operator<(const Question& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin>>arr[i];
    map<Question,int> memo;
    for (int i = 0, x, y; i < q; ++i){
        cin >> x >> y;
        pre = 0, idx = 0, ans = 0;
        if(memo.count({x,y})){
            cout << memo[{x, y}] << '\n';
            continue;
        }
        while(idx<n){
            while(arr[idx]!=x) ++idx;
            //cout << "x的下标 " << idx << '\n';
            cur = 0;
            while(idx+1<n && arr[idx+1]!=x){
                idx++;
                if(arr[idx]==y) cur++;
            }
            //cout << "下一个x前的坐标 " << idx << '\n';
            //cout << "收集到的y的个数cur " << cur << '\n';
            ans += (pre + 1) * cur;
            //cout << "当前答案 " << ans << '\n';
            pre++;
        }
        memo[{x, y}] = ans;
        cout << ans << '\n';
    }
    return 0;
}
