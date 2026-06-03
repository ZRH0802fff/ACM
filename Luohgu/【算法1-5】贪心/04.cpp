#include<bits/stdc++.h>
using namespace std;

int n;
long long sum;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n;++i){
        int w;
        cin >> w;
        pq.push(w);
    }
    for (int i = 1; i < n;++i){
        int m1 = pq.top();
        pq.pop();
        int m2 = pq.top();
        pq.pop();
        int m = m1 + m2;
        pq.push(m);
        sum += m;
    }
    cout << sum << "\n";
    return 0;
}