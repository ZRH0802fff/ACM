#include<bits/stdc++.h>

using namespace std;
#define int long long

signed main()
{
    int a[7];
    for (int i = 1; i <= 6;i++){
        cin >> a[i];
    }
    int k;
    cin >> k;
    int t = a[3] + 1;
    int qz;
    for (int i = 3; i <= 6;i++){
        if(t>a[i])
            qz = i;
    }
    int min;
    //  cout << "qz" << qz << endl;
    //  cout << "t" << t << endl;
    int sl = 5;
    if(qz==3)
        min = t * sl+ (a[4] + (6-sl));
        
    else{
         sl=(19 + qz - 1) / qz;
        //  cout << "sl" << sl << endl;
        min = t * sl + (6 - sl);
    }
    cout <<"min   "<< min << endl;
    if( min<=k)
        {
            cout << "YES" << endl;
            for (int i = 1; i <= sl;i++){
                cout << t << ' ';
            }
            if(qz==3) {
                cout << k-t*sl;
            }
            else{
                for (int i = 1; i <= (6 - sl)-1;i++){
                    cout << "1"<<' ';
                }cout << k - t * sl - (5 - sl) << endl;

            }

            
        }
    else
        cout << "NO" << endl;
        
}