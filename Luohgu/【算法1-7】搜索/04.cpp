#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, a, b;
    cin >> n >> a >> b;
    int arr[n];
    for (int i = 0; i < n;++i){
        cin >> arr[i];
    }
    if (a == b){
        cout << 0 << endl;
        return 0;
    }
    deque<int> queue;
    queue.push_back(a);
    int ge = 1;
    int ce = 1;
    int nx_ge = 0;
    bool memo[n];
    for (int i = 0; i < n;i++){
        memo[i] = false;
    }
    memo[a-1] = true;
    while (!queue.empty())
    {
        ge--;
        int cur = queue.front();
        queue.pop_front();
        int xia = cur - arr[cur - 1];
        int sa = cur + arr[cur - 1];
        if (xia >= 1 && xia <= n && !memo[xia - 1])
        {
            if (xia == b)
            {
                cout << ce << endl;
                return 0;
            }
            queue.push_back(xia);
            memo[xia - 1] = true;
            nx_ge += 1;
        }
        if (sa >= 1 && sa <= n && !memo[sa - 1])
        {
            if (sa == b)
            {
                cout << ce << endl;
                return 0;
            }
            memo[sa - 1] = true;
            queue.push_back(sa);
            nx_ge += 1;
        }
        if (ge == 0)
        {
            ce++;
            ge = nx_ge;
            nx_ge = 0;
        }
        }
    cout << -1 << endl;
    return 0;
}