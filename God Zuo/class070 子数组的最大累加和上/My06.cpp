// 子矩阵最大累加和问题
// 给定一个二维数组grid，找到其中子矩阵的最大累加和
// 返回拥有最大累加和的子矩阵左上角和右下角坐标
// 如果有多个子矩阵都有最大累加和，返回哪一个都可以
// 测试链接 : https://leetcode.cn/problems/max-submatrix-lcci/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    vector<int> getMaxMatrix(vector<vector<int>> &matrix){
        int n = matrix.size();
        int m = matrix[0].size();
        int ma = matrix[0][0];
        int a = 0, b = 0, c = 0, d = 0;
        int nums[m];
        for (int up = 0; up < n;++up){
            for (int j = 0; j < m;++j)
                nums[j] = 0;
            for (int down = up; down < n; ++down){
                for (int l = 0, r = 0, pre = INT_MIN; r < m;++r){
                    nums[r] += matrix[down][r];
                    if(pre>=0){
                        pre += nums[r];
                    }else{
                        pre = nums[r];
                        l = r;
                    }
                    if(pre>ma){
                        ma = pre;
                        a = up;
                        b = l;
                        c = down;
                        d = r;
                    }
                }
            }
        }
        return {a, b, c, d};
    }
};