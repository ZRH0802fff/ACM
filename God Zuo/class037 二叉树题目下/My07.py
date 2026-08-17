class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def rob(self, root):
        self.yes=0
        self.no=0
        def f(cur):
            if not cur:
                self.no=0
                self.yes=0
                return 
            f(cur.left)
            y=cur.val+self.no
            n=max(self.yes,self.no)
            f(cur.right)
            y+=self.no
            n+=max(self.yes,self.no)
            self.no=n
            self.yesj=y
            return 
        f(root)
        return max(self.yes,self.no)
    