#include<bits/stdc++.h>
using namespace std;
int n, ans;

struct node{
    int sta, ed;
}nd[1000010];

bool cmp(node n1,node n2){
    if(n1.ed==n2.ed)
        return n1.sta > n2.sta;
    return n1.ed < n2.ed;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n;++i){
        cin >> nd[i].sta >> nd[i].ed;
    }
    sort(nd, nd + n, cmp);
    int ed = 0;
    for (int i = 0; i < n;++i){
        if(nd[i].sta>=ed){
            ++ans;
            ed = nd[i].ed;
        }
    }
    cout << ans << "\n";
    return 0;
}