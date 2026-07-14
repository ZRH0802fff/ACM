// 乘积最大子数组
// 给你一个整数数组 nums
// 请你找出数组中乘积最大的非空连续子数组
// 并返回该子数组所对应的乘积
// 测试链接 : https://leetcode.cn/problems/maximum-product-subarray/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = nums[0], pmin = nums[0], pmax = nums[0], cmin, cmax;
        for (int i = 1; i < nums.size();++i){
            cmin = min({nums[i], pmin * nums[i], pmax * nums[i]});
            cmax = max({nums[i], pmin * nums[i], pmax * nums[i]});
            pmin = cmin;
            pmax = cmax;
            ans = ans > pmax ? ans : pmax;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 3, -2, 4};
    cout << sol.maxProduct(nums) << endl;

    nums = {-2, 0, -1};
    cout << sol.maxProduct(nums) << endl;

    nums = {-2, 3, -4};
    cout << sol.maxProduct(nums) << endl;
    return 0;
}



//踩坑：max和min函数只能接受两个变量，若有多个需要用{}括起来当作数组

//此题核心: 
//1.将乘积最大值的可能行分为三种：一种是自身，另外两种是拿前面的最大值乘上当前数。
//2.当前数若为负数希望×的是上一个的最小值，对应第二种情况
//3.当前数若为正数则希望×的上一个是最大值，对应第三种情况
//因此每一轮需要四个变量去滚动，上一轮的最大最小与这一轮的最大最小
