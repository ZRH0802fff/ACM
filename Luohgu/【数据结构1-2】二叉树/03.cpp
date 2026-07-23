#include<bits/stdc++.h>
using namespace std;

string pre,mid;

void dfs(int ls,int le,int rs,int re){
    if(ls>le || rs>re) return;
    for(int i=ls;i<=le;++i){
        if(mid[i]==pre[rs]){
            dfs(ls,i-1,rs+1,rs+i-ls);
            dfs(i+1,le,rs+i-ls+1,re);
            cout<<mid[i];
        }
    }
}

int main(){
    cin>>mid;
    cin>>pre;
    int l=pre.length();
    dfs(0,l-1,0,l-1);
    return 0;
}