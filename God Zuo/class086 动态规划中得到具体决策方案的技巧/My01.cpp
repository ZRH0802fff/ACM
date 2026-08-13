// 最长公共子序列其中一个结果
// 给定两个字符串str1和str2
// 输出两个字符串的最长公共子序列
// 如果最长公共子序列为空，则输出-1
// 测试链接 : https://www.nowcoder.com/practice/4727c06b9ee9446cab2e859b4bb86bb8
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法

#include<bits/stdc++.h>
using namespace std;

int dp[5010][5010];
char ans[5010];
string s1,s2;
int n,m,k;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>s1>>s2;
    n=s1.length();
    m=s2.length();

    for(int i=1;i<=n;++i){
        for(int j=1;j<=m; ++j){
            if(s1[i-1]==s2[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            }else{
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }

    k=dp[n][m];
    if(k>0){
        for(int len=k,i=n,j=m; len>0;){
            if(s1[i-1]==s2[j-1]){
                ans[--len]=s1[i-1];
                --i;
                --j;
            }else{
                if(dp[i-1][j]>=dp[i][j-1]){
                    --i;
                }else{
                    --j;
                }
            }
        }
        for(int i=0;i<k; ++i){
            cout<<ans[i];
        }
        cout<<'\n';
    }else{
        cout<<-1<<'\n';
    }
    return 0;
}