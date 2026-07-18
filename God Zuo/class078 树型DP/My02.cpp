// 二叉搜索子树的最大键值和
// 给你一棵以 root 为根的二叉树
// 请你返回 任意 二叉搜索子树的最大键值和
// 二叉搜索树的定义如下：
// 任意节点的左子树中的键值都 小于 此节点的键值
// 任意节点的右子树中的键值都 大于 此节点的键值
// 任意节点的左子树和右子树都是二叉搜索树
// 测试链接 : https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/

#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:

    struct Info{
        int maxVal, minVal, sum;
        bool isBst;
        int maxSum;
        Info(int a,int b,int c,bool d,int e)
            :maxVal(a),minVal(b),sum(c),isBst(d),maxSum(e) {}
    };

    Info f(TreeNode* x){
        if(x==nullptr)
            return Info(INT_MIN, INT_MAX, 0, true, 0);
        Info f1 = f(x->left);
        Info f2 = f(x->right);
        int maxVal = max(x->val, max(f1.maxVal, f2.maxVal));
        int minVal = min(x->val, min(f1.minVal, f2.minVal));
        int sum = f1.sum + f2.sum + x->val;
        bool isBst = f1.isBst && f2.isBst && f1.maxVal < x->val && x->val < f2.minVal;
        int maxSum = max(f1.maxSum, f2.maxSum);
        if(isBst){
            maxSum = max(maxSum, sum);
        }
        return Info(maxVal, minVal, sum, isBst, maxSum);
    }

    int maxSumBST(TreeNode* root) {
        return f(root).maxSum;
    }
};