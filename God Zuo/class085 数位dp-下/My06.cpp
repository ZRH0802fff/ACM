// 范围内的数字计数
// 给定两个正整数a和b，求在[a,b]范围上的所有整数中
// 每个数码(digit)各出现了多少次
// 1 <= a, b
// 测试链接 : https://www.luogu.com.cn/problem/P2602
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a,b;

ll ct(ll num,int d){
    ll ans=0;
    for(ll r=1,tmp=num,l,cur;tmp!=0; r*=10,tmp/=10){
        l=tmp/10;
        if(d==0) l--;
        ans+=l*r;
        cur=tmp%10;
        if(cur>d){
            ans+=r;
        }else if(cur==d){
            ans+=num%r+1;
        }
    }
    return ans;
}

ll slove(int d){
    return ct(b,d)-ct(a-1,d);
}

int main(){
    cin>>a>>b;
    for(int i=0;i<9; ++i){
        cout<<slove(i)<<' ';
    }
    cout<<slove(9)<<'\n';
    return 0;
}