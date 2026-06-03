class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def trimBST(self, root: TreeNode, low: int, high: int) -> TreeNode:
        if  not root:
            return None
        if root.val<low:
            self.trimBST(root.right)
        if root.val>high:
            self.trimBST(root.left)
        root.left=self.trimBST(root.left)
        root.right=self.trimBST(root.left)
        return root
            