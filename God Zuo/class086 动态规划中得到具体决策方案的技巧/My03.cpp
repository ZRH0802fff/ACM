// 最长递增子序列字典序最小的结果
// 给定数组arr，设长度为n
// 输出arr的最长递增子序列
// 如果有多个答案，请输出其中字典序最小的
// 注意这道题的字典序设定（根据提交的结果推论的）：
// 每个数字看作是单独的字符，比如120认为比36的字典序大
// 保证从左到右每个数字尽量小
// 测试链接 : https://www.nowcoder.com/practice/30fb9b3cab9742ecae9acda1c75bf927
// 测试链接 : https://www.luogu.com.cn/problem/T386911
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法

#include<bits/stdc++.h>
using namespace std;

int nums[100010];
int dp[100010];
int ed[100010];
int ans[100010];
int n,k;

//二分查找<=num的最左位置
int f(int len ,int num){
    int l=0,r=len-1,m,ans=-1;
    while(l<=r){
        m=(l+r)/2;
        if(ed[m]<=num){
            ans=m;
            r=m-1;
        }else{
            l=m+1;
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=0;i<n; ++i) cin>>nums[i];

    //填dp表，得到最长递增子序列长度k
    int len=0;
    for(int i=n-1,find;i>=0;--i){
        find=f(len,nums[i]);
        if(find==-1){
            ed[len++]=nums[i];
            dp[i]=len;
        }else{
            ed[find]=nums[i];
            dp[i]=find+1;
        }
    }
    k=len;

    //找路径，填到ans里面
    for(int i=0;i<=k; ++i) ans[i]=INT_MAX;
    for(int i=0;i<n; ++i){
        if(dp[i]==k){
            ans[0]=nums[i];
        }else{
            if(ans[k-dp[i]-1]<nums[i]){
                ans[k-dp[i]]=nums[i];
            }
        }
    }

    // 输出答案
    for(int i=0;i<k-1;++i){
        cout<<ans[i]<<' ';
    }
    cout<<ans[k-1]<<'\n';
    return 0;
}