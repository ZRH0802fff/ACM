#include <bits/stdc++.h>
using namespace std;

int arr[1<<8],tree[1<<9];

void build(int l,int r, int idx)
{
    if (l==r)
    {
        tree[idx]=l;
        return;
    }
    int mid,l_win,r_win;
    mid=(l+r)/2;
    build(l,mid,idx*2);
    build(mid+1,r,idx*2+1);
    l_win=tree[2*idx];
    r_win=tree[2*idx+1];
    if (arr[l_win]>arr[r_win]) tree[idx]=l_win;
    else tree[idx]=r_win;
}

int main(){
    int n;
    cin >> n;
    for (int i=0;i<1<<n;++i) cin >> arr[i];
    build(0,(1<<n)-1,1);
    int l_win,r_win;
    l_win=tree[2];
    r_win=tree[3];
    if (arr[l_win]>arr[r_win]) cout << r_win+1 << "\n";
    else cout << l_win+1 << "\n";
}