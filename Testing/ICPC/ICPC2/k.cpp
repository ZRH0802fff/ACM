#include<bits/stdc++.h>

using namespace std;
int T = 1;
const int N = 5e3 + 10;
int a[N];
int n;
int q,k;
int x;
void chushihua() {//初始化

};

void sort_a() {//对数组a排序

};
void find(int k){//二分查找数组,如果有k,返回最右边k在数组下标
                //          如果没K，返回比k小的最右边数组下标,返回下标被x接住
    
}
int  f(int l,int r){
    int ans = 0;
    if(r<l)
        return ans;
    else if(r==l){
        
    }else{
        


    }
}

void solved(){
    cin >> n;
    chushihua();//初始化
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    sort_a();//对数组a排序

    cin >> q;
    int l, r;//左右指针
    while(q--){
        cin >> k;
        find(k);//
        l = 1;
        r = x;
        f(l,r);
    }
    
}

int main(){
    cin >> T;
    while(T--)
        solved();
}