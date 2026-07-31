#include<bits/stdc++.h>
using namespace std;

int n, m;
long long ans;
int a[300005];
pair<int, int> p[300005];

bool cmp(const pair<int,int>&x,const pair<int,int>&y){
    return x.first != y.first ? x.first > y.first : x.second > y.second;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
}