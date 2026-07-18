// 最大BST子树
// 给定一个二叉树，找到其中最大的二叉搜索树（BST）子树，并返回该子树的大小
// 其中，最大指的是子树节点数最多的
// 二叉搜索树（BST）中的所有节点都具备以下属性：
// 左子树的值小于其父（根）节点的值
// 右子树的值大于其父（根）节点的值
// 注意：子树必须包含其所有后代
// 测试链接 : https://leetcode.cn/problems/largest-bst-subtree/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:

    struct Info{
        ll maxv, minv;
        bool isBST;
        int maxs;
        Info(ll a, ll b, bool c, int d) 
            : maxv(a), minv(b), isBST(c), maxs(d) {}
    };

    Info f(TreeNode* x){
        if(x==nullptr){
            return Info(LLONG_MIN, LLONG_MAX, true, 0);
        }
        Info f1 = f(x->left);
        Info f2 = f(x->right);
        ll maxv = max((ll)x->val, max(f1.maxv, f2.maxv));
        ll minv = min((ll)x->val, min(f1.minv, f2.minv));
        bool isBST = f1.isBST && f2.isBST && f1.maxv < x->val && x->val < f2.minv;
        int maxs;
        if(isBST){
            maxs = f1.maxs + f2.maxs + 1;
        }else{
            maxs = max(f1.maxs, f2.maxs);
        }
        return Info(maxv, minv, isBST, maxs);
    }

    int maxSumBST(TreeNode* root) {
        return f(root).maxs;
    }
};