// 二叉搜索子树的最大键值和
// 给你一棵以 root 为根的二叉树
// 请你返回 任意 二叉搜索子树的最大键值和
// 二叉搜索树的定义如下：
// 任意节点的左子树中的键值都 小于 此节点的键值
// 任意节点的右子树中的键值都 大于 此节点的键值
// 任意节点的左子树和右子树都是二叉搜索树
// 测试链接 : https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct Info {
    // 为什么这里的max和min是int类型？
    // 因为题目的数据量规定，
    // 节点值在[-4 * 10^4，4 * 10^4]范围
    // 所以int类型的最小值和最大值就够用了
    // 不需要用long类型
    int maxVal;
    int minVal;
    int sum;
    bool isBst;
    int maxBstSum;
    Info(int a, int b, int c, bool d, int e)
        : maxVal(a), minVal(b), sum(c), isBst(d), maxBstSum(e) {}
};

Info f(TreeNode* x) {
    if (x == nullptr) {
        return Info(INT_MIN, INT_MAX, 0, true, 0);
    }
    Info infol = f(x->left);
    Info infor = f(x->right);
    int maxVal = max(x->val, max(infol.maxVal, infor.maxVal));
    int minVal = min(x->val, min(infol.minVal, infor.minVal));
    int sum = infol.sum + infor.sum + x->val;
    bool isBst = infol.isBst && infor.isBst && infol.maxVal < x->val && x->val < infor.minVal;
    int maxBstSum = max(infol.maxBstSum, infor.maxBstSum);
    if (isBst) {
        maxBstSum = max(maxBstSum, sum);
    }
    return Info(maxVal, minVal, sum, isBst, maxBstSum);
}

class Solution {
public:
    int maxSumBST(TreeNode* root) {
        return f(root).maxBstSum;
    }
};
