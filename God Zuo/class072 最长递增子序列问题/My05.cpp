// 有一次修改机会的最长不下降子序列
// 给定一个长度为n的数组arr，和一个整数k
// 只有一次机会可以将其中连续的k个数全修改成任意一个值
// 这次机会你可以用也可以不用，请返回最长不下降子序列长度
// 1 <= k, n <= 10^5
// 1 <= arr[i] <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P8776
// 核心: 修改的K个紧贴分界点; 枚举j: left(结尾<=arr[j]) + K + rightArr[j](以arr[j]开头)
//       rightArr: 从右往左最长不上升 = 从左往右以该位置开头的最长不下降
//       分离: 用arr[j](分界值)查edp, 用arr[i](滑出窗口)入edp
// 坑点: ①别漏末尾K个(右侧空)的情况 ans=max(ans, len+K)
//       ②edp在computeRight(bs1:<最左)和主循环(bs2:>最左)复用, 二分策略不同
//       ③suffix[n-1]必须显式置0(全局数组残留)


#include<bits/stdc++.h>
using namespace std;

int n, k;
int arr[100010];
int rg[100010];
int red[100010];
int ed[100010];

int bs1(int len,int num){
    int l = 0, r = len - 1, m, ans = -1;
    while(l<=r){
        m = (l + r) / 2;
        if(red[m]<num){
            ans = m;
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    return ans;
}

int bs2(int len,int num){
    int l = 0, r = len - 1, m, ans=-1;
    while(l<=r){
        m = (l + r) / 2;
        if(ed[m]>num){
            ans = m;
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    return ans;
}

void r(){
    int len = 0;
    for (int i = n - 1, find; i >= 0; --i){
        find = bs1(len, arr[i]);
        if(find==-1){
            red[len++] = arr[i];
            rg[i]=len;
        }else{
            red[find] = arr[i];
            rg[i] = find + 1;
        }
    }
}

int f(){
    r();
    int len = 0;
    int ans = 0;
    for (int i = 0, j = k, find, l; j < n; ++i, ++j){
        find = bs2(len, arr[j]);
        l = find == -1 ? len : find;
        ans = max(ans, l + k + rg[j]);
        find = bs2(len, arr[i]);
        if(find==-1){
            ed[len++] = arr[i];
        }else{
            ed[find] = arr[i];
        }
    }
    ans = max(ans, len + k);
    return ans;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 0; i < n;++i)
        cin >> arr[i];
    if(k>=n)
        cout << n << '\n';
    else
        cout << f() << '\n';
    return 0;
}