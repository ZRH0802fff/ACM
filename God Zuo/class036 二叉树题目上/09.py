# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def countNodes(self, root: TreeNode) -> int:
        if not root:
            return 0
        
        # 先求整棵树的高度（最左路径长度）
        h = self.most_left(root, 1)
        
        return self.f(root, 1, h)
    
    
    def f(self, cur: TreeNode, level: int, h: int) -> int:
        # """
        # cur: 当前子树的根
        # level: cur 所在的层数（从1开始）
        # h: 整棵树的高度
        # 返回：以 cur 为根的子树节点个数
        # """
        if level == h:
            return 1
        
        # 检查右子树的最左路径是否能到达最底层
        if self.most_left(cur.right, level + 1) == h:
            # 右树是最满的 → 左树是满二叉树 + 右树递归
            # 左树节点数 = 2^(h - level) - 1 + 1（根） → 直接用位移：1 << (h - level)
            return (1 << (h - level)) + self.f(cur.right, level + 1, h)
        else:
            # 右树不满 → 右树是满二叉树（高度 h-1） + 左树递归
            return (1 << (h - level - 1)) + self.f(cur.left, level + 1, h)
    
    
    def most_left(self, cur: TreeNode, level: int) -> int:
        # """
        # 从 cur 开始一直往左走，能到达的层数
        # 返回值：到达的最深层数（从1开始计数）
        # """
        while cur:
            level += 1
            cur = cur.left
        return level - 1


# 如果你喜欢写成函数形式（不使用类）：
def count_nodes(root: TreeNode) -> int:
    if not root:
        return 0
    
    def most_left(cur, level):
        while cur:
            level += 1
            cur = cur.left
        return level - 1
    
    def f(cur, level, h):
        if level == h:
            return 1
        if most_left(cur.right, level + 1) == h:
            return (1 << (h - level)) + f(cur.right, level + 1, h)
        return (1 << (h - level - 1)) + f(cur.left, level + 1, h)
    
    h = most_left(root, 1)
    return f(root, 1, h)