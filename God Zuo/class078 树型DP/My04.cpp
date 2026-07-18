// 在二叉树中分配硬币
// 给你一个有 n 个结点的二叉树的根结点 root
// 其中树中每个结点 node 都对应有 node.val 枚硬币
// 整棵树上一共有 n 枚硬币
// 在一次移动中，我们可以选择两个相邻的结点，然后将一枚硬币从其中一个结点移动到另一个结点
// 移动可以是从父结点到子结点，或者从子结点移动到父结点
// 返回使每个结点上 只有 一枚硬币所需的 最少 移动次数
// 测试链接 : https://leetcode.cn/problems/distribute-coins-in-binary-tree/

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
        int cnt, sum, move;
        Info(int a,int b,int c): cnt(a),sum(b),move(c) {}
    };

    Info f(TreeNode* x){
        if(x==nullptr)
            return Info(0, 0, 0);
        Info f1 = f(x->left);
        Info f2 = f(x->right);
        int cnt = f1.cnt + f2.cnt + 1;
        int sum = f1.sum + f2.sum + x->val;
        int move = f1.move + f2.move + abs(f1.cnt - f1.sum) + abs(f2.cnt - f2.sum);
        return Info(cnt, sum, move);
    }

    int distributeCoins(TreeNode* root) {
        return f(root).move;
    }
};