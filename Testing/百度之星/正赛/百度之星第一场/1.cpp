#include<bits/stdc++.h>
using namespace std;

int T;
int n, k, s;
struct G{
    int hp, val;
} arr[105];
bool Cmp(G a,G b){
    if(a.hp==b.hp) return a.val>b.val;
    return a.hp < b.hp;
}
int cnt;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int _ = 0; _ < T; ++_){
        cin >> n >> k >> s;
        for (int i = 0; i < n; ++i){
            cin >> arr[i].hp >> arr[i].val;
        }
        sort(arr, arr + n, Cmp);
        // for (int i = 0; i < n;++i){
        //     cout << arr[i].hp << ' ' << arr[i].val<<'\n';
        // }

        cnt = 0;
        for (int i = 0; i < n; ++i){
            if(s>=arr[i].hp){
                s += arr[i].val;
                continue;
            }
            if(cnt<k){
                while(cnt<k && s<arr[i].hp){
                    s *= 2;
                    cnt++;
                }
                if(s>=arr[i].hp){
                    s += arr[i].val;
                    continue;
                }
            }
        }
        while(cnt<k){
            s *= 2;
            cnt++;
        }
        cout << s << '\n';
    }
    return 0;
}