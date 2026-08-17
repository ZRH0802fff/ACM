# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        """
        二叉搜索树（BST）中两个节点的最近公共祖先
        LeetCode: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/
        
        利用 BST 的有序性，时间复杂度 O(h)，h 为树高
        """
        # 假设 p.val <= q.val （不需要提前排序，因为下面用了 min/max）
        while root:
            # 当前节点值在 [min(p,q), max(p,q)] 之间 → 就是 LCA
            if min(p.val, q.val) < root.val < max(p.val, q.val):
                return root
            
            # 当前节点就是 p 或 q 中的一个 → 也是 LCA（因为另一个在它的子树中）
            if root.val == p.val or root.val == q.val:
                return root
            
            # root.val 在两者左侧 → 往右子树走
            if root.val < min(p.val, q.val):
                root = root.right
            # root.val 在两者右侧 → 往左子树走
            else:
                root = root.left
        
        # 理论上不会走到这里（因为 p 和 q 一定在树中）
        return None