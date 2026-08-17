class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution1:
    def isValidBST(self, root):
        if not root:
            return True
        stack=[]
        pre=None
        while stack or root:
            while root:
                stack.append(root)
                root=root.left
            root=stack.pop()
            if pre is not None and pre.val>=root.val:
                return False
            pre = root
            root = root.right
        return True
                
class Solution2:
    def isValidBST(self, root):
        if not root:
            return True
        self.ma=float('-inf')
        self.mi=float('inf')
        
        def f(cur):
            if not cur :
                self.ma=float('-inf')
                self.mi=float('inf')
                return True
            ll=f(cur.left)
            lmi=self.mi
            lma=self.ma
            rr=f(cur.right)
            rmi=self.mi
            rma=self.ma
            self.mi=min(lmi,rmi,cur.val)
            self.ma=max(lma,rma,cur.val)
            return ll and rr and lma<cur.val and cur.val<rmi
        return f(root)