#include<bits/stdc++.h>
using namespace std;

multiset<int>q;
int n,order;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    q.insert(-2147483647);
    q.insert(2147483647);
    cin>>n;
    for(int _=0,op,num;_<n;++_){
        cin>>op>>num;
        if(op==5){
            q.insert(num);
        } else if(op==1){
            auto it = q.lower_bound(num);
            order=0;
            for(auto i=q.begin();i!=it;++i,++order);
            cout<<order<<'\n';
        } else if(op==2){
            order=-1;
            for(int i:q){
                if(++order==num) 
                    cout<<i<<'\n';
            }
        } else if(op==3){
            auto it =q.lower_bound(num);
            cout<<*--it<<'\n';
        } else if(op==4){
            auto it =q.upper_bound(num);
            cout<<*it<<'\n';
        }
    }
}