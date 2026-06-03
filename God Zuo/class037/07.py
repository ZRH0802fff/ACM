class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def rob(self, root):
        self.yes = 0
        self.no = 0
        
        def f(node):
            if not node:
                self.yes = 0
                self.no = 0
                return
            
            # 先递归左右子树
            f(node.left)
            # 偷当前节点 → 左右子树都不能偷根 → 用左右的 no
            y = node.val + self.no
            
            # 不偷当前节点 → 左右子树取最大值
            n = max(self.yes, self.no)
            
            f(node.right)
            # 继续累加右子树的结果
            y += self.no
            n += max(self.yes, self.no)
            
            # 更新全局
            self.yes = y
            self.no = n
        
        f(root)
        return max(self.yes, self.no)