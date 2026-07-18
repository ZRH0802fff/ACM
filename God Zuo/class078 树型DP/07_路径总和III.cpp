// 路径总和 III
// 给定一个二叉树的根节点 root ，和一个整数 targetSum
// 求该二叉树里节点值之和等于 targetSum 的 路径 的数目
// 路径 不需要从根节点开始，也不需要在叶子节点结束
// 但是路径方向必须是向下的（只能从父节点到子节点）
// 测试链接 : https://leetcode.cn/problems/path-sum-iii/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

long long ans;
unordered_map<long long, int> presum;

// sum : 从头节点出发，来到x的时候，上方累加和是多少
// 路径必须以x作为结尾，路径累加和是target的路径数量，累加到全局变量ans上
void f(TreeNode* x, int target, long long sum) {
    if (x != nullptr) {
        sum += x->val; // 从头节点出发一路走到x的整体累加和
        ans += presum[sum - target];
        presum[sum]++;
        f(x->left, target, sum);
        f(x->right, target, sum);
        presum[sum]--;
    }
}

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        presum.clear();
        presum[0] = 1;
        ans = 0;
        f(root, targetSum, 0);
        return (int)ans;
    }
};
