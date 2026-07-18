// 二叉树的直径
// 给你一棵二叉树的根节点，返回该树的直径
// 二叉树的 直径 是指树中任意两个节点之间最长路径的长度
// 这条路径可能经过也可能不经过根节点 root
// 两节点之间路径的 长度 由它们之间边数表示
// 测试链接 : https://leetcode.cn/problems/diameter-of-binary-tree/

#include<bits/stdc++.h>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

class Solution {
public:
    struct Info{
        int l;
        int h;
        Info(int a,int b) : l(a),h(b){}
    };

    Info f(TreeNode* x){
        if(x==nullptr)
            return Info(0, 0);
        Info f1 = f(x->left);
        Info f2 = f(x->right);
        int h = max(f1.h, f2.h) + 1;
        int l = max(f1.l, f2.l);
        l = max(l, f1.h + f2.h);
        return Info(l, h);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        return f(root).l;
    }
};