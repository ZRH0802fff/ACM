// #include<bits/stdc++.h>
// using namespace std;

// int arr[4];
// int nums[25];
// int fin;

// bool isOK(int mid,int n){
//     int zuo = 0, you = 0;
//     for (int i = 0; i < n; ++i){
//         if(zuo<you){
//             zuo += nums[i];
//         }else{
//             you += nums[i];
//         }
//     }
//     return max(zuo, you) <= mid;
// }

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     for (int _ = 0; _ < 4; ++_){
//         cin >> arr[_];
//     }
//     for (int _ = 0; _ < 4; ++_){
//         int n = arr[_];
//         int sum = 0;
//         for (int i = 0; i < n; ++i){
//             cin >> nums[i];
//             sum += nums[i];
//         }
//         int l = sum / 2, r = sum, mid, ans;
//         while(l<=r){
//             mid = (l + r) / 2;
//             if(isOK(mid,n)){
//                 r = mid - 1;
//                 ans = mid;
//             }else{
//                 l = mid + 1;
//             }
//         }
//         fin += ans;
//     }
//     cout << fin << '\n';
//     return 0;
// }


/*
坑点：
    二分+贪心检查错误的，
    设置左右脑，数组排序后就从大到小拿，左右脑哪个小往那里放
    例子{4，4，3，3，2}可以推翻
核心点：
    最终目标是把一个数组里面的数划分成两组，使这两组之间的累加和尽可能的小。
    将sum/2当作背包容量，每题的time是容量和价值
    用01背包在不超过sum/2的情况下得到背包能装的最大价值（耗时）
    sum-这个时间得到的时间就是最小的总时间了
*/

#include<bits/stdc++.h>
using namespace std;

int arr[4];
int nums[25];
int fin;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 4; ++i){
        cin >> arr[i];
    }
    for (int _ = 0; _ < 4; ++_){
        int n = arr[_];
        int sum = 0;
        for (int i = 1; i <= n; ++i){
            cin >> nums[i];
            sum += nums[i];
        }
        int m = sum / 2;
        int dp[m + 1];
        for(int i=0;i<=m;++i)
            dp[i] = 0;
        for (int i = 1; i <= n; ++i){
            for (int j = m; j >= nums[i];--j){
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        fin += (sum-dp[m]);
    }
    cout << fin << '\n';
    return 0;
}