// 完成配对需要的最少字符数量
// 给定一个由'['、']'、'('，')'组成的字符串
// 请问最少插入多少个括号就能使这个字符串的所有括号正确配对
// 例如当前串是 "([[])"，那么插入一个']'即可满足
// 输出最少需要插入多少个字符
// 测试链接 : https://www.nowcoder.com/practice/e391767d80d942d29e6095a935a5b96b

#include<bits/stdc++.h>
using namespace std;

const int maxn = 210;
int dp[maxn][maxn];
string s;

int f(int l,int r){
    if(l==r)
        return 1;
    if(l+1==r){
        if((s[l]=='(' && s[r]==')') || (s[l]=='[' && s[r]==']')){
            return 0;
        }else{
            return 2;
        }
    }
    if(dp[l][r]!=-1)
        return dp[l][r];

    int p1 = INT_MAX;
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')){
        p1 = f(l + 1, r - 1);
    }
    int p2 = INT_MAX;
    for (int k = l; k < r;++k){
        p2 = min(p2, f(l, k) + f(k + 1, r));
    }
    int ans = min(p1, p2);
    dp[l][r] = ans;
    return ans;
}

int main(){
    cin >> s;
    int n = s.length();
    for (int i = 0; i < n;++i){
        for (int j = 0; j < n;++j)
            dp[i][j] = -1;
    }
    cout << f(0, n - 1)<<'\n';
    return 0;
}