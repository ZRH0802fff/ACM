#include<bits/stdc++.h>
using namespace std;

int tarr[100010];
int arr[100010];
int edp[100010];
int n,len,len2;
int dao[100010];

int f(int len,int num){
    int l = 0, r = len - 1, m, ans = -1;
    while(l<=r){
        m = (l + r) / 2;
        if(edp[m]>num){
            ans = m;
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    return ans;
}

//查询>=num的第一个元素下标，没有返回-1
int f2(int len,int num){
    int l = 0, r = len - 1, m, ans = -1;
    while(l<=r){
        m = (l + r) / 2;
        if(dao[m]>=num){
            ans = m;
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int idx = 0;
    while (cin>>tarr[idx++]){
        n++;
    }
    for (int i = 0; i < n; ++i){
        arr[i] = tarr[n - i - 1];
    }
    len = 0;
    for (int i = 0, find; i < n; ++i){
        find = f(len, arr[i]);
        if(find==-1){
            edp[len++] = arr[i];
        }
        else{
            edp[find] = arr[i];
        }
    }
    cout << len << '\n';

    len2 = 1;
    dao[0] = tarr[0];
    for (int i = 1,find; i < n; ++i){
        find = f2(len2, tarr[i]);
        if(find==-1){
            dao[len2++] = tarr[i];
        }else{
            dao[find] = tarr[i];
        }
    }
    cout << len2 << '\n';
    return 0;
}