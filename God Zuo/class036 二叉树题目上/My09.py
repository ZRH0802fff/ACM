class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def countNodes(self, root: TreeNode) -> int:
        if not root:
            return 0
        
        h=self.mostleft(root,1)
        return self.f(root,1,h)

    def f(self,cur, level,h):
        if level==h:
            return 1
        if self.mostleft(cur.right,level+1):
            return (1<<(h-level))+self.f(cur.right,level+1,h)
        else:
            return (1<<(h-level-1))+self.f(cur.left,level+1,h)
        

    def mostleft(self,cur, level):
        while cur:
            level+=1
            cur=cur.left
        return level-1