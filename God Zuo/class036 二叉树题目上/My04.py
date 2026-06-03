# 求二叉树的最大、最小深度

# 不提交这个类
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    # 测试链接 : https://leetcode.cn/problems/maximum-depth-of-binary-tree/
    def maxDepth(self, root: TreeNode) -> int:
        return 0 if not root else max(self.maxDepth(root.left) , self.maxDepth(root.right) )+1
    
   # 测试链接 : https://leetcode.cn/problems/minimum-depth-of-binary-tree/
    def minDepth(self, root: TreeNode) -> int:
        if not root:
            return 0
        if not root.left and not root.right:
            return 1
        ldeep = float('inf')
        rdeep = float('inf')
        if root.left:
            ldeep=self.minDepth(root.left)
        if root.right:
            rdeep=self.minDepth(root.right)
        return min(ldeep,rdeep)+1