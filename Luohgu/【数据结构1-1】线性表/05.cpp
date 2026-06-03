// #include<bits/stdc++.h>
// using namespace std;

// int main(){
//     int n;
//     cin >> n;
//     list<int> ls;
//     ls.push_back(1);
//     int curnum = 2;
//     for (int i = 0; i < n - 1; ++i){
//         int k, q;
//         cin >> k >> q;
//         auto it = find(ls.begin(), ls.end(), k);
//         if(q==1)
//             it = next(it);
//         ls.insert(it, curnum);
//         ++curnum;
//     }
//     int m;
//     cin >> m;
//     for(int i = 0; i < m;++i){
//         int t;
//         cin >> t;
//         auto it = find(ls.begin(), ls.end(), t);
//         if(it!=ls.end())
//             ls.erase(it);
//     }
//     for(int val:ls)
//         cout << val << ' ';
//     cout << endl;
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n;
    cin >> n;
    list<int> ls;
    vector<list<int>::iterator> pos(n + 1);
    ls.push_back(1);
    pos[1] = ls.begin();
    for (int i = 2; i <= n;++i){
        int k, p;
        cin >> k >> p;
        auto it = pos[k];
        if(p==1){
            ++it;
        }
        pos[i] = ls.insert(it, i);
    }
    int m;
    cin >> m;
    vector<bool> vis(n + 1, false);
    for (int i = 0; i < m;++i){
        int x;
        cin >> x;
        if(!vis[x]){
            ls.erase(pos[x]);
            vis[x] = true;
        }
    }
    for(int val:ls){
        cout << val << ' ';
    }
    cout << "\n";
    return 0;
}