// 贿赂怪兽
// 开始时你的能力是0，你的目标是从0号怪兽开始，通过所有的n只怪兽
// 如果你当前的能力小于i号怪兽的能力，则必须付出b[i]的钱贿赂这个怪兽
// 然后怪兽就会加入你，他的能力a[i]直接累加到你的能力上
// 如果你当前的能力大于等于i号怪兽的能力，你可以选择直接通过，且能力不会下降
// 但你依然可以选择贿赂这个怪兽，然后怪兽的能力直接累加到你的能力上
// 返回通过所有的怪兽，需要花的最小钱数
// 测试链接 : https://www.nowcoder.com/practice/736e12861f9746ab8ae064d4aae2d5a9
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
#include<bits/stdc++.h>
using namespace std;

int n;
int a[505];
int b[505];
int dp[505][500010];

int compute1(){
    int m=0;
    for(int i=1;i<=n;++i){
        m+=b[i];
    }
    for(int j=0;j<=m;++j){
        dp[0][j]=0;
    }
    for(int i=1;i<=n;++i){
        for(int j=0;j<=m;++j){
            dp[i][j]=INT_MIN;
            if(dp[i-1][j]>=a[i]){
                dp[i][j]=dp[i-1][j];
            }
            if(j-b[i]>=0 && dp[i-1][j-b[i]]!=INT_MIN){
                dp[i][j]=max(dp[i][j],dp[i-1][j-b[i]]+a[i]);
            }
        }
    }

    int ans=-1;
    for(int j=0;j<=m;++j){
        if(dp[n][j]!=INT_MIN){
            ans=j;
            break;
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n; ++i){
        cin>>a[i]>>b[i];
    }
    cout<<compute1()<<'\n';
    return 0;
}