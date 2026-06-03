# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def build_tree(preorder, inorder):
    if not preorder or not inorder or len(preorder) != len(inorder):
        return None
    map_ = {val: idx for idx, val in enumerate(inorder)}
    def f(l1, r1, l2, r2):
        if l1 > r1:
            return None
        head = TreeNode(preorder[l1])
        if l1 == r1:
            return head
        k = map_[preorder[l1]]
        head.left = f(l1 + 1, l1 + k - l2, l2, k - 1)
        head.right = f(l1 + k - l2 + 1, r1, k + 1, r2)
        return head
    return f(0, len(preorder) - 1, 0, len(inorder) - 1)