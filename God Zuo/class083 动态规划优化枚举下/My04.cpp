// 累加和不大于k的最长子数组
// 给定一个无序数组arr，长度为n，其中元素可能是正、负、0
// 给定一个整数k，求arr所有的子数组中累加和不大于k的最长子数组长度
// 要求时间复杂度为O(n)
// 测试链接 : https://www.nowcoder.com/practice/3473e545d6924077a4f7cbc850408ade
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
// 至今的最优解，全网题解几乎都是我几年前讲的方法

/*
核心
    求 ..j..i.. 在累加和小于等于k时使j..i长度最长
    pre -> 前j-1个数的前缀和
    sum -> 前i个数的和
    要求 sum-pre<=k
    转化 pre>=sum-k
    来到每一个i位置，找到最早出现（最左）满足要求的pre
    当pre开始下降时，我们让他等于前一个数，做到不下降，就可以二分了

*/

#include<bits/stdc++.h>
using namespace std;

int n, k,ans;
int arr[100010];
int sums[100010];

int find(int num){
    int l = 0, r = n, m, ans = 1;
    while(l<=r){
        m = (l + r) / 2;
        if(sums[m]>=num){
            ans = m;
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin>>arr[i];
    for (int i = 0,sum=0; i < n; ++i){
        sum += arr[i];
        sums[i + 1] = max(sum, sums[i]);
    }
    int sum = 0, pre, len;
    for (int i = 0; i < n; ++i){
        sum += arr[i];
        pre = find(sum - k);
        len = (pre == -1) ? 0 : i - pre + 1;
        ans = max(ans, len);
    }
    cout << ans << '\n';
    return 0;
}