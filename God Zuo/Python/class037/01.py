# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        """
        普通二叉树两个节点的最近公共祖先
        LeetCode: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
        """
        # 边界情况：root 为空，或 root 本身就是 p 或 q 中的一个
        if not root or root == p or root == q:
            return root
        
        # 向左子树递归查找
        left = self.lowestCommonAncestor(root.left, p, q)
        # 向右子树递归查找
        right = self.lowestCommonAncestor(root.right, p, q)
        
        # 情况1：左右子树都找到了 → 当前节点就是 LCA
        if left and right:
            return root
        
        # 情况2：左右子树都没找到 → 返回 None
        # （实际上这里可以省略，因为下面会处理，但保留更清晰）
        if not left and not right:
            return None
        
        # 情况3：只有一个子树找到了 → 返回找到的那个（可能是 p/q 本身，也可能是它们的 LCA）
        return left if left else right