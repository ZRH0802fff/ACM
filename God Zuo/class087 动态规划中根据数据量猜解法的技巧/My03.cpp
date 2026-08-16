// 两个排列的最长公共子序列长度
// 给出由1~n这些数字组成的两个排列
// 求它们的最长公共子序列长度
// n <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1439
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法

#include<bits/stdc++.h>
using namespace std;

int a[100010];
int b[100010];
int where[100010];
int ed[100010];
int n,len;

//二分查找>=num的最左位置
int bs(int len,int num){
    int l=0,r=len-1,m,ans=-1;
    while(l<=r){
        m=(l+r)/2;
        if(ed[m]>=num){
            ans=m;
            r=m-1;
        }else{
            l=m+1;
        }
    }
    return ans;
}

int main(){
    //读入处理
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=0; i<n; ++i) cin>>a[i];
    for(int i=0; i<n; ++i) cin>>b[i];

    //求解辅助数组where映射到b
    for(int i=0;i<n;++i){
        where[a[i]]=i;
    }
    for(int i=0;i<n;++i){
        b[i]=where[b[i]];
    }

    //lis 在b中求最长递增子序列
    len=0;
    for(int i=0,find;i<n; ++i){
        find=bs(len,b[i]);
        if(find==-1){
            ed[len++]=b[i];
        }else{
            ed[find]=b[i];
        }
    }

    //输出答案
    cout<<len<<'\n';
    return 0;
}