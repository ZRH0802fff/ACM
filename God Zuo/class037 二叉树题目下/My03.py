class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def pathSum(self, root, targetSum):
        result=[]
        path=[]
        def f(cur, sum,path):
            if not cur:
                return
            path.append(cur.val)
            sum+=cur.val
            if not cur.left  and not cur.right:
                if sum==targetSum:
                    result.append(path[:])
            if cur.left:
                f(cur.left,sum,path)
            if cur.right:
                f(cur.right,sum,path)
            path.pop()
        if root:
            f(root,0,path)
        return result