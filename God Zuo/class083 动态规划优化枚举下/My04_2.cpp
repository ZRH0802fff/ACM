// 累加和不大于k的最长子数组
// 给定一个无序数组arr，长度为n，其中元素可能是正、负、0
// 给定一个整数k，求arr所有的子数组中累加和不大于k的最长子数组长度
// 要求时间复杂度为O(n)
// 测试链接 : https://www.nowcoder.com/practice/3473e545d6924077a4f7cbc850408ade
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
// 至今的最优解，全网题解几乎都是我几年前讲的方法

#include<bits/stdc++.h>
using namespace std;

int nums[100010];
int minsums[100010];             //从i开始往右扩充能得到的最小累加和
int minsumends[100010];          //得到最小累加和的右边界
int n, k, ans;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin>>nums[i];
    
    minsums[n - 1] = nums[n - 1];
    minsumends[n - 1] = n - 1;
    for (int i = n - 1; i >= 0; --i){
        if (minsums[i+1]<0){
            minsums[i] = nums[i] + minsums[i + 1];
            minsumends[i] = minsumends[i + 1];
        }else{
            minsums[i] = nums[i];
            minsumends[i] = i;
        }
    }

    for (int i = 0, sum = 0, end = 0; i < n; ++i){
        while(end<n && sum+minsums[end]<=k){
            sum += minsums[end];
            end = minsumends[end] + 1;
        }
        if(end>i){
            ans = max(ans, end - i);
            sum -= nums[i];
        }else{
            end = i + 1;
        }
    }
    cout << ans << '\n';
    return 0;
}   