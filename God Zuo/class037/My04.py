class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isBalanced(self, root):
        self.balance=True
        def f(cur):
            if not cur or not self.balance:
                return 0
            ll=f(cur.left)
            lr=f(cur.right)
            if abs(ll-lr)>1:
                self.balance=False
                return 0
            return max(lr,ll)+1
        f(root)
        return self.balance