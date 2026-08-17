class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isBalanced(self, root):
        # 使用类属性作为“全局”标志（替代 Java 的 static balance）
        self.balance = True
        
        def height(cur):
            # 如果已经不平衡了，或者节点为空，直接返回 0
            if not self.balance or not cur:
                return 0
            
            lh = height(cur.left)
            rh = height(cur.right)
            
            # 检查当前节点是否平衡
            if abs(lh - rh) > 1:
                self.balance = False
            
            return max(lh, rh) + 1
        
        height(root)
        return self.balance