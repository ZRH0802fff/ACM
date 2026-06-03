#include<bits/stdc++.h>
using namespace std;

vector<int> arr;
int n, s, a, b,ans;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s;
    cin >> a >> b;
    int mh = a + b;
    for (int i = 0; i < n;++i){
        int h, t;
        cin >> h >> t;
        if(h<=mh)
            arr.push_back(t);
    }
    sort(arr.begin(), arr.end());
    for(int t:arr){
        if (s>=t){
            s -= t;
            ++ans;
        }else{
            break;
        }
    }
    cout << ans << endl;
    return 0;
}