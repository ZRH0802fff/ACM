class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        while root:
            if min(p.val,q.val)< root.val <max(p.val,q.val):
                return root
            if root.val==p.val or root .val ==q.val:
                return root
            if root.val<min(p.val , q.val):
                root = root.right
            else:
                root =root.left
        return None 