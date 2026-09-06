#include<bits/stdc++.h>
using namespace std;

int T;
int n, k;
int arr[200010];
int tong[200010];
bool isgai[200010];
int stidx;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while(T--){
        cin >> n >> k;
        memset(tong, 0, sizeof(tong));
        memset(isgai, 0, sizeof(isgai));
        stidx = 1;
        for (int i = 0; i < n; ++i){
            cin >> arr[i];
            tong[arr[i]]++;
            if(tong[arr[i]]>=2 || (tong[arr[i]]!=0 && arr[i]>=k)){
                isgai[arr[i]] = true;
            }
        }
        if(k==1){
            cout << -1 << '\n';
            continue;
        }

        long long ans = 0;
        for (int i = 1; i < k; ++i){
            if(tong[i]!=0) continue;
            stidx = i + 1;
            while(!isgai[stidx]) stidx++;

            ans += stidx-i;
            tong[i]++;
            tong[stidx]--;
            if((stidx<k && tong[stidx]==1) || (stidx>=k && tong[stidx]==0)) isgai[stidx] = false;
        }
        if(tong[k]>=0){
            ans += tong[k];
            tong[k - 1] += tong[k];
            tong[k] == 0;
        }
        for (int i = 1; i < k; ++i){
            if(tong[k]==0){
                ans = -1;
                break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}