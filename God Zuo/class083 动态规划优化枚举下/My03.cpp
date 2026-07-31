// 自由之路
// 题目描述比较多，打开链接查看
// 测试链接 : https://leetcode.cn/problems/freedom-trail/
// 为了让所有语言的同学都可以理解
// 不会使用任何java语言自带的数据结构
// 只使用最简单的数组结构

/*
核心
    dp[i][j] 表示指针在i搞定key[j...]的最小代价
    当r[i]==k[j]时，直接按下
    当r[i]!=k[j]时，只需要找顺时针最近和逆时针最近取最小就可以
坑点
    顺时针最近就是在where查找 >i最靠左的下标，若不存在，就代表要转到下一圈，返回最后一位
    逆时针最近就是在where查找 <i最靠右的下标，若不存在，就代表要转到下一圈，返回第0位
*/


#include<bits/stdc++.h>
using namespace std;

int n, m;
int ring[105];
int key[105];

int sz[26];
int where[26][105];
int dp[105][105];

void bulid(string& r,string& k){
    n = r.length();
    m = k.length();
    for (int i = 0; i < 26; ++i) sz[i] = 0;
    for (int i = 0,v; i < n; ++i){
        v = r[i] - 'a';
        where[v][sz[v]++] = i;
        ring[i] = v;
    }
    for (int i = 0; i < m; ++i){
        key[i] = k[i] - 'a';
    }
    for (int i = 0; i < 105;++i){
        for (int j = 0; j < 105; ++j){
            dp[i][j] = -1;
        }
    }
}

int sfind(int i,int v){
    int l = 0, r = sz[v] - 1, m, ans = -1;
    auto p = where[v];
    while(l<=r){
        m = (l + r) / 2;
        if(p[m]>i){
            ans=m;
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    return ans == -1 ? p[0] : p[ans];
}

int nfind(int i,int v){
    int l = 0, r = sz[v] - 1, m, ans = -1;
    auto p = where[v];
    while(l<=r){
        m = (l + r) / 2;
        if(p[m]<i){
            ans=m;
            l = m + 1;
        }else{
            r = m - 1;
        }
    }
    return ans == -1 ? p[sz[v] - 1] : p[ans];
}

//指针指向i位置时，搞定key[j...]的最小代价
int f(int i,int j){
    if(j==m) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    int ans = 0;
    if(ring[i]==key[j]){
        ans = 1 + f(i, j + 1);
    }else{
        int j1 = sfind(i, key[j]);
        int d1 = j1 > i ? j1 - i : n - i + j1;
        int j2 = nfind(i, key[j]);
        int d2 = i > j2 ? i - j2 : i + n - j2;
        ans = min(d1 + f(j1, j), d2 + f(j2, j));
    }
    dp[i][j] = ans;
    return ans;
}



class Solution {
public:
    int findRotateSteps(string r, string k) {
        bulid(r, k);
        return f(0, 0);
    }
};