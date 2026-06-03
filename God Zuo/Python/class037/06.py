# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def trimBST(self, root: TreeNode, low: int, high: int) -> TreeNode:
        """
        修剪二叉搜索树，使得所有节点值都在 [low, high] 范围内
        返回修剪后的树的根节点
        
        思路：因为是二叉搜索树，利用有序性进行剪枝
        1. 如果当前节点为空 → 返回 None
        2. 如果当前节点值 < low → 整个左子树都不合法，只需递归右子树
        3. 如果当前节点值 > high → 整个右子树都不合法，只需递归左子树
        4. 如果当前节点值在 [low, high] 内 → 保留该节点，递归修剪左右子树
        """
        if not root:
            return None
        
        # 当前节点太小，整个左子树都太小，只看右子树
        if root.val < low:
            return self.trimBST(root.right, low, high)
        
        # 当前节点太大，整个右子树都太大，只看左子树
        if root.val > high:
            return self.trimBST(root.left, low, high)
        
        # 当前节点在 [low, high] 范围内，保留它，并修剪左右子树
        root.left = self.trimBST(root.left, low, high)
        root.right = self.trimBST(root.right, low, high)
        
        return root