#include<bits/stdc++.h>
using namespace std;

struct Zhan{
    int c,pc;
    bool vis;
};

bool Cmp1(Zhan a,Zhan b){
    return a.c<b.c;
}
bool Cmp2(Zhan a,Zhan b){
    return a.pc<b.pc;
}
Zhan arr[1010];

int n,m;
int cnt;
int tal;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0,p,s;i<n;++i){
        cin>>p>>s;
        arr[i].c=p+s;
        arr[i].pc=p/2+s;
    }
    sort(arr,arr+n,Cmp1);
    for(int i=0;i<n;++i){
        if(tal+arr[i].c<=m){
            tal+=arr[i].c;
            cnt++;
            arr[i].vis=true;
        }else{
            break;
        }
    }
    sort(arr,arr+n,Cmp2);
    for(int i=0;i<n;++i){
        if(!arr[i].vis){
            if(arr[i].pc+tal<=m)cnt++;
            break;
        }
    }
    cout<<cnt<<'\n';
    return 0;
}