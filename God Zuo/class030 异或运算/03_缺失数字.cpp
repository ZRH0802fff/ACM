// 找到缺失的数字
// 测试链接 : https://leetcode.cn/problems/missing-number/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int eorAll = 0, eorHas = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            eorAll ^= i;
            eorHas ^= nums[i];
        }
        eorAll ^= nums.size();
        return eorAll ^ eorHas;
    }
};
