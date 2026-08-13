// 选择k个数字使得两集合累加和相差不超过1
// 给定一个正数n，表示1~n这些数字都可以选择
// 给定一个正数k，表示要从1~n中选择k个数字组成集合A，剩下数字组成集合B
// 希望做到集合A和集合B的累加和相差不超过1
// 如果能做到，返回集合A选择了哪些数字，任何一种方案都可以
// 如果不能做到，返回长度为0的数组
// 2 <= n <= 10^6
// 1 <= k <= n
// 来自真实大厂笔试，没有测试链接，用对数器验证

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int ansarr[1000010];
int anslen;

void pick(int n,int k){
    ll sum=(ll)(n+1)*n/2;
    bulid(sum/2,n,k);
    if(anslen==0 && (sum&1)==1){
        bulid(sum/2+1,n,k);
    }
}

// 1~n里面挑k个数字，看能否凑够sum的累加和
// 能就写到ans里面，不能返回空数组
void bulid(ll sum,int n,int k){
    ll minKsum=(ll)(k+1)*k/2;
    int range=n-k;
    if(sum<minKsum || sum>minKsum+(ll)range*k){
        anslen=0;
        return;
    }
    ll need=sum-minKsum;
    int rsize=(int)(need/range);
    int midx=(k-rsize)+(int)(need%range);
    int lsize=k-rsize-(need%range==0 ?0:1);
    anslen=k;
    for(int i=0;i<lsize;++i){
        ansarr[i]=i+1;
    }
    if(need%range!=0){
        ansarr[lsize]=midx;
    }
    for(int i=k-1,j=0;j<rsize; --i,++j){
        ansarr[i]=n-j;
    }
}