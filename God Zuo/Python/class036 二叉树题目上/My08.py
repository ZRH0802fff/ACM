# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isCompleteTree(self, root: TreeNode) -> bool:
        if not root:
            return True
        
        queue = []
        queue.append(root)
        leaf = False
        
        while queue:
            node = queue.pop(0)
            
            # 规则1：有右孩子但没有左孩子 → 非法
            if node.left is None and node.right is not None:
                return False
            
            # 规则2：已经遇到过不完整的节点，后面不能再有任何孩子
            if leaf and (node.left is not None or node.right is not None):
                return False
            
            # 正确入队：先左后右
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
            
            # 一旦当前节点不是“左右都完整”，标记为 leaf 阶段
            if node.left is None or node.right is None:
                leaf = True
        
        return True