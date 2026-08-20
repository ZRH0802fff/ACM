// Floyd算法模版（洛谷）
// 测试链接 : https://www.luogu.com.cn/problem/P2910
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include<bits/stdc++.h>
using namespace std;

int n,m,ans;
int path[10005];
int dt[105][105];

void floyd(){
    for(int t=0;t<n;++t){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(dt[i][t]!=INT_MAX && dt[t][j]!=INT_MAX && dt[i][j]>dt[i][t]+dt[t][j]){
                    dt[i][j]=dt[i][t]+dt[t][j];
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n>>m){
        for(int i=0;i<m;++i){
            cin>>path[i];
            path[i]--;
        }
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                cin>>dt[i][j];
            }
        }

        floyd();

        ans=0;
        for(int i=1;i<m;++i){
            ans+=dt[path[i-1]][path[i]];
        }
        cout<<ans<<'\n';
    }
    return 0;
}