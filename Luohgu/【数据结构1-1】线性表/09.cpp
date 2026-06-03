#include<bits/stdc++.h>
using namespace std;
int main(){
    int q;
    cin >> q;
    for (int _ = 0; _ < q; ++_){
        int n;
        cin >> n;
        int pu[n], po[n];
        for (int i = 0; i < n;++i)
            cin >> pu[i];
        for (int i = 0; i < n; ++i)
            cin >> po[i];
        int msta[n], r = 0;
        int idx = 0;
        int puidx = 0;
        while(puidx<n){
            msta[r++] = pu[puidx++];
            while(r>0 && po[idx]==msta[r-1]){
                r--;
                idx++;
            }
        }
        if(idx==n)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}